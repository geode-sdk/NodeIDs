#include <Geode/Geode.hpp>
#include <Geode/modify/GJMessagePopup.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(GJMessagePopup) {
    m_mainLayer->setID("main-layer");

    setIDs(
        m_mainLayer,
        0,
        "background",
        "main-menu",
        "title-label",
        "user-label",
        "loading-circle",
        "error-label",
        "content-bg"
    );
    if (auto dateLabel = m_mainLayer->getChildByType<CCLabelBMFont>(3)) {
        dateLabel->setID("date-label");
    }

    setIDSafe(m_buttonMenu, 0, "close-button");
    for (auto btn : CCArrayExt<CCMenuItemSpriteExtra*>(m_buttonMenu->getChildren())) {
        if (isSpriteFrameName(btn->getNormalImage(), "GJ_reportBtn_001.png")) {
            btn->setID("report-button");
        }
    }

    verifyIDSafe(m_buttonMenu, "main-menu");

    auto winSize = CCDirector::get()->getWinSize();

    auto topLeftMenu = CCMenu::create();
    topLeftMenu->setLayout(
        RowLayout::create()
            ->setGap(8.f)
            ->setAxisAlignment(AxisAlignment::Start)
            ->setCrossAxisAlignment(AxisAlignment::End)
            ->setAxisReverse(false)
    );
    topLeftMenu->setID("top-left-menu");
    topLeftMenu->setAnchorPoint({ 0.f, 1.f });
    topLeftMenu->setPosition({ (winSize.width / 2) - 223.4f, (winSize.height / 2) + 134.f });
    topLeftMenu->setContentSize({ 130.f, 0.f });
    topLeftMenu->setZOrder(10);
    m_mainLayer->addChild(topLeftMenu);

    switchToMenu(m_buttonMenu->getChildByID("close-button"), topLeftMenu);
    topLeftMenu->updateLayout();

    auto bottomLeftMenu = CCMenu::create();
    bottomLeftMenu->setLayout(
        RowLayout::create()
            ->setGap(8.f)
            ->setAxisAlignment(AxisAlignment::Start)
            ->setCrossAxisAlignment(AxisAlignment::Start)
            ->setAxisReverse(false)
    );
    bottomLeftMenu->setID("bottom-left-menu");
    bottomLeftMenu->setAnchorPoint({ 0.f, 0.f });
    bottomLeftMenu->setPosition({ (winSize.width / 2) - 213.8f, (winSize.height / 2) - 124.25f });
    bottomLeftMenu->setContentSize({ 130.f, 0.f });
    bottomLeftMenu->setZOrder(10);
    m_mainLayer->addChild(bottomLeftMenu);

    switchToMenu(m_buttonMenu->getChildByID("report-button"), bottomLeftMenu);
    bottomLeftMenu->updateLayout();

    auto bottomMenu = CCMenu::create();
    bottomMenu->setLayout(
        RowLayout::create()
            ->setGap(35.f)
            ->setAxisAlignment(AxisAlignment::Center)
            ->setAxisReverse(false)
    );
    bottomMenu->setID("bottom-menu");
    bottomMenu->setPosition({ winSize.width / 2, (winSize.height / 2) - 98.f });
    bottomMenu->setContentSize({ 370.f, 30.f });
    bottomMenu->setZOrder(10);
    m_mainLayer->addChild(bottomMenu);

    switchToMenu(m_buttonMenu->getChildByID("reply-button"), bottomMenu);
    switchToMenu(m_buttonMenu->getChildByID("remove-button"), bottomMenu);
    switchToMenu(m_buttonMenu->getChildByID("block-button"), bottomMenu);
    bottomMenu->updateLayout();

    handleTouchPriority(this);
}

struct GJMessagePopupIDs : Modify<GJMessagePopupIDs, GJMessagePopup> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("GJMessagePopup::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set GJMessagePopup::init hook priority, node IDs may not work properly");
        }
        if (!self.setHookPriority("GJMessagePopup::loadFromGJMessage", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set GJMessagePopup::loadFromGJMessage hook priority, node IDs may not work properly");
        }
    }

    bool init(GJUserMessage* message) {
        if (!GJMessagePopup::init(message)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }

    void loadFromGJMessage(GJUserMessage* message) {
        auto oldCount = m_buttonMenu->getChildrenCount();

        GJMessagePopup::loadFromGJMessage(message);

        if (auto textArea = m_mainLayer->getChildByType<TextArea>(0)) {
            textArea->setID("message-area");
        }

        auto addedCount = m_buttonMenu->getChildrenCount() - oldCount;
        if (addedCount == 3) {
            setIDs(
                m_buttonMenu,
                oldCount,
                "reply-button",
                "remove-button",
                "block-button"
            );
        }
        else if (addedCount == 1) {
            setIDSafe(m_buttonMenu, oldCount, "remove-button");
        }

        if (auto bottomMenu = m_mainLayer->getChildByID("bottom-menu")) {
            switchToMenu(m_buttonMenu->getChildByID("reply-button"), bottomMenu);
            switchToMenu(m_buttonMenu->getChildByID("remove-button"), bottomMenu);
            switchToMenu(m_buttonMenu->getChildByID("block-button"), bottomMenu);
            bottomMenu->updateLayout();
            handleTouchPriority(this);
        }
    }
};
