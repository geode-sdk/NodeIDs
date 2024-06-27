#include <Geode/Geode.hpp>
#include <Geode/modify/FriendsProfilePage.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(FriendsProfilePage) {
    m_mainLayer->setID("main-layer");

    size_t i = 0;
    setIDs(
        m_mainLayer,
        0,
        "background",
        "title-label"
    );

    i += 2;
    if(m_type != UserListType::Blocked) {
        setIDs(
            m_mainLayer,
            i,
            "tap-user-label"
        );
        i += 1;
    }

    setIDs(
        m_mainLayer,
        i,
        "total-friends-label",
        "main-menu",
        "no-internet-label",
        "loading-circle"
        //setting label for gjcommentlistlayer skipped, it never sticks and theres only one
    );

    size_t buttonIdx = 0;
    setIDSafe(m_buttonMenu, buttonIdx++, "back-button");
    if(m_type == UserListType::Friends) setIDSafe(m_buttonMenu, buttonIdx++, "blocked-button");
    setIDSafe(m_buttonMenu, buttonIdx++, "refresh-button");

    //sanity checks
    verifyIDSafe(m_buttonMenu, "main-menu");
    verifyIDSafe(m_refreshBtn, "refresh-button");
    verifyIDSafe(m_circle, "loading-circle");

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
    );
    switchToMenu(m_refreshBtn, bottomRightMenu);
    bottomRightMenu->updateLayout();
    m_mainLayer->addChild(bottomRightMenu);

    auto bottomLeftMenu = CCMenu::create();
    bottomLeftMenu->setPosition((winSize.width / 2) - 233, (winSize.height / 2) - (160 - 2.25f));
    bottomLeftMenu->setID("bottom-left-menu");
    bottomLeftMenu->setAnchorPoint({0, 0});
    bottomLeftMenu->setZOrder(1);
    bottomLeftMenu->setContentSize({ 130.f, 0.f });
    bottomLeftMenu->setLayout(
        RowLayout::create()
            ->setAxisAlignment(AxisAlignment::Start)
            ->setCrossAxisAlignment(AxisAlignment::Start)
            ->setAxisReverse(false)
            ->setGap(8.f)
    );
    bottomLeftMenu->updateLayout();
    m_mainLayer->addChild(bottomLeftMenu);

    auto topRightMenu = CCMenu::create();
    topRightMenu->setPosition((winSize.width / 2) + 231.5, (winSize.height / 2) + (160 - 4.25f));
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
    switchToMenu(m_buttonMenu->getChildByID("blocked-button"), topRightMenu);
    topRightMenu->updateLayout();
    m_mainLayer->addChild(topRightMenu);

    auto topLeftMenu = CCMenu::create();
    topLeftMenu->setPosition((winSize.width / 2) - 234.5, (winSize.height / 2) + (160 - 1.25f));
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
