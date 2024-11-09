#include <Geode/Geode.hpp>
#include <Geode/modify/SetGroupIDLayer.hpp>
#include <Geode/utils/NodeIDs.hpp>
#include <Geode/ui/TextInput.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;
using namespace std::string_view_literals;

// TODO: remove this when beta.22 comes out
inline bool isSpriteFrameName(CCNode* node, const char* name) {
    if (!node) return false;

    auto cache = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name);
    if (!cache) return false;

    auto* texture = cache->getTexture();
    auto rect = cache->getRect();

    if (auto* spr = typeinfo_cast<CCSprite*>(node)) {
        if (spr->getTexture() == texture && spr->getTextureRect() == rect) {
            return true;
        }
    } else if (auto* btn = typeinfo_cast<CCMenuItemSprite*>(node)) {
        auto* img = btn->getNormalImage();
        if (auto* spr = typeinfo_cast<CCSprite*>(img)) {
            if (spr->getTexture() == texture && spr->getTextureRect() == rect) {
                return true;
            }
        }
    }
    return false;
}

static void offsetChildren(CCMenu* target, CCPoint const& offset) {
    auto winSize = CCDirector::get()->getWinSize();
    for (auto child : CCArrayExt<CCNode*>(target->getChildren())) {
        child->setPosition(child->getPosition() - winSize + target->getContentSize() / 2 + offset);
    }
}

static void replaceInput(
    CCNode* parent, const char* inputID, const char* bgID,
    CCTextInputNode** inputMember
) {
    auto input = static_cast<CCTextInputNode*>(parent->getChildByID(inputID));
    if (!input) return;
    auto bg = parent->getChildByID(bgID);
    auto newInput = TextInput::create(bg->getContentSize().width, input->m_caption);
    parent->addChild(newInput);
    // newInput->getInput()->m_placeholderScale = input->m_placeholderScale;
    // newInput->getInput()->m_maxLabelScale = input->m_maxLabelScale;
    // newInput->getInput()->m_maxLabelLength = input->m_maxLabelLength;
    // newInput->getInput()->m_maxLabelWidth = input->m_maxLabelWidth;
    newInput->getInputNode()->m_numberInput = input->m_numberInput;
    newInput->setFilter(input->m_allowedChars);
    newInput->setString(input->getString());
    newInput->setDelegate(input->m_delegate, input->getTag());
    newInput->setID(inputID);
    newInput->setPosition(bg->getPosition());

    input->removeFromParent();
    bg->removeFromParent();
    
    *inputMember = newInput->getInputNode();
}

