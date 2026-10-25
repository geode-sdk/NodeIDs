#include <Geode/Geode.hpp>
#include <Geode/binding/GameSettingsLayer.hpp>
#include <Geode/modify/GameSettingsLayer.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

static void wrapSliderInput(Slider* slider, CCMenuItemSpriteExtra* infoBtn, CCTextInputNode* input, CCScale9Sprite* inputBg, CCLabelBMFont* label, std::string id) {
    if (!slider || !slider->getParent()) return;
    auto menu = CCMenu::create();
    menu->setPosition({slider->getPositionX(), slider->getPositionY() + 13.f});
    menu->setContentSize({slider->m_touchLogic->m_length + 15.f, 45.f});
    menu->setID(std::move(id));
    menu->ignoreAnchorPointForPosition(false);
    menu->giveMenuTouchPriority(-506);

    slider->getParent()->addChild(menu);

    switchToMenu(slider, menu);
    slider->setID("slider");
    if (infoBtn) {
        switchToMenu(infoBtn, menu);
        infoBtn->setID("info-button");
    }
    if (inputBg) {
        switchToMenu(inputBg, menu);
        inputBg->setID("input-background");
    }
    if (input) {
        switchToMenu(input, menu);
        input->setID("input");
    }
    if (label) {
        switchToMenu(label, menu);
        label->setID("label");
    }
}

static void wrapNumberButtons(CCLabelBMFont* current, CCMenuItemSpriteExtra* leftBtn, CCMenuItemSpriteExtra* rightBtn, CCLabelBMFont* title, std::string id) {
    if (!current || !leftBtn || !rightBtn || !current->getParent()) return;
    auto menu = CCMenu::create();
    menu->setPosition({current->getPositionX() - 33.f, current->getPositionY() - 2.f});
    menu->setContentSize({155.f, 30.f});
    menu->setID(std::move(id));
    menu->ignoreAnchorPointForPosition(false);
    menu->giveMenuTouchPriority(-506);

    current->getParent()->addChild(menu);

    switchToMenu(current, menu);
    current->setID("current-label");
    switchToMenu(leftBtn, menu);
    leftBtn->setID("left-button");
    switchToMenu(rightBtn, menu);
    rightBtn->setID("right-button");
    if (title) {
        switchToMenu(title, menu);
        title->setID("title-label");
    }
}

$register_ids(GameSettingsLayer) {
    m_mainLayer->setID("main-layer");

    auto winSize = CCDirector::get()->getWinSize();

    setIDs(
        m_mainLayer,
        0,
        "background-outline",
        "background"
    );

    m_buttonMenu->setID("button-menu");

    setIDs(
        m_buttonMenu,
        0,
        "close-button",
        "gameplay-button",
        "visual-button",
        "practice-button",
        "editor-button",
        "audio-button",
        "other-button",
        "prev-button",
        "next-button",
        #ifdef GEODE_IS_DESKTOP
        "keys-button",
        #endif
        "saved-songs-button",
        "audio-offset-info-button",
        #ifdef GEODE_IS_DESKTOP
        "scroll-speed-info-button",
        #endif
        "clear-plat-saves-button",
        "buttons-per-row-left-button",
        "buttons-per-row-right-button",
        "button-rows-left-button",
        "button-rows-right-button",
        "scroll-info-button"
        );
    wrapSliderInput(
        m_mainLayer->getChildByType<Slider>(0),
        typeinfo_cast<CCMenuItemSpriteExtra*>(m_buttonMenu->getChildByID("audio-offset-info-button")),
        m_mainLayer->getChildByType<CCTextInputNode>(0),
        m_mainLayer->getChildByType<CCScale9Sprite>(2),
        m_mainLayer->getChildByType<CCLabelBMFont>(0),
        "audio-offset"
        );
    #ifdef GEODE_IS_DESKTOP
    wrapSliderInput(
        m_mainLayer->getChildByType<Slider>(0),
        typeinfo_cast<CCMenuItemSpriteExtra*>(m_buttonMenu->getChildByID("scroll-speed-button")),
        m_mainLayer->getChildByType<CCTextInputNode>(0),
        m_mainLayer->getChildByType<CCScale9Sprite>(2),
        m_mainLayer->getChildByType<CCLabelBMFont>(0),
        "scroll-speed"
    );
    #endif

    wrapNumberButtons(
        m_mainLayer->getChildByType<CCLabelBMFont>(1),
        typeinfo_cast<CCMenuItemSpriteExtra*>(m_buttonMenu->getChildByID("buttons-per-row-left-button")),
        typeinfo_cast<CCMenuItemSpriteExtra*>(m_buttonMenu->getChildByID("buttons-per-row-right-button")),
        m_mainLayer->getChildByType<CCLabelBMFont>(0),
        "buttons-per-row"
    );

    wrapNumberButtons(
        m_mainLayer->getChildByType<CCLabelBMFont>(1),
        typeinfo_cast<CCMenuItemSpriteExtra*>(m_buttonMenu->getChildByID("button-rows-left-button")),
        typeinfo_cast<CCMenuItemSpriteExtra*>(m_buttonMenu->getChildByID("button-rows-right-button")),
        m_mainLayer->getChildByType<CCLabelBMFont>(0),
        "buttons-rows"
    );

    auto menu = detachAndCreateMenu(
        m_mainLayer,
        "tab-menu",
        RowLayout::create()->setGap(4.f),
        m_buttonMenu->getChildByID("gameplay-button"),
        m_buttonMenu->getChildByID("visual-button"),
        m_buttonMenu->getChildByID("practice-button"),
        m_buttonMenu->getChildByID("editor-button"),
        m_buttonMenu->getChildByID("audio-button"),
        m_buttonMenu->getChildByID("other-button"),
        m_buttonMenu->getChildByID("keys-button")
    );
    menu->setPositionX(winSize.width / 2);
    menu->setContentWidth(385);
    menu->updateLayout();
    menu->giveMenuTouchPriority(-506);
}

