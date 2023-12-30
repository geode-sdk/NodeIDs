// #include "AddIDs.hpp"

#include <Geode/modify/DailyLevelPage.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(DailyLevelPage) {
    getChildOfType<CCScale9Sprite>(m_mainLayer, 0)->setID("background");
    getChildOfType<CCSprite>(m_mainLayer, 0)->setID("title-sprite");
    getChildOfType<CCSprite>(m_mainLayer, 1)->setID("bottom-left-corner");
    getChildOfType<CCSprite>(m_mainLayer, 2)->setID("top-left-corner");
    getChildOfType<CCSprite>(m_mainLayer, 3)->setID("top-right-corner");
    getChildOfType<CCSprite>(m_mainLayer, 4)->setID("bottom-right-corner");


    if (auto mainMenu = getChildOfType<CCMenu>(m_mainLayer, 0)) {
        mainMenu->setID("main-menu");

        getChildOfType<CCMenuItemSpriteExtra>(mainMenu, 0)->setID("close-button");
        getChildOfType<CCMenuItemSpriteExtra>(mainMenu, 1)->setID("the-safe-button");
    }

    getChildOfType<CCLabelBMFont>(m_mainLayer, 0)->setID("time-label");
    getChildOfType<LoadingCircle>(m_mainLayer, 0)->setID("time-circle");
    getChildOfType<LoadingCircle>(m_mainLayer, 1)->setID("node-circle");
}

struct DailyLevelPageIDs : Modify<DailyLevelPageIDs, DailyLevelPage> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("DailyLevelPage::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set DailyLevelPage::init hook priority, node IDs may not work properly");
        }
    }

    bool init(GJTimedLevelType type) {
        if(!DailyLevelPage::init(type)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};
