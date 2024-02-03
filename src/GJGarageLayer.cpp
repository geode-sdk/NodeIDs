// #include "AddIDs.hpp"

#include <Geode/Bindings.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(GJGarageLayer) {
    auto GJAM = GJAccountManager::sharedState();
    auto GM = GameManager::sharedState();
    auto winSize = CCDirector::sharedDirector()->getWinSize();

    size_t offset = 0;

    setIDSafe(this, offset++, "background");
    setIDSafe(this, offset++, "top-left-corner");
    setIDSafe(this, offset++, "bottom-left-corner");
    setIDSafe(this, offset++, "bottom-right-corner");
    setIDSafe(this, offset++, "username-label");

    if(GJAM->m_accountID == 0) {
        if(!GM->m_clickedName) setIDSafe(this, offset++, "username-hint");
    } else {
        setIDSafe(this, offset++, "username-lock");
    }

    setIDSafe(this, offset++, "floor-line");
    setIDSafe(this, offset++, "player-icon");

    // setupIconSelect
    setIDSafe(this, offset++, "select-background");
    setIDSafe(this, offset++, "tap-more-hint");
    
    if(auto menu = typeinfo_cast<CCMenu*>(setIDSafe(this, offset++, "category-menu"))) {
        setIDs(
            menu,
            0,
            "cube-button",
            "ship-button",
            "ball-button",
            "ufo-button",
            "wave-button",
            "robot-button",
            "spider-button",
            "swing-button",
            "jetpack-button",
            "trail-button",
            "death-effect-button",
            "prev-button",
            "next-button"
        );

        if (auto prevPageBtn = menu->getChildByID("prev-button")) {
            auto prevMenu = detachAndCreateMenu(
                this,
                "prev-page-menu",
                ColumnLayout::create()
                    ->setAxisAlignment(AxisAlignment::Center),
                prevPageBtn
            );
            prevPageBtn->setZOrder(-1);
            prevMenu->setContentSize({ 40.f, 100.f });
            prevMenu->updateLayout();
        }

        if (auto nextPageBtn = menu->getChildByID("next-button")) {
            auto nextMenu = detachAndCreateMenu(
                this,
                "next-page-menu",
                ColumnLayout::create()
                    ->setAxisAlignment(AxisAlignment::Center),
                nextPageBtn
            );
            nextPageBtn->setZOrder(-1);
            nextMenu->setContentSize({ 40.f, 100.f });
            nextMenu->updateLayout();
        }

        menu->setContentSize({ winSize.width - 100.f, 50.f });
        menu->setLayout(
            RowLayout::create()
                ->setAxisAlignment(AxisAlignment::Center)
                ->setGap(2.f)
        );
    }

    setIDSafe(this, offset++, "cursor-1");
    setIDSafe(this, offset++, "cursor-2");

    if(auto menu = typeinfo_cast<CCMenu*>(setIDSafe(this, offset++, "navdot-menu"))) {
        // no point in setting IDs for the dots, they're constantly reset

        menu->setLayout(
            RowLayout::create()
                ->setGap(6.f)
                ->setAxisAlignment(AxisAlignment::Center)
        );
        menu->setContentSize({ winSize.width - 60.f, 20.f });
        menu->updateLayout();
    }

    setIDSafe(this, offset++, "icon-selection-bar");
    // end of setupIconSelect

    if(auto menu = typeinfo_cast<CCMenu*>(setIDSafe(this, offset++, "top-left-menu"))) {
        setIDs(menu, 0, "back-button", "shop-button", "shards-button", "color-button");

        if(auto backBtn = menu->getChildByID("back-button")) {
            auto backMenu = detachAndCreateMenu(
                this,
                "back-menu",
                RowLayout::create()
                    ->setAxisAlignment(AxisAlignment::Start),
                backBtn
            );
            backMenu->setContentSize({ 100.f, 50.f });
            backMenu->setPositionX(
                backMenu->getPositionX() + 100.f / 2 - 
                    getSizeSafe(backBtn).width / 2
            );
            backMenu->updateLayout();
        }

        if(auto shardsBtn = menu->getChildByID("shards-button")) {
            auto shardsMenu = detachAndCreateMenu(
                this,
                "shards-menu",
                ColumnLayout::create()
                    ->setAxisReverse(true)
                    ->setAxisAlignment(AxisAlignment::End)
                    ->setGap(3.25f),
                shardsBtn,
                menu->getChildByID("color-button")
            );
            shardsMenu->setContentSize({ 50.f, 200.f });
            shardsMenu->setPositionY(
                shardsMenu->getPositionY() - 200.f / 2 + 
                    getSizeSafe(shardsBtn).height / 2
            );
            shardsMenu->updateLayout();
        }
    }

    setIDs(
        this,
        offset,
        "stars-icon",
        "stars-label",
        "moons-icon",
        "moons-label",
        "coins-icon",
        "coins-label",
        "user-coins-icon",
        "user-coins-label",
        "orbs-icon",
        "orbs-label",
        "diamonds-icon",
        "diamonds-label",
        "diamond-shards-icon",
        "diamond-shards-label"
    );
}

struct GJGarageLayerIDs : Modify<GJGarageLayerIDs, GJGarageLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("GJGarageLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set GJGarageLayer::init hook priority, node IDs may not work properly");
        }
    }

    bool init() {
        if (!GJGarageLayer::init()) return false;

        NodeIDs::get()->provide(this);

        return true;
    }

    void setupPage(int a1, IconType a2) {
        GJGarageLayer::setupPage(a1, a2);

        if(auto menu = getChildByID("navdot-menu")) {
            menu->updateLayout();
        }
    }
};
