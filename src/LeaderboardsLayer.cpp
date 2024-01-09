#include <Geode/Bindings.hpp>
#include <Geode/modify/LeaderboardsLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(LeaderboardsLayer) {
    setIDs(
        this,
        0,
        "background",
        "bottom-left-art",
        "bottom-right-art",
        "loading-circle",
        "no-internet-label",
        "info-menu",
        "top-100-menu",
        "friends-menu",
        "global-menu",
        "creators-menu",
        "list-layer",
        "back-menu"
    );

    auto winSize = CCDirector::get()->getWinSize();

    auto bottomRightMenu = CCMenu::create();
    bottomRightMenu->setID("bottom-right-menu");
    bottomRightMenu->setContentSize({ 26.75f*2, winSize.height - 10.f });
    bottomRightMenu->setPosition(winSize.width - 26.75f, winSize.height / 2);
    bottomRightMenu->setZOrder(2);
    bottomRightMenu->setLayout(
        ColumnLayout::create()
                ->setGap(7.f)
                ->setAxisAlignment(AxisAlignment::Start)
                ->setAxisReverse(true)
    );
    this->addChild(bottomRightMenu);

    if(auto infoMenu = getChildByID("info-menu")) {
        setIDSafe(infoMenu, 0, "info-button");

        infoMenu->setContentSize({ 26.75f*2, winSize.height - 37.f });
        infoMenu->setPositionY(winSize.height / 2);
        infoMenu->setLayout(
            ColumnLayout::create()
                ->setGap(7.f)
                ->setAxisAlignment(AxisAlignment::Start)
                ->setAxisReverse(true)
        );
    }
}

struct LeaderboardsLayerIDs : Modify<LeaderboardsLayerIDs, LeaderboardsLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("LeaderboardsLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set LeaderboardsLayer::init hook priority, node IDs may not work properly");
        }
    }

    bool init(LeaderboardState state) {
        if (!LeaderboardsLayer::init(state)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};
