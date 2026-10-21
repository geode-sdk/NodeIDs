#include <Geode/Geode.hpp>
#include <Geode/modify/FriendsProfilePage.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(FriendsProfilePage) {
    m_mainLayer->setID("main-layer");

    setIDs(
        m_mainLayer,
        0,
        "background",
        "main-menu",
        "title-label",
        "search-bar-bg",
        "search-input",
        "total-friends-label",
        "list-layer"
    );
    if (auto loadingCircle = m_mainLayer->getChildByType<LoadingCircle>(0)) {
        loadingCircle->setID("loading-circle");
    }

    size_t buttonIdx = 0;
    setIDSafe(m_buttonMenu, buttonIdx++, "back-button");
    if(static_cast<int>(m_type) == 3) setIDSafe(m_buttonMenu, buttonIdx++, "info-button");
    setIDs(
        m_buttonMenu,
        buttonIdx,
        "friends-button",
        "blocked-button",
        "following-button",
        "muted-button"
    );
    buttonIdx += 4;
    if(m_type != UserListType::Blocked) {
        setIDs(
            m_buttonMenu,
            buttonIdx,
            "search-button",
            "clear-search-button",
            "sort-button",
            "sort-direction-button"
        );
        buttonIdx += 4;
    }
    setIDSafe(m_buttonMenu, buttonIdx++, "refresh-button");

    //sanity checks
    verifyIDSafe(m_buttonMenu, "main-menu");

    //menu gaming
    auto winSize = CCDirector::get()->getWinSize();

    auto bottomRightMenu = CCMenu::create();
    bottomRightMenu->setPosition((winSize.width / 2) + 233, (winSize.height / 2) - (160 - 2.25f));
    bottomRightMenu->setID("bottom-right-menu");
    bottomRightMenu->setAnchorPoint({1, 0});
    bottomRightMenu->setZOrder(1);
    bottomRightMenu->setContentSize({ 130.f, 0.f });
    bottomRightMenu->setLayout(
        RowLayout::create()
            ->setAxisAlignment(AxisAlignment::End)
            ->setCrossAxisAlignment(AxisAlignment::Start)
            ->setAxisReverse(true)
            ->setGap(8.f)
            ->ignoreInvisibleChildren(false)
    );
    switchToMenu(m_buttonMenu->getChildByID("refresh-button"), bottomRightMenu);
    bottomRightMenu->updateLayout();
    m_mainLayer->addChild(bottomRightMenu);

    auto sortBtn = m_buttonMenu->getChildByID("sort-button");
    auto sortDirBtn = m_buttonMenu->getChildByID("sort-direction-button");
    auto sortWidth = sortBtn ? sortBtn->getScaledContentSize().width : 0.f;
    auto sortDirWidth = sortDirBtn ? sortDirBtn->getScaledContentSize().width : 0.f;

    auto bottomLeftMenu = CCMenu::create();
    bottomLeftMenu->setPosition((winSize.width / 2) - 181 - sortWidth / 2, (winSize.height / 2) - 122);
    bottomLeftMenu->setID("bottom-left-menu");
    bottomLeftMenu->setAnchorPoint({0, 0.5f});
    bottomLeftMenu->setZOrder(1);
    bottomLeftMenu->setContentSize({ 130.f, 30.f });
    bottomLeftMenu->setLayout(
        RowLayout::create()
            ->setAxisAlignment(AxisAlignment::Start)
            ->setAxisReverse(false)
            ->setGap(43.f - (sortWidth + sortDirWidth) / 2)
            ->ignoreInvisibleChildren(false)
    );
    switchToMenu(sortBtn, bottomLeftMenu);
    switchToMenu(sortDirBtn, bottomLeftMenu);
    bottomLeftMenu->updateLayout();
    m_mainLayer->addChild(bottomLeftMenu);

    auto topRightMenu = CCMenu::create();
    topRightMenu->setPosition((winSize.width / 2) + 212.3f, (winSize.height / 2) + 137.2f);
    topRightMenu->setID("top-right-menu");
    topRightMenu->setAnchorPoint({1, 1});
    topRightMenu->setZOrder(1);
    topRightMenu->setContentSize({ 130.f, 0.f });
    topRightMenu->setLayout(
        RowLayout::create()
            ->setAxisAlignment(AxisAlignment::End)
            ->setCrossAxisAlignment(AxisAlignment::End)
            ->setAxisReverse(true)
            ->setGap(8.f)
    );
    switchToMenu(m_buttonMenu->getChildByID("info-button"), topRightMenu);
    topRightMenu->updateLayout();
    m_mainLayer->addChild(topRightMenu);

    auto topLeftMenu = CCMenu::create();
    topLeftMenu->setPosition((winSize.width / 2) - 234.75f, (winSize.height / 2) + 160.5f);
    topLeftMenu->setID("top-left-menu");
    topLeftMenu->setAnchorPoint({0, 1});
    topLeftMenu->setZOrder(1);
    topLeftMenu->setContentSize({ 130.f, 0.f });
    topLeftMenu->setLayout(
        RowLayout::create()
            ->setAxisAlignment(AxisAlignment::Start)
            ->setCrossAxisAlignment(AxisAlignment::End)
            ->setAxisReverse(false)
            ->setGap(8.f)
    );
    switchToMenu(m_buttonMenu->getChildByID("back-button"), topLeftMenu);
    topLeftMenu->updateLayout();
    m_mainLayer->addChild(topLeftMenu);

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
    leftMenu->setContentSize({ 35.f, 146.f });
    leftMenu->setZOrder(10);
    m_mainLayer->addChild(leftMenu);

    switchToMenu(m_buttonMenu->getChildByID("friends-button"), leftMenu);
    switchToMenu(m_buttonMenu->getChildByID("blocked-button"), leftMenu);
    switchToMenu(m_buttonMenu->getChildByID("following-button"), leftMenu);
    switchToMenu(m_buttonMenu->getChildByID("muted-button"), leftMenu);
    leftMenu->updateLayout();

    auto topMenu = CCMenu::create();
    topMenu->setLayout(
        RowLayout::create()
            ->setGap(4.f)
            ->setAxisAlignment(AxisAlignment::Center)
            ->setAxisReverse(false)
    );
    topMenu->setID("top-menu");
    topMenu->setPosition({ winSize.width / 2, (winSize.height / 2) + 100.f });
    topMenu->setContentSize({ 262.f, 24.f });
    topMenu->setZOrder(10);
    m_mainLayer->addChild(topMenu);

    if (auto bg = m_mainLayer->getChildByID("search-bar-bg")) {
        auto searchBar = CCNode::create();
        searchBar->setID("search-bar");
        searchBar->setAnchorPoint({ 0.5f, 0.5f });
        searchBar->setContentSize(bg->getScaledContentSize());
        searchBar->setPosition(bg->getPosition());
        m_mainLayer->addChild(searchBar);

        switchToMenu(bg, searchBar);
        switchToMenu(m_mainLayer->getChildByID("search-input"), searchBar);
        switchToMenu(searchBar, topMenu);
    }
    switchToMenu(m_buttonMenu->getChildByID("search-button"), topMenu);
    switchToMenu(m_buttonMenu->getChildByID("clear-search-button"), topMenu);
    topMenu->updateLayout();

    handleTouchPriority(this);
}

struct FriendsProfilePageIDs : Modify<FriendsProfilePageIDs, FriendsProfilePage> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("FriendsProfilePage::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set FriendsProfilePage::init hook priority, node IDs may not work properly");
        }
    }

    bool init(UserListType type) {
        if (!FriendsProfilePage::init(type)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};