$register_ids(SetGroupIDLayer) {
    auto winSize = CCDirector::get()->getWinSize();

    m_buttonMenu->setID("main-menu");

    setIDs(
        this, 0,
        "main-layer",
        // for some god knows reason these are not in m_mainLayer???
        "preview-label",
        "playback-label"
    );

    setIDs(
        m_mainLayer, 0,
        "background",
        "groups-bg",
        "editor-layer-label",
        "editor-layer-2-label",
        "add-group-id-label",
        "z-order-label",
        "z-layer-label",
        "groups-list-menu",
        "editor-layer-input-bg",
        "editor-layer-input",
        "editor-layer-2-input-bg",
        "editor-layer-2-input",
        "add-group-id-input-bg",
        "add-group-id-input",
        "z-order-input-bg",
        "z-order-input",
        "draw-order-label",
        "channel-order-input-bg",
        "channel-order-input",
        "channel-input-bg",
        "channel-input"
    );
    
    if (auto menu = m_mainLayer->getChildByID("groups-list-menu")) {
        int offset = 0;

        setIDs(
            menu, &offset,
            "ok-button",
            "editor-layer-next-free-button",
            "editor-layer-2-next-free-button",
            "info-button",
            "editor-layer-prev-button",
            "editor-layer-next-button",
            "editor-layer-2-prev-button",
            "editor-layer-2-next-button",
            "add-group-id-prev-button",
            "add-group-id-next-button",
            "next-free-button",
            "add-group-id-button"
        );

        if (m_targetObject) {
            setIDs(menu, &offset, "add-group-parent-button");
        }

        setIDs(
            menu, &offset,
            "z-order-prev-button",
            "z-order-next-button",
            "b5-layer-button",
            "b4-layer-button",
            "b3-layer-button",
            "b2-layer-button",
            "b1-layer-button",
            "t1-layer-button",
            "t2-layer-button",
            "t3-layer-button",
            "t4-layer-button",
            "default-layer-button"
        );

        // i have no idea what member control these buttons, sorry
        // so just use the sprite name
        if (::isSpriteFrameName(getChild(menu, offset), "GJ_colorBtn_001.png")) {
            // TODO: make a menu for these two
            setIDs(
                menu, &offset,
                "z-layer-decrement-button",
                "z-layer-increment-button"
            );
        }

        if (m_showChannelOrder) {
            setIDs(
                menu, &offset,
                "channel-order-prev-button",
                "channel-order-next-button",
                "channel-prev-button",
                "channel-next-button",
                "channel-next-free-button"
            );
        }

        offset += m_groupIDObjects->count();

        for (int i = offset; i < menu->getChildrenCount(); i++) {
            auto child = getChild(menu, i);
            if (auto btn = getChildOfType<ButtonSprite>(child, 0)) {
                if (auto label = getChildOfType<CCLabelBMFont>(btn, 0)) {
                    if (label->getString() == "Copy"sv) {
                        child->setID("copy-button");
                    } else if (label->getString() == "Paste"sv) {
                        child->setID("paste-button");
                    } else if (label->getString() == "Extra"sv) {
                        child->setID("extra-button");
                    } else if (label->getString() == "Extra2"sv) {
                        child->setID("extra2-button");
                    } else if (label->getString() == "Anim"sv) {
                        child->setID("anim-button");
                    }
                }
            } else if (typeinfo_cast<CCMenuItemToggler*>(child)) {
                child->setID("preview-toggle");
                if (getChild(menu, i + 1))
                    getChild(menu, i + 1)->setID("playback-toggle");
                break;
            }
        }

        replaceInput(m_mainLayer, "editor-layer-input", "editor-layer-input-bg", &m_editorLayerInput);
        replaceInput(m_mainLayer, "editor-layer-2-input", "editor-layer-2-input-bg", &m_editorLayer2Input);
        replaceInput(m_mainLayer, "add-group-id-input", "add-group-id-input-bg", &m_groupIDInput);
        replaceInput(m_mainLayer, "z-order-input", "z-order-input-bg", &m_zOrderInput);
        replaceInput(m_mainLayer, "channel-input", "channel-input-bg", &m_channelInput);
        replaceInput(m_mainLayer, "channel-order-input", "channel-order-input-bg", &m_orderInput);

        auto okMenu = detachAndCreateMenu(
            m_mainLayer,
            "ok-menu",
            RowLayout::create(),
            menu->getChildByID("ok-button")
        );
        okMenu->setPosition(winSize.width / 2, winSize.height / 2 - 130);
        okMenu->setContentSize({ 75, 60 });
        okMenu->updateLayout();

        auto infoMenu = detachAndCreateMenu(
            m_mainLayer,
            "info-menu",
            RowLayout::create()
                ->setAxisReverse(true)
                ->setAxisAlignment(AxisAlignment::End),
            menu->getChildByID("info-button")
        );
        infoMenu->setPosition(winSize.width / 2 + 185, winSize.height / 2 + 140);
        infoMenu->setAnchorPoint({ 1.f, .5f });
        infoMenu->setContentSize({ 30, 30 });
        infoMenu->updateLayout();

        auto editorLMenu = detachAndCreateMenu(
            m_mainLayer,
            "editor-layer-menu",
            nullptr,
            m_mainLayer->getChildByID("editor-layer-input"),
            menu->getChildByID("editor-layer-next-free-button"),
            menu->getChildByID("editor-layer-prev-button"),
            menu->getChildByID("editor-layer-next-button"),
            m_mainLayer->getChildByID("editor-layer-label")
        );
        editorLMenu->setPosition(winSize.width / 2 - 125, winSize.height / 2 + 115);
        editorLMenu->setContentSize({ 120, 60 });
        offsetChildren(editorLMenu, ccp(0, -10));

        auto editorL2Menu = detachAndCreateMenu(
            m_mainLayer,
            "editor-layer-2-menu",
            nullptr,
            m_mainLayer->getChildByID("editor-layer-2-input"),
            menu->getChildByID("editor-layer-2-next-free-button"),
            menu->getChildByID("editor-layer-2-prev-button"),
            menu->getChildByID("editor-layer-2-next-button"),
            m_mainLayer->getChildByID("editor-layer-2-label")
        );
        editorL2Menu->setPosition(winSize.width / 2, winSize.height / 2 + 115);
        editorL2Menu->setContentSize({ 120, 60 });
        offsetChildren(editorL2Menu, ccp(0, -10));

        auto zOrderMenu = detachAndCreateMenu(
            m_mainLayer,
            "z-order-menu",
            nullptr,
            m_mainLayer->getChildByID("z-order-input"),
            menu->getChildByID("z-order-prev-button"),
            menu->getChildByID("z-order-next-button"),
            m_mainLayer->getChildByID("z-order-label")
        );
        zOrderMenu->setPosition(winSize.width / 2 + 125, winSize.height / 2 + 115);
        zOrderMenu->setContentSize({ 120, 60 });
        offsetChildren(zOrderMenu, ccp(0, -10));

        auto addGroupIDMenu = detachAndCreateMenu(
            m_mainLayer,
            "add-group-id-menu",
            nullptr,
            m_mainLayer->getChildByID("add-group-id-input"),
            menu->getChildByID("add-group-id-prev-button"),
            menu->getChildByID("add-group-id-next-button"),
            m_mainLayer->getChildByID("add-group-id-label")
        );
        addGroupIDMenu->setPosition(winSize.width / 2, winSize.height / 2 + 50);
        addGroupIDMenu->setContentSize({ 120, 60 });
        offsetChildren(addGroupIDMenu, ccp(0, -10));

        auto nextFreeMenu = detachAndCreateMenu(
            m_mainLayer,
            "next-free-menu",
            RowLayout::create(),
            menu->getChildByID("next-free-button")
        );
        nextFreeMenu->setPosition(winSize.width / 2 - 125, winSize.height / 2 + 40);
        nextFreeMenu->setContentSize({ 120, 60 });
        nextFreeMenu->updateLayout();

        auto addGroupMenu = detachAndCreateMenu(
            m_mainLayer,
            "add-group-id-buttons-menu",
            RowLayout::create(),
            menu->getChildByID("add-group-id-button"),
            menu->getChildByID("add-group-parent-button")
        );
        addGroupMenu->setPosition(winSize.width / 2 + 125, winSize.height / 2 + 40);
        addGroupMenu->setContentSize({ 120, 60 });
        addGroupMenu->updateLayout();

        auto zLayerMenu = detachAndCreateMenu(
            m_mainLayer,
            "z-layer-menu",
            RowLayout::create(),
            menu->getChildByID("b5-layer-button"),
            menu->getChildByID("b4-layer-button"),
            menu->getChildByID("b3-layer-button"),
            menu->getChildByID("b2-layer-button"),
            menu->getChildByID("b1-layer-button"),
            menu->getChildByID("t1-layer-button"),
            menu->getChildByID("t2-layer-button"),
            menu->getChildByID("t3-layer-button"),
            menu->getChildByID("t4-layer-button"),
            menu->getChildByID("default-layer-button")
        );
        zLayerMenu->setPosition(winSize.width / 2, winSize.height / 2 - 90);
        zLayerMenu->setContentSize({ 380, 60 });
        zLayerMenu->updateLayout();

        if (auto previewLabel = this->getChildByID("preview-label")) {
            auto previewMenu = detachAndCreateMenu(
                m_mainLayer,
                "preview-menu",
                nullptr,
                previewLabel,
                menu->getChildByID("preview-toggle")
            );
            previewMenu->setContentSize({ 35, 40 });
            offsetChildren(previewMenu, ccp(0, 12));
        }

        if (auto playbackLabel = this->getChildByID("playback-label")) {
            auto playbackMenu = detachAndCreateMenu(
                m_mainLayer,
                "playback-menu",
                nullptr,
                playbackLabel,
                menu->getChildByID("playback-toggle")
            );
            playbackMenu->setContentSize({ 35, 40 });
            offsetChildren(playbackMenu, ccp(0, 12));
        }

        auto actionsMenu = detachAndCreateMenu(
            m_mainLayer,
            "actions-menu",
            ColumnLayout::create()
                ->setAxisReverse(true)
                ->setAxisAlignment(AxisAlignment::End),
            menu->getChildByID("copy-button") ? menu->getChildByID("copy-button") : menu->getChildByID("extra-button"),
            menu->getChildByID("paste-button"),
            menu->getChildByID("extra-button"),
            menu->getChildByID("extra2-button"),
            menu->getChildByID("anim-button"),
            m_mainLayer->getChildByID("preview-menu"),
            m_mainLayer->getChildByID("playback-menu")
        );
        actionsMenu->setPosition(winSize.width / 2 + 220, winSize.height / 2);
        actionsMenu->setContentSize({ 90, 300 });
        actionsMenu->updateLayout();

        auto orderMenu = detachAndCreateMenu(
            m_mainLayer,
            "channel-order-menu",
            nullptr,
            m_mainLayer->getChildByID("channel-order-input"),
            menu->getChildByID("channel-order-prev-button"),
            menu->getChildByID("channel-order-next-button")
        );
        orderMenu->setPosition(winSize.width / 2 - 125, winSize.height / 2 - 120);
        orderMenu->setContentSize({ 120, 60 });
        orderMenu->updateLayout();
        offsetChildren(orderMenu, ccp(0, -10));

        auto channelMenu = detachAndCreateMenu(
            m_mainLayer,
            "channel-menu",
            nullptr,
            m_mainLayer->getChildByID("channel-input"),
            menu->getChildByID("channel-prev-button"),
            menu->getChildByID("channel-next-button"),
            menu->getChildByID("channel-next-free-button")
        );
        channelMenu->setPosition(winSize.width / 2 + 125, winSize.height / 2 - 120);
        channelMenu->setContentSize({ 120, 60 });
        channelMenu->updateLayout();
        offsetChildren(channelMenu, ccp(0, -10));
    }
};

struct SetGroupIDLayerIDs : Modify<SetGroupIDLayerIDs, SetGroupIDLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("SetGroupIDLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set SetGroupIDLayer::init hook priority, node IDs may not work properly");
        }
    }

    bool init(GameObject* obj, CCArray* objs) {
        if (!SetGroupIDLayer::init(obj, objs))
            return false;

        NodeIDs::get()->provide(this);
        handleTouchPriority(this);

        return true;
    }
};
