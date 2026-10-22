#include <Geode/Geode.hpp>
#include <Geode/modify/SetGroupIDLayer.hpp>
#include <Geode/utils/NodeIDs.hpp>
#include <Geode/ui/TextInput.hpp>
#include "Spacer.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

static void createToggleContainer(FLAlertLayer* popup, CCNode* parent, ZStringView ID) {
    auto label = setIDSafe<CCLabelBMFont>(popup, 0, fmt::format("{}-label", ID).c_str());
    auto toggle = setIDSafe<CCMenuItemToggler>(popup->m_buttonMenu, 0, fmt::format("{}-toggle", ID).c_str());

    if (!label || !toggle) return;

    detachAndCreateMenu(
        parent, 
        fmt::format("{}-container", ID).c_str(), 
        SimpleColumnLayout::create()
            ->setGap(3.f)
            ->setMainAxisScaling(AxisScaling::Fit)
            ->setCrossAxisScaling(AxisScaling::Fit), 
        label, 
        toggle
    );
}

template <typename T, typename... Args>
static CCMenu* createInputContainer(CCNode* parent, char const* menuID, CCSize size, CCPoint offset, T first, Args... args) {
    if (!first) return nullptr;

    auto container = detachAndCreateMenu(parent, menuID, nullptr, first, args...);
    first->setZOrder(1);

    for (auto child : container->getChildrenExt()) {
        child->setPosition(child->getPosition() - container->getContentSize() + size / 2.f - offset);
    }

    container->setContentSize(size);
    container->setPosition(container->getPosition() + offset);

    return container;
}

static CCNode* getActionButton(CCNode* parent, ZStringView ID) {
    auto node = parent->getChildByID(ID);
    if (!node) {
        node = Spacer::create({36.f, 25.f});
        parent->addChild(node);
    }
    return node;
}