struct GameSettingsLayerIDs : Modify<GameSettingsLayerIDs, GameSettingsLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("GameSettingsLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set GameSettingsLayer::init hook priority, node IDs may not work properly");
        }
    }

    void buildTabContent() {
        auto winSize = CCDirector::get()->getWinSize();
        auto holder = CCNode::create();
        holder->setID("toggle-holder");
        holder->setPosition({winSize.width / 2, winSize.height / 2 - 20});
        holder->setAnchorPoint({.5, .5});
        holder->setContentSize({400, 240});
        m_mainLayer->addChild(holder);
        GameSettingsLayer::buildTabContent();
    }

    bool init(GJBaseGameLayer* bgl, int probPage) {
        if (!GameSettingsLayer::init(bgl, probPage)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }

    void addToggle(char const* name, int id, char const* desc, bool disabled) {
        GameSettingsLayer::addToggle(name, id, desc, disabled);
        bool hasDesc = desc && strlen(desc) > 0;
        if (auto toggler = setIDSafe(m_buttonMenu, m_buttonMenu->getChildrenCount() - (hasDesc ? 2 : 1), "toggler")) {
            toggler->setLayoutOptions(AnchorLayoutOptions::create()
                ->setAnchor(Anchor::Left)
                ->setOffset({15, 0}));
            auto label = setIDSafe(m_mainLayer, m_mainLayer->getChildrenCount() - 1, "label");
            label->setLayoutOptions(AnchorLayoutOptions::create()
                ->setAnchor(Anchor::Left)
                ->setOffset({35.25, 0}));
            auto infoBtn = hasDesc ? setIDSafe(m_buttonMenu, m_buttonMenu->getChildrenCount() - 1, "info-button") : nullptr;
            if (infoBtn) infoBtn->setLayoutOptions(AnchorLayoutOptions::create()
                ->setAnchor(Anchor::TopLeft)
                ->setOffset({-2, 0}));
            auto menu = detachAndCreateMenu(m_mainLayer->getChildByID("toggle-holder")
                , numToString(id).c_str(), AnchorLayout::create(),
                toggler,
                label,
                infoBtn
                );
            menu->setTag(id);
            menu->setContentSize({175, 30});
            menu->setAnchorPoint({0, .5});
            menu->setPositionX(menu->getPositionX() - 15);
            menu->giveMenuTouchPriority(-506);
            menu->updateLayout();
        }


    }
};
