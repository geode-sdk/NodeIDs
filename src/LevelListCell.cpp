#include <Geode/Bindings.hpp>
#include <Geode/modify/LevelListCell.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(LevelListCell) {
    setIDSafe<CCLayerColor>(this, 0, "background");
    
    if (auto mainLayer = setIDSafe<CCLayer>(this, 1, "main-layer")) {
        if (auto mainMenu = setIDSafe<CCMenu>(mainLayer, 0, "main-menu")) {
            setIDSafe<CCMenuItemSpriteExtra>(mainMenu, 0, "view-button");
            setIDSafe<CCMenuItemSpriteExtra>(mainMenu, 1, "creator-name");
            setIDSafe<CCMenuItemSpriteExtra>(mainMenu, 2, "info-icon");
        }
        if (auto diamondIcon = ::getChildBySpriteFrameName(mainLayer, "diamond_small01_001.png")) {
            diamondIcon->setID("diamond-icon");
        }
        if (auto downloadsIcon = ::getChildBySpriteFrameName(mainLayer, "GJ_downloadsIcon_001.png")) {
            downloadsIcon->setID("downloads-icon");
        }
        if (auto likesIcon = ::getChildBySpriteFrameName(mainLayer, "GJ_likesIcon_001.png")) {
            likesIcon->setID("likes-icon");
        }
        if (auto featuredIcon = ::getChildBySpriteFrameName(mainLayer, "GJ_featuredIcon_001.png")) {
            featuredIcon->setID("featured-icon");
        }
    }
}

struct LevelListCellIDs : Modify<LevelListCellIDs, LevelListCell> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("LevelListCell::loadFromList", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set LevelListCell::loadFromList hook priority, node IDs may not work properly");
        }
    }

    void loadFromList(GJLevelList* p0) {
        LevelListCell::loadFromList(p0);

        NodeIDs::get()->provide(this);
    }
};