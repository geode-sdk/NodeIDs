#include "IDCheck.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/FriendRequestPopup.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(FriendRequestPopup) {
    m_mainLayer->setID("main-layer");

    setIDs(
        m_mainLayer,
        0,
        "background",
        "main-menu",
        "title-label",
        "username-label",
        "loading-circle",
        "description-background",
        "description-area"
    );

    if (!m_request->m_uploadDate.empty()) {
        setIDSafe(m_mainLayer, 8, "date-label");
    }

    size_t btnIdx = 0;
    setIDSafe<CCMenuItemSpriteExtra>(m_buttonMenu, btnIdx++, "close-button");

    if (!m_sent && !m_request->m_message.empty()) {
        setIDSafe<CCMenuItemSpriteExtra>(m_buttonMenu, btnIdx++, "report-button");
    }

    if (m_sent) {
        setIDSafe<CCMenuItemSpriteExtra>(m_buttonMenu, btnIdx++, "remove-button");
    } else {
        setIDSafe<CCMenuItemSpriteExtra>(m_buttonMenu, btnIdx++, "accept-button");

        if (!m_request->m_isRead) {
            setIDSafe<CCMenuItemSpriteExtra>(m_buttonMenu, btnIdx++, "remove-button");
        }

        setIDSafe<CCMenuItemSpriteExtra>(m_buttonMenu, btnIdx++, "block-button");
    }

    verifyIDSafe(m_buttonMenu, "main-menu");
    verifyIDSafe(m_circle, "loading-circle");
    verifyIDSafe(m_closeBtn, "close-button");

    auto winSize = CCDirector::sharedDirector()->getWinSize();

    auto bottomMenu = CCMenu::create();
    bottomMenu->setLayout(
        RowLayout::create()
            ->setGap(14.f)
            ->setAxisAlignment(AxisAlignment::Center)
    );
    bottomMenu->setID("bottom-menu");
    bottomMenu->setContentSize({ 335.f, 30.f });
    bottomMenu->setPosition(winSize / 2 + CCPoint { 0.f, -73.f });
    bottomMenu->setZOrder(10);
    m_mainLayer->addChild(bottomMenu);

    switchToMenu(m_buttonMenu->getChildByID("accept-button"), bottomMenu);
    switchToMenu(m_buttonMenu->getChildByID("remove-button"), bottomMenu);
    switchToMenu(m_buttonMenu->getChildByID("block-button"), bottomMenu);

    bottomMenu->updateLayout();

    handleTouchPriority(this);
}

struct FriendRequestPopupIDs : Modify<FriendRequestPopupIDs, FriendRequestPopup> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("FriendRequestPopup::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set FriendRequestPopup::init hook priority, node IDs may not work properly");
        }
    }

    bool init(GJFriendRequest* request, bool sent) {
        if(!FriendRequestPopup::init(request, sent)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};