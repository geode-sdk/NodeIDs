#include <Geode/Geode.hpp>

#if GEODE_COMP_GD_VERSION >= 22090

#include <Geode/modify/InvitesPopup.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(InvitesPopup) {
    m_mainLayer->setID("main-layer");

    setIDs(
        m_mainLayer,
        0,
        "background",
        "main-menu",
        "title-label",
        "status-label",
        "scroll-bg",
        "scroll-layer",
        "search-bg",
        "search-input"
    );
    if (auto loadingCircle = m_mainLayer->getChildByType<LoadingCircle>(0)) {
        loadingCircle->setID("loading-circle");
    }

    setIDs(
        m_buttonMenu,
        0,
        "close-button",
        "prev-page-button",
        "next-page-button",
        "ignored-button",
        "info-button",
        "clear-search-button"
    );

    verifyIDSafe(m_buttonMenu, "main-menu");

    auto winSize = CCDirector::get()->getWinSize();

    auto searchMenu = CCMenu::create();
    searchMenu->setLayout(
        RowLayout::create()
            ->setGap(4.f)
            ->setAxisAlignment(AxisAlignment::Center)
            ->setAxisReverse(false)
            ->ignoreInvisibleChildren(false)
    );
    searchMenu->setID("search-menu");
    searchMenu->setPosition({ winSize.width / 2, (winSize.height / 2) + 85.f });
    searchMenu->setContentSize({ 232.f, 24.f });
    searchMenu->setZOrder(10);
    m_mainLayer->addChild(searchMenu);

    if (auto bg = m_mainLayer->getChildByID("search-bg")) {
        auto field = CCNode::create();
        field->setID("search-field");
        field->setAnchorPoint({ 0.5f, 0.5f });
        field->setContentSize(bg->getScaledContentSize());
        field->setPosition(bg->getPosition());
        m_mainLayer->addChild(field);

        switchToMenu(bg, field);
        switchToMenu(m_mainLayer->getChildByID("search-input"), field);
        switchToMenu(field, searchMenu);
    }

    switchToMenu(m_buttonMenu->getChildByID("clear-search-button"), searchMenu);
    searchMenu->updateLayout();

    handleTouchPriority(this);
}

struct InvitesPopupIDs : Modify<InvitesPopupIDs, InvitesPopup> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("InvitesPopup::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set InvitesPopup::init hook priority, node IDs may not work properly");
        }
    }

    bool init() {
        if (!InvitesPopup::init()) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};

#endif
