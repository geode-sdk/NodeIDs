#include <Geode/Geode.hpp>

#include <Geode/modify/CustomizeObjectLayer.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(CustomizeObjectLayer) {
    auto winSize = CCDirector::get()->getWinSize();

    setIDs(
        m_mainLayer, 0,
        "alert-bg",
        "title-label",
        "button-menu",
        "selected-channel-label",
        "channel-input-bg",
        "channel-input",
        "kerning-label",
        "kerning-slider",
        "text-input-bg",
        "text-input"
    );

    m_buttonMenu->setID("ok-menu");

    setIDs(
        m_buttonMenu,
        0,
        "ok-button",
        "info-button",
        // 2
        "base-tab-button",
        "detail-tab-button",
        "settings-button",
        "base-hsv-button",
        "detail-hsv-button",
        // 8
        "player-color-1-button",
        "player-color-2-button",
        "light-bg-button",
        "default-button",
        "channel-1-button",
        "channel-2-button",
        "channel-3-button",
        "channel-4-button",
        "channel-5-button",
        "channel-6-button",
        "channel-7-button",
        "channel-8-button",
        "channel-9-button",
        "channel-custom-button",
        // 22
        "select-channel-up-button",
        "select-channel-down-button",
        "select-channel-button",
        "live-color-select-button"
    );

    int idOffset = 25;

    // Text object and counter object
    if (m_targetObject && (m_targetObject->m_objectID == 914 || m_targetObject->m_objectID == 1615)) {
        setIDs(
            m_buttonMenu,
            idOffset,
            "text-tab-button",
            "split-text-button",
            "clear-text-button",
            "next-free-button"
        );
        idOffset += 4;
    }
    else {
        setIDs(
            m_buttonMenu,
            idOffset,
            "next-free-button"
        );
        idOffset += 1;
    }

    if (m_targetObject) {
        setIDs(
            m_buttonMenu,
            idOffset,
            "copy-button",
            "paste-button",
            "browse-button"
        );
        idOffset += 3;
    }
    else {
        //if LevelEditorLayer::canPasteState
        if(auto btn = typeinfo_cast<CCMenuItemSpriteExtra*>(m_buttonMenu->getChildren()->objectAtIndex(idOffset))) {
            if(auto label = typeinfo_cast<ButtonSprite*>(btn->getNormalImage())) {
                if(std::string_view(label->m_label->getString()) == "Paste") {
                    setIDs(
                        m_buttonMenu,
                        idOffset,
                        "paste-button"
                    );
                    idOffset += 1;
                }
            }
        }
        setIDs(
            m_buttonMenu,
            idOffset,
            "browse-button"
        );
        idOffset += 1;
    }

    auto tabsLayout = RowLayout::create()
        ->setAxisAlignment(AxisAlignment::Center)
        ->setCrossAxisAlignment(AxisAlignment::Center);
    tabsLayout->ignoreInvisibleChildren(true);
    auto tabsMenu = detachAndCreateMenu(
        m_mainLayer,
        "tabs-menu",
        tabsLayout,
        m_buttonMenu->getChildByID("base-tab-button"),
        m_buttonMenu->getChildByID("detail-tab-button"),
        m_buttonMenu->getChildByID("settings-button"),
        SpacerNode::create(),
        m_buttonMenu->getChildByID("text-tab-button")
    );
    tabsMenu->setContentSize({ 360.f, 50.f });
    tabsMenu->setPositionX(winSize.width / 2);
    tabsMenu->updateLayout();

    auto specialChannelsMenu = detachAndCreateMenu(
        m_mainLayer,
        "special-channels-menu",
        RowLayout::create()
            ->setCrossAxisOverflow(false)
            ->setGrowCrossAxis(true)
            ->setAxisAlignment(AxisAlignment::Center)
            ->setCrossAxisAlignment(AxisAlignment::Center)
            ->setGap(18.f),
        m_buttonMenu->getChildByID("player-color-1-button"),
        m_buttonMenu->getChildByID("player-color-2-button"),
        m_buttonMenu->getChildByID("light-bg-button"),
        m_buttonMenu->getChildByID("default-button")
    );
    specialChannelsMenu->setContentSize({ 350.f, 50.f });
    specialChannelsMenu->setPositionX(winSize.width / 2);
    specialChannelsMenu->updateLayout();

    auto channelsMenu = detachAndCreateMenu(
        m_mainLayer,
        "channels-menu",
        RowLayout::create()
            ->setCrossAxisOverflow(false)
            ->setGrowCrossAxis(true)
            ->setAxisAlignment(AxisAlignment::Center)
            ->setCrossAxisAlignment(AxisAlignment::Center)
            ->setGap(17.f),
        m_buttonMenu->getChildByID("channel-1-button"),
        m_buttonMenu->getChildByID("channel-2-button"),
        m_buttonMenu->getChildByID("channel-3-button"),
        m_buttonMenu->getChildByID("channel-4-button"),
        m_buttonMenu->getChildByID("channel-5-button"),
        m_buttonMenu->getChildByID("channel-6-button"),
        m_buttonMenu->getChildByID("channel-7-button"),
        m_buttonMenu->getChildByID("channel-8-button"),
        m_buttonMenu->getChildByID("channel-9-button"),
        m_buttonMenu->getChildByID("channel-custom-button")
    );
    channelsMenu->setContentSize({ 330.f, 100.f });
    channelsMenu->setPosition(winSize.width / 2, winSize.height / 2 - 20.f);
    channelsMenu->updateLayout();

    auto selectedChannelMenu = detachAndCreateMenu(
        m_mainLayer,
        "selected-channel-menu",
        nullptr,
        m_buttonMenu->getChildByID("select-channel-button"),
        m_mainLayer->getChildByID("selected-channel-label")
    );
    selectedChannelMenu->setContentSize({ 120.f, 40.f });
    selectedChannelMenu->setPosition(
        winSize.width / 2 + 115.f,
        winSize.height / 2 - 93.f
    );
    if (auto label = selectedChannelMenu->getChildByID("selected-channel-label")) {
        label->setPosition(75.f, 22.f);
    }
    if (auto button = selectedChannelMenu->getChildByID("select-channel-button")) {
        button->setPosition(100.f, 20.f);
    }

    auto togglesMenu = CCMenu::create();
    togglesMenu->setID("toggles-menu");
    togglesMenu->setLayout(ColumnLayout::create());
    togglesMenu->setContentSize({ 75.f, 120.f });
    togglesMenu->setPosition(55.f, 90.f);
    m_mainLayer->addChild(togglesMenu);

    auto baseHSVMenu = detachAndCreateMenu(
        m_mainLayer,
        "base-hsv-menu",
        RowLayout::create()
            ->setAxisAlignment(AxisAlignment::Start),
        m_buttonMenu->getChildByID("base-hsv-button")
    );
    baseHSVMenu->setContentSize({ 80.f, 60.f });
    baseHSVMenu->setPositionX(winSize.width / 2 - 131.5f);
    baseHSVMenu->updateLayout();

    auto detailHSVMenu = detachAndCreateMenu(
        m_mainLayer,
        "detail-hsv-menu",
        RowLayout::create()
            ->setAxisAlignment(AxisAlignment::Start),
        m_buttonMenu->getChildByID("detail-hsv-button")
    );
    detailHSVMenu->setContentSize({ 80.f, 60.f });
    detailHSVMenu->setPositionX(baseHSVMenu->getPositionX());
    detailHSVMenu->updateLayout();

    auto nextFreeMenu = detachAndCreateMenu(
        m_mainLayer,
        "next-free-menu",
        RowLayout::create()
            ->setAxisAlignment(AxisAlignment::Start),
        m_buttonMenu->getChildByID("next-free-button")
    );
    nextFreeMenu->setContentSize({ 120.f, 60.f });
    nextFreeMenu->setPositionX(winSize.width / 2 - 111.f);
    nextFreeMenu->updateLayout();

    auto textActionsMenu = detachAndCreateMenu(
        m_mainLayer,
        "text-actions-menu",
        RowLayout::create()
            ->setAxisAlignment(AxisAlignment::End)
            ->setAxisReverse(true),
        m_buttonMenu->getChildByID("split-text-button")
    );
    textActionsMenu->setContentSize({ 120.f, 60.f });
    textActionsMenu->setPositionX(winSize.width / 2 + 112.f);
    textActionsMenu->updateLayout();

    if(auto clearTextMenu = detachAndCreateMenu(
        m_mainLayer,
        "clear-text-menu",
        nullptr,
        m_buttonMenu->getChildByID("clear-text-button")
    )) {
        //the position being incorrect has something to do with anchor points and ignoreAnchorPointForPosition
        //if the anchor point of the menu was {1,0} and it actually worked, it'd be correct
        //but that's not what's happening so whatever
        //dont care enough, this fixes it
        if(auto btn = clearTextMenu->getChildByID("clear-text-button")) btn->setPosition({winSize / 2});
    }

    auto infoMenu = detachAndCreateMenu(
        m_mainLayer,
        "info-menu",
        RowLayout::create()
            ->setAxisAlignment(AxisAlignment::End)
            ->setAxisReverse(true),
        m_buttonMenu->getChildByID("info-button")
    );
    infoMenu->setContentSize({ 80.f, 60.f });
    infoMenu->setPosition(winSize.width / 2 + 133.5f, baseHSVMenu->getPositionY() + 7.f);
    infoMenu->updateLayout();

    auto browseMenu = detachAndCreateMenu(
        m_mainLayer,
        "browse-menu",
        ColumnLayout::create()
            ->setAxisAlignment(AxisAlignment::Start)
            ->setAxisReverse(true),
        m_buttonMenu->getChildByID("browse-button")
    );
    browseMenu->setContentSize({ 100.f, 140.f });
    browseMenu->setPositionY(winSize.height / 2 - 67.5f);
    browseMenu->updateLayout();

    auto copyPasteMenu = detachAndCreateMenu(
        m_mainLayer,
        "copy-paste-menu",
        ColumnLayout::create()
            ->setAxisAlignment(AxisAlignment::End)
            ->setAxisReverse(false)
            ->setGap(6.f),
        m_buttonMenu->getChildByID("paste-button"),
        m_buttonMenu->getChildByID("copy-button")
    );
    copyPasteMenu->setContentSize({ 100.f, 140.f });
    copyPasteMenu->setPositionY(winSize.height / 2 + 99.5f);
    copyPasteMenu->updateLayout();

    auto selectChannelMenu = detachAndCreateMenu(
        m_mainLayer,
        "select-channel-menu",
        nullptr,
        m_buttonMenu->getChildByID("select-channel-up-button"),
        m_buttonMenu->getChildByID("select-channel-down-button")
    );
    selectChannelMenu->setPosition(m_customColorInputBG->getPosition());
    selectChannelMenu->setContentSize({ 60.f, 140.f });
    if (auto btn = selectChannelMenu->getChildByID("select-channel-up-button")) {
        btn->setPosition({ 30.f, 110.f });
    }
    if (auto btn = selectChannelMenu->getChildByID("select-channel-down-button")) {
        btn->setPosition({ 30.f, 30.f });
    }
}