$register_ids(SetGroupIDLayer) {
    auto winSize = CCDirector::get()->getWinSize();

    m_buttonMenu->setID("main-menu");
    m_mainLayer->setID("main-layer");

    auto background = setIDSafe<CCScale9Sprite>(m_mainLayer, 0, "background");
    auto groupBG = setIDSafe<CCScale9Sprite>(m_mainLayer, 1, "groups-bg");
    auto editorLayerInputBG = setIDSafe<CCScale9Sprite>(m_mainLayer, 2, "editor-layer-input-bg");
    auto editorLayer2InputBG = setIDSafe<CCScale9Sprite>(m_mainLayer, 3, "editor-layer-2-input-bg");
    auto addGroupIDInputBG = setIDSafe<CCScale9Sprite>(m_mainLayer, 4, "add-group-id-input-bg");
    auto zOrderInputBG = setIDSafe<CCScale9Sprite>(m_mainLayer, 5, "z-order-input-bg");
    auto channelOrderInputBG = setIDSafe<CCScale9Sprite>(m_mainLayer, 6, "channel-order-input-bg");
    auto channelInputBG = setIDSafe<CCScale9Sprite>(m_mainLayer, 7, "channel-input-bg");

    auto editorLayerLabel = setIDSafe<CCLabelBMFont>(m_mainLayer, 0, "editor-layer-label");
    auto editorLayer2Label = setIDSafe<CCLabelBMFont>(m_mainLayer, 1, "editor-layer-2-label");
    auto addGroupIDLabel = setIDSafe<CCLabelBMFont>(m_mainLayer, 2, "add-group-id-label");
    auto zOrderLabel = setIDSafe<CCLabelBMFont>(m_mainLayer, 3, "z-order-label");
    auto zLayerLabel = setIDSafe<CCLabelBMFont>(m_mainLayer, 4, "z-layer-label");

    auto idNameInput = setIDSafe<IDNameInput>(m_mainLayer, 0, "id-name-input");
    auto groupList = setIDSafe<ScrollableContentLayer>(m_mainLayer, 0, "group-list-scroll-layer");

    auto groupNameLabel = setIDSafe<CCLabelBMFont>(m_mainLayer, 5, "group-name-label");
    auto groupNameLabelShadow = setIDSafe<CCLabelBMFont>(m_mainLayer, 6, "group-name-label-shadow");
    auto drawOrderLabel = setIDSafe<CCLabelBMFont>(m_mainLayer, 7, "draw-order-label");

    if (m_editorLayerInput) m_editorLayerInput->setID("editor-layer-input");
    if (m_editorLayer2Input) m_editorLayer2Input->setID("editor-layer-2-input");
    if (m_zOrderInput) m_zOrderInput->setID("z-order-input");
    if (m_groupIDInput) m_groupIDInput->setID("add-group-id-input");
    if (m_orderInput) m_orderInput->setID("channel-order-input");
    if (m_channelInput) m_channelInput->setID("channel-input");

    int offset = 0;

    setIDs(
        m_buttonMenu, &offset,
        "ok-button",
        "editor-layer-next-free-button",
        "editor-layer-2-next-free-button",
        "group-offset-button",
        "info-button",
        "editor-layer-prev-button",
        "editor-layer-next-button",
        "editor-layer-2-prev-button",
        "editor-layer-2-next-button",
        "add-group-id-prev-button",
        "add-group-id-next-button",
        "next-free-button",
        "named-groups-button",
        "add-group-id-button"
    );

    if (m_targetObject) {
        setIDs(m_buttonMenu, &offset, "add-group-parent-button");
    }

    setIDs(
        m_buttonMenu, &offset,
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

    /*
        normally we would check the ZLayer being -100, but this is a temp solution while bindings are broken
        if (m_zLayerValue == static_cast<ZLayer>(-100) && m_targetObjects && m_targetObjects->count() != 0)
    */

    auto zLayerDecrement = setIDSafe<CCMenuItemSpriteExtra>(m_buttonMenu, offset, "z-layer-decrement-button");
    auto zLayerIncrement = setIDSafe<CCMenuItemSpriteExtra>(m_buttonMenu, offset + 1, "z-layer-increment-button");

    auto zLayerDecLabel = zLayerDecrement->getNormalImage()->getChildByType<CCLabelBMFont>();
    if (zLayerDecLabel && std::string_view(zLayerDecLabel->getString()) == "-") {
        offset += 2;
    }
    else {
        zLayerDecrement = nullptr;
        zLayerIncrement = nullptr;
    }

    if (m_showChannelOrder) {
        setIDs(
            m_buttonMenu, &offset,
            "channel-order-prev-button",
            "channel-order-next-button",
            "channel-prev-button",
            "channel-next-button",
            "channel-next-free-button"
        );
    }

    for (int i = offset; i < m_buttonMenu->getChildrenCount(); i++) {
        auto child = m_buttonMenu->getChildrenExt()[i];
        auto btnSpr = child->getChildByType<ButtonSprite>();
        if (!btnSpr) continue;

        auto label = btnSpr->getChildByType<CCLabelBMFont>();
        if (!label) continue;

        auto ID = string::replace(label->getString(), " ", "-");
        string::toLowerIP(ID);

        child->setID(fmt::format("{}-button", ID));
    }

    auto previewMenu = CCMenu::create();
    previewMenu->setID("preview-menu");
    previewMenu->setLayout(SimpleColumnLayout::create()
        ->setGap(6.f)
        ->setCrossAxisScaling(AxisScaling::Fit)
        ->setMainAxisAlignment(MainAxisAlignment::End)
    );
    previewMenu->ignoreAnchorPointForPosition(false);
    previewMenu->setAnchorPoint({0.5f, 0.f});
    previewMenu->setPosition(winSize.width / 2.f + 217.5f, winSize.height / 2.f - 147.f);
    previewMenu->setContentSize({40.f, 150.f});

    m_mainLayer->addChild(previewMenu);

    if (m_targetObject) {
        if (m_targetObject->m_classType == GameObjectClassType::Effect) {
            createToggleContainer(this, previewMenu, "preview");
            createToggleContainer(this, previewMenu, "playback");
            createToggleContainer(this, previewMenu, "trace-out");
            createToggleContainer(this, previewMenu, "trace-in");
        }
        else {
            createToggleContainer(this, previewMenu, "trace-in");
        }

        previewMenu->updateLayout();
    }

    auto actionsMenu = detachAndCreateMenu(
        m_mainLayer,
        "actions-menu",
        SimpleColumnLayout::create()
            ->setGap(5.f)
            ->setCrossAxisScaling(AxisScaling::Fit)
            ->setMainAxisAlignment(MainAxisAlignment::Start),
        getActionButton(m_buttonMenu, "copy-button"),
        getActionButton(m_buttonMenu, "paste-button"),
        getActionButton(m_buttonMenu, "extra-button"),
        getActionButton(m_buttonMenu, "extra2-button"),
        getActionButton(m_buttonMenu, "anim-button")
    );

    actionsMenu->ignoreAnchorPointForPosition(false);
    actionsMenu->setAnchorPoint({0.5f, 1.f});
    actionsMenu->setPosition(winSize.width / 2.f + 217.5f, winSize.height / 2.f + 155.f);
    actionsMenu->setContentSize({40.f, 150.f});
    actionsMenu->updateLayout();

    auto zLayerMenu = detachAndCreateMenu(
        m_mainLayer,
        "z-layer-menu",
        SimpleRowLayout::create()
            ->setGap(5.f)
            ->setCrossAxisScaling(AxisScaling::Fit),
        m_buttonMenu->getChildByID("b5-layer-button"),
        m_buttonMenu->getChildByID("b4-layer-button"),
        m_buttonMenu->getChildByID("b3-layer-button"),
        m_buttonMenu->getChildByID("b2-layer-button"),
        m_buttonMenu->getChildByID("b1-layer-button"),
        m_buttonMenu->getChildByID("t1-layer-button"),
        m_buttonMenu->getChildByID("t2-layer-button"),
        m_buttonMenu->getChildByID("t3-layer-button"),
        m_buttonMenu->getChildByID("t4-layer-button"),
        m_buttonMenu->getChildByID("default-layer-button")
    );
    zLayerMenu->setPosition(winSize.width / 2.f, winSize.height / 2.f - 92.f);
    zLayerMenu->setContentSize({380.f, 60.f});
    zLayerMenu->updateLayout();

    auto okMenu = detachAndCreateMenu(
        m_mainLayer,
        "ok-menu",
        SimpleRowLayout::create()
            ->setGap(5.f)
            ->setCrossAxisScaling(AxisScaling::Fit),
        m_buttonMenu->getChildByID("ok-button")
    );
    okMenu->setPosition(winSize.width / 2.f, winSize.height / 2.f - 146.f);
    okMenu->setAnchorPoint({0.5f, 0.f});
    okMenu->setContentSize({75.f, 60.f});
    okMenu->updateLayout();

    auto infoMenu = detachAndCreateMenu(
        m_mainLayer,
        "info-menu",
        SimpleRowLayout::create()
            ->setGap(5.f)
            ->setCrossAxisScaling(AxisScaling::Fit)
            ->setMainAxisDirection(AxisDirection::RightToLeft)
            ->setMainAxisAlignment(MainAxisAlignment::Start),
        m_buttonMenu->getChildByID("info-button")
    );
    infoMenu->setPosition(winSize.width / 2.f + 188.f, winSize.height / 2.f + 147.f);
    infoMenu->setAnchorPoint({1.f, 1.f});
    infoMenu->setContentSize({30.f, 30.f});
    infoMenu->updateLayout();

    auto layerContainer = createInputContainer(
        m_mainLayer, 
        "editor-layer-container",
        {120.f, 60.f},
        {0.f, 10.f},
        m_editorLayerInput,
        editorLayerLabel,
        editorLayer2InputBG,
        m_buttonMenu->getChildByID("editor-layer-prev-button"),
        m_buttonMenu->getChildByID("editor-layer-next-button"),
        m_buttonMenu->getChildByID("editor-layer-next-free-button")
    );

    auto layer2Container = createInputContainer(
        m_mainLayer, 
        "editor-layer-2-container",
        {120.f, 60.f},
        {0.f, 10.f},
        m_editorLayer2Input,
        editorLayer2Label,
        editorLayer2InputBG,
        m_buttonMenu->getChildByID("editor-layer-2-prev-button"),
        m_buttonMenu->getChildByID("editor-layer-2-next-button"),
        m_buttonMenu->getChildByID("editor-layer-2-next-free-button")
    );

    auto zOrderContainer = createInputContainer(
        m_mainLayer, 
        "z-order-container",
        {120.f, 60.f},
        {0.f, 10.f},
        m_zOrderInput,
        zLayerLabel,
        zOrderInputBG,
        m_buttonMenu->getChildByID("z-order-prev-button"),
        m_buttonMenu->getChildByID("z-order-next-button")
    );

    auto orderContainer = createInputContainer(
        m_mainLayer, 
        "channel-order-container",
        {120.f, 35.f},
        {0.f, 0.f},
        m_orderInput,
        channelOrderInputBG,
        m_buttonMenu->getChildByID("channel-order-prev-button"),
        m_buttonMenu->getChildByID("channel-order-next-button")
    );
    
    auto channelContainer = createInputContainer(
        m_mainLayer, 
        "channel-container",
        {150.f, 35.f},
        {-15.f, 0.f},
        m_channelInput,
        channelInputBG,
        m_buttonMenu->getChildByID("channel-prev-button"),
        m_buttonMenu->getChildByID("channel-next-button"),
        m_buttonMenu->getChildByID("channel-next-free-button")
    );

    auto addGroupContainer = createInputContainer(
        m_mainLayer, 
        "add-group-id-container",
        {170.f, 46.f},
        {0.f, -7.f},
        m_groupIDInput,
        addGroupIDInputBG,
        groupNameLabel,
        groupNameLabelShadow,
        m_buttonMenu->getChildByID("add-group-id-prev-button"),
        m_buttonMenu->getChildByID("add-group-id-next-button"),
        m_buttonMenu->getChildByID("next-free-button"),
        m_buttonMenu->getChildByID("named-groups-button")
    );

    auto addGroupMenu = detachAndCreateMenu(
        m_mainLayer,
        "add-group-menu",
        SimpleRowLayout::create()
            ->setGap(10.f)
            ->setCrossAxisScaling(AxisScaling::Fit),
        m_buttonMenu->getChildByID("add-group-id-button"),
        m_buttonMenu->getChildByID("add-group-parent-button")
    );
    addGroupMenu->setPosition(winSize.width / 2.f + 86.f, winSize.height / 2.f + 49.f);
    addGroupMenu->setContentSize({108.f, 60.f});
    addGroupMenu->updateLayout();

    auto groupOffsetMenu = detachAndCreateMenu(
        m_mainLayer,
        "group-offset-menu",
        SimpleRowLayout::create()
            ->setGap(5.f)
            ->setMainAxisScaling(AxisScaling::Fit)
            ->setMainAxisAlignment(MainAxisAlignment::Start)
            ->setCrossAxisScaling(AxisScaling::ScaleDown),
        m_buttonMenu->getChildByID("group-offset-button")
    );
    groupOffsetMenu->setAnchorPoint({0.f, 0.5f});
    groupOffsetMenu->setPosition(winSize.width / 2.f + 65.f, winSize.height / 2.f + 80.f);
    groupOffsetMenu->setContentSize({20.f, 20.f});
    groupOffsetMenu->updateLayout();

    if (zLayerDecrement && zLayerIncrement) {
        auto zLayerOffsetMenu = detachAndCreateMenu(
            m_mainLayer,
            "z-layer-offset-menu",
            SimpleRowLayout::create()
                ->setGap(zLayerLabel->getScaledContentWidth() + 6.f)
                ->setMainAxisScaling(AxisScaling::Fit)
                ->setCrossAxisScaling(AxisScaling::Fit),
            zLayerDecrement,
            zLayerIncrement
        );
        zLayerOffsetMenu->setPosition(winSize.width / 2.f, winSize.height / 2.f - 66.f);
        zLayerOffsetMenu->updateLayout();
    }
    
    m_buttonMenu->ignoreAnchorPointForPosition(false);
    m_buttonMenu->setPosition(winSize / 2.f);

    setIDSafe<CCLayerColor>(groupList, 0, "scroll-bar");

    auto innerNode = setIDSafe<CCNode>(groupList, 0, "scroll-content");
    if (innerNode) {
        setIDSafe(innerNode, 0, "groups-list-menu");
    }
};

struct SetGroupIDLayerIDs : Modify<SetGroupIDLayerIDs, SetGroupIDLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("SetGroupIDLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set SetGroupIDLayer::init hook priority, node IDs may not work properly");
        }
    }

    bool init(GameObject* obj, CCArray* objs) {
        if (!SetGroupIDLayer::init(obj, objs)) return false;

        NodeIDs::get()->provide(this);
        handleTouchPriority(this);

        return true;
    }
};
