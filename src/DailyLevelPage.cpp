// #include "AddIDs.hpp"

#include <Geode/Geode.hpp>
#include <Geode/modify/DailyLevelPage.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(DailyLevelPage) {
    m_mainLayer->getChildByType<CCScale9Sprite>(0)->setID("background");
    m_mainLayer->getChildByType<CCSprite>(0)->setID("title-sprite");
    m_mainLayer->getChildByType<CCSprite>(1)->setID("bottom-left-corner");
    m_mainLayer->getChildByType<CCSprite>(2)->setID("top-left-corner");
    m_mainLayer->getChildByType<CCSprite>(3)->setID("top-right-corner");
    m_mainLayer->getChildByType<CCSprite>(4)->setID("bottom-right-corner");


    if (auto mainMenu = m_mainLayer->getChildByType<CCMenu>(0)) {
        mainMenu->setID("main-menu");

        mainMenu->getChildByType<CCMenuItemSpriteExtra>(0)->setID("close-button");
        mainMenu->getChildByType<CCMenuItemSpriteExtra>(1)->setID("the-safe-button");
    }

    m_mainLayer->getChildByType<CCLabelBMFont>(0)->setID("time-label");
    m_mainLayer->getChildByType<LoadingCircle>(0)->setID("time-circle");
    m_mainLayer->getChildByType<LoadingCircle>(1)->setID("node-circle");
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
