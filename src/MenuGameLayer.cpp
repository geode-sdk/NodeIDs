#include <Geode/Bindings.hpp>
#include <Geode/modify/MenuGameLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(MenuGameLayer) {
    setIDSafe<CCSprite>(this, 0, "background");
    setIDSafe<GJGroundLayer>(this, 0, "ground");
    setIDSafe<CCMotionStreak>(this, 0, "player-streak");
    setIDSafe<HardStreak>(this, 0, "player-wave-trail");

    // all the other objects are just particles, which are members of the player.
    // node id for the player isn't set cuz it already has one
}

struct MenuGameLayerIDs : Modify<MenuGameLayerIDs, MenuGameLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("MenuGameLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set MenuGameLayer::init hook priority, node IDs may not work properly");
        }
    }

    virtual bool init() {
        if (!MenuGameLayer::init()) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};
