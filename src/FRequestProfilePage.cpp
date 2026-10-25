#include "IDCheck.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/FRequestProfilePage.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(FRequestProfilePage) {
	m_mainLayer->setID("main-layer");

    setIDs(
        m_mainLayer,
        0,
        "background",
        "title-label",
        "search-bar-bg",
        "search-input",
        "page-label",
        "main-menu",
        "loading-circle",
        "selection-strip",
        "selected-count-label",
        "error-label"
    );

    setIDs(
        m_buttonMenu,
        0,
        "back-button",
        "info-button",
        "inbox-button",
        "sent-button",
        "ignored-button",
        "search-button",
        "clear-search-button",
        "select-all-button",
        "mark-read-button",
        "ignore-button",
        "prev-page-button",
        "next-page-button",
        "refresh-button"
    );

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

    switchToMenu(m_buttonMenu->getChildByID("inbox-button"), leftMenu);
    switchToMenu(m_buttonMenu->getChildByID("sent-button"), leftMenu);
    switchToMenu(m_buttonMenu->getChildByID("ignored-button"), leftMenu);
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
    selectMenu->setPosition({ (winSize.width / 2) - 151.f, (winSize.height / 2) - 124.f });
    selectMenu->setContentSize({ 66.f, 28.f });
    selectMenu->setZOrder(10);
    m_mainLayer->addChild(selectMenu);

    switchToMenu(m_buttonMenu->getChildByID("mark-read-button"), selectMenu);
    switchToMenu(m_buttonMenu->getChildByID("ignore-button"), selectMenu);
    selectMenu->updateLayout();

    auto topMenu = CCMenu::create();
    topMenu->setLayout(
        RowLayout::create()
            ->setGap(4.f)
            ->setAxisAlignment(AxisAlignment::Center)
            ->setAxisReverse(false)
    );
    topMenu->setID("top-menu");
    topMenu->setAnchorPoint({ 0.f, 0.5f });
    topMenu->setPosition({ (winSize.width / 2) - 170.f, (winSize.height / 2) + 100.f });
    topMenu->setContentSize({ 340.f, 24.f });
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

    auto bottomRightMenu = CCMenu::create();
    bottomRightMenu->setLayout(
        ColumnLayout::create()
            ->setAxisAlignment(AxisAlignment::Start)
            ->setAxisReverse(false)
            ->ignoreInvisibleChildren(false)
    );

    // 473, 2
    bottomRightMenu->setID("bottom-right-menu");
    bottomRightMenu->setAnchorPoint({ 0.5f, 0.f });
    bottomRightMenu->setPosition({ (winSize.width / 2) + 210.f, (winSize.height / 2) - 158.f });
    bottomRightMenu->setContentSize({ 37.f, 100.f });
    bottomRightMenu->setZOrder(10);
    m_mainLayer->addChild(bottomRightMenu);

    switchToMenu(m_buttonMenu->getChildByID("refresh-button"), bottomRightMenu);
    bottomRightMenu->updateLayout();

    handleTouchPriority(this);
}

struct FRequestProfilePageIDs : Modify<FRequestProfilePageIDs, FRequestProfilePage> {
	static void onModify(auto &self) {
		if (!self.setHookPriority("FRequestProfilePage::init", GEODE_ID_PRIORITY)) {
			log::warn("Failed to set FRequestProfilePage::init hook priority, node IDs may not work properly");
		}
	}

	bool init(bool sentrequest) {
		if (!FRequestProfilePage::init(sentrequest))
			return false;
		NodeIDs::get()->provide(this);
		return true;
	}
};