struct CustomizeObjectLayerIDs : Modify<CustomizeObjectLayerIDs, CustomizeObjectLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("CustomizeObjectLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set CustomizeObjectLayer::init hook priority, node IDs may not work properly");
        }
    }

    void toggleMenuIf(const char* id, int mode) {
        if (auto menu = m_mainLayer->getChildByID(id)) {
            menu->setVisible(m_selectedMode == mode);
        }
    }

    void toggleMenuIfNot(const char* id, int mode) {
        if (auto menu = m_mainLayer->getChildByID(id)) {
            menu->setVisible(m_selectedMode != mode);
        }
    }

    void toggleVisible() {
        CustomizeObjectLayer::toggleVisible();
        // have to manually toggle menu visibility to allow touches being correctly passed
        this->toggleMenuIf("base-hsv-menu", 1);
        this->toggleMenuIf("detail-hsv-menu", 2);
        this->toggleMenuIf("text-actions-menu", 3);
        this->toggleMenuIf("clear-text-menu", 3);
        this->toggleMenuIfNot("next-free-menu", 3);
        this->toggleMenuIfNot("toggles-menu", 3);
        this->toggleMenuIfNot("channels-menu", 3);
        this->toggleMenuIfNot("special-channels-menu", 3);
        this->toggleMenuIfNot("selected-channel-menu", 3);
        //this->toggleMenuIfNot("browse-menu", 3); //rob leaves these 2 visible in text input mode even though it doesnt make much sense
        //this->toggleMenuIfNot("copy-paste-menu", 3);
        this->toggleMenuIfNot("select-channel-menu", 3);
    }

    bool init(GameObject* obj, CCArray* objs) {
        if (!CustomizeObjectLayer::init(obj, objs))
            return false;

        NodeIDs::get()->provide(this);
        this->toggleVisible();

        handleTouchPriority(this);

        return true;
    }
};
