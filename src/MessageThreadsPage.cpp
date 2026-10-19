#include <Geode/Geode.hpp>

#if GEODE_COMP_GD_VERSION >= 22090

#include <Geode/modify/MessageThreadsPage.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(MessageThreadsPage) {
    m_mainLayer->setID("main-layer");

    setIDs(
        m_mainLayer,
        0,
        "background",
        "title-label",
        "main-menu",
        "search-bar-bg",
        "search-input",
        "loading-circle",
        "error-label",
        "page-label",
        "selection-strip",
        "selected-count-label",
        "invites-label"
    );

    setIDs(
        m_buttonMenu,
        0,
        "info-button",
        "back-button",
        "legacy-button",
        "new-thread-button",
        "search-button",
        "clear-search-button",
        "user-search-button",
        "all-filter-button",
        "dm-filter-button",
        "group-filter-button",
        "prev-page-button",
        "next-page-button",
        "refresh-button",
        "scroll-to-top-button",
        "select-all-button",
        "mark-read-button",
        "delete-button",
        "invites-button"
    );

    if (auto userSearchBtn = static_cast<CCMenuItemSpriteExtra*>(m_buttonMenu->getChildByID("user-search-button"))) {
        if (auto label = userSearchBtn->getNormalImage()->getChildByType<CCLabelBMFont>(0)) {
            label->setID("user-count-label");
        }
    }

    if (auto invitesBtn = static_cast<CCMenuItemSpriteExtra*>(m_buttonMenu->getChildByID("invites-button"))) {
        if (auto badge = invitesBtn->getNormalImage()->getChildByType<CCSprite>(0)) {
            badge->setID("invites-badge");
            if (auto label = badge->getChildByType<CCLabelBMFont>(0)) {
                label->setID("invites-count-label");
            }
        }
    }

    verifyIDSafe(m_buttonMenu, "main-menu");

    auto winSize = CCDirector::get()->getWinSize();

    auto leftMenu = CCMenu::create();
    leftMenu->setLayout(
        ColumnLayout::create()
            ->setGap(2.f)
            ->setAxisAlignment(AxisAlignment::End)
            ->setAxisReverse(true)
    );
    leftMenu->setID("left-menu");
    leftMenu->setAnchorPoint({ 0.5f, 1.f });
    leftMenu->setPosition({ (winSize.width / 2) - 194.f, (winSize.height / 2) + 85.5f });
    leftMenu->setContentSize({ 35.f, 183.f });
    leftMenu->setZOrder(10);
    m_mainLayer->addChild(leftMenu);

    switchToMenu(m_buttonMenu->getChildByID("all-filter-button"), leftMenu);
    switchToMenu(m_buttonMenu->getChildByID("dm-filter-button"), leftMenu);
    switchToMenu(m_buttonMenu->getChildByID("group-filter-button"), leftMenu);
    leftMenu->updateLayout();

    auto selectMenu = CCMenu::create();
    selectMenu->setLayout(
        RowLayout::create()
            ->setGap(7.25f)
            ->setAxisAlignment(AxisAlignment::Start)
            ->setAxisReverse(false)
            ->ignoreInvisibleChildren(false)
    );
    selectMenu->setID("select-menu");
    selectMenu->setAnchorPoint({ 0.f, 0.5f });
    selectMenu->setPosition({ (winSize.width / 2) - 151.f, (winSize.height / 2) - 129.f });
    selectMenu->setContentSize({ 66.f, 28.f });
    selectMenu->setZOrder(10);
    m_mainLayer->addChild(selectMenu);

    switchToMenu(m_buttonMenu->getChildByID("mark-read-button"), selectMenu);
    switchToMenu(m_buttonMenu->getChildByID("delete-button"), selectMenu);
    selectMenu->updateLayout();

    auto topMenu = CCMenu::create();
    topMenu->setLayout(
        RowLayout::create()
            ->setGap(4.f)
            ->setAxisAlignment(AxisAlignment::Start)
            ->setAxisReverse(false)
    );
    topMenu->setID("top-menu");
    topMenu->setAnchorPoint({ 0.f, 0.5f });
    topMenu->setPosition({ (winSize.width / 2) - 16.f, (winSize.height / 2) + 105.f });
    topMenu->setContentSize({ 186.f, 21.f });
    topMenu->setZOrder(10);
    m_mainLayer->addChild(topMenu);

    switchToMenu(m_buttonMenu->getChildByID("search-button"), topMenu);
    switchToMenu(m_buttonMenu->getChildByID("clear-search-button"), topMenu);
    if (auto userSearchBtn = m_buttonMenu->getChildByID("user-search-button")) {
        userSearchBtn->setLayoutOptions(AxisLayoutOptions::create()->setPrevGap(14.5f));
        switchToMenu(userSearchBtn, topMenu);
    }
    if (auto newThreadBtn = m_buttonMenu->getChildByID("new-thread-button")) {
        newThreadBtn->setLayoutOptions(AxisLayoutOptions::create()->setPrevGap(28.f));
        switchToMenu(newThreadBtn, topMenu);
    }
    topMenu->updateLayout();

    auto bottomRightMenu = CCMenu::create();
    bottomRightMenu->setLayout(
        ColumnLayout::create()
            ->setAxisAlignment(AxisAlignment::Start)
            ->setAxisReverse(false)
            ->ignoreInvisibleChildren(false)
    );
    bottomRightMenu->setID("bottom-right-menu");
    bottomRightMenu->setAnchorPoint({ 0.5f, 0.f });
    bottomRightMenu->setPosition({ (winSize.width / 2) + 196.f, (winSize.height / 2) - 143.f });
    bottomRightMenu->setContentSize({ 37.f, 100.f });
    bottomRightMenu->setZOrder(10);
    m_mainLayer->addChild(bottomRightMenu);

    switchToMenu(m_buttonMenu->getChildByID("refresh-button"), bottomRightMenu);
    bottomRightMenu->updateLayout();

    handleTouchPriority(this);
}

struct MessageThreadsPageIDs : Modify<MessageThreadsPageIDs, MessageThreadsPage> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("MessageThreadsPage::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set MessageThreadsPage::init hook priority, node IDs may not work properly");
        }
    }

    bool init() {
        if (!MessageThreadsPage::init()) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};

#endif
