#include <Geode/Geode.hpp>
#include <Geode/modify/MessagesProfilePage.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(MessagesProfilePage) {
    m_mainLayer->setID("main-layer");

    setIDs(
        m_mainLayer,
        0,
        "background",
        "title-label",
        "page-label",
        "main-menu",
        "loading-circle",
        "selected-count-label",
        "error-label"
    );

    size_t buttonIdx = 0;
    setIDSafe(m_buttonMenu, buttonIdx++, "back-button");
    if (!m_sentMessages) setIDSafe(m_buttonMenu, buttonIdx++, "sent-messages-button");
    setIDs(
        m_buttonMenu,
        buttonIdx,
        "select-all-button",
        "delete-button",
        "prev-page-button",
        "next-page-button",
        "refresh-button"
    );

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
    topLeftMenu->setPosition({ (winSize.width / 2) - 234.75f, (winSize.height / 2) + 160.5f });
    topLeftMenu->setContentSize({ 130.f, 0.f });
    topLeftMenu->setZOrder(10);
    m_mainLayer->addChild(topLeftMenu);

    switchToMenu(m_buttonMenu->getChildByID("back-button"), topLeftMenu);
    topLeftMenu->updateLayout();

    auto topRightMenu = CCMenu::create();
    topRightMenu->setLayout(
        RowLayout::create()
            ->setGap(8.f)
            ->setAxisAlignment(AxisAlignment::End)
            ->setCrossAxisAlignment(AxisAlignment::End)
            ->setAxisReverse(true)
    );
    topRightMenu->setID("top-right-menu");
    topRightMenu->setAnchorPoint({ 1.f, 1.f });
    topRightMenu->setPosition({ (winSize.width / 2) + 231.5f, (winSize.height / 2) + 155.75f });
    topRightMenu->setContentSize({ 130.f, 0.f });
    topRightMenu->setZOrder(10);
    m_mainLayer->addChild(topRightMenu);

    switchToMenu(m_buttonMenu->getChildByID("sent-messages-button"), topRightMenu);
    topRightMenu->updateLayout();

    auto bottomRightMenu = CCMenu::create();
    bottomRightMenu->setLayout(
        RowLayout::create()
            ->setGap(8.f)
            ->setAxisAlignment(AxisAlignment::End)
            ->setCrossAxisAlignment(AxisAlignment::Start)
            ->setAxisReverse(true)
            ->ignoreInvisibleChildren(false)
    );
    bottomRightMenu->setID("bottom-right-menu");
    bottomRightMenu->setAnchorPoint({ 1.f, 0.f });
    bottomRightMenu->setPosition({ (winSize.width / 2) + 233.f, (winSize.height / 2) - 157.75f });
    bottomRightMenu->setContentSize({ 130.f, 0.f });
    bottomRightMenu->setZOrder(10);
    m_mainLayer->addChild(bottomRightMenu);

    switchToMenu(m_buttonMenu->getChildByID("refresh-button"), bottomRightMenu);
    bottomRightMenu->updateLayout();

    handleTouchPriority(this);
}

struct MessagesProfilePageIDs : Modify<MessagesProfilePageIDs, MessagesProfilePage> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("MessagesProfilePage::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set MessagesProfilePage::init hook priority, node IDs may not work properly");
        }
    }

    bool init(bool sent) {
        if (!MessagesProfilePage::init(sent)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};
