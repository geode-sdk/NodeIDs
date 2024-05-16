#include <Geode/Bindings.hpp>
#include <Geode/modify/GJGroundLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(GJGroundLayer) {
    setIDSafe<CCSprite>(this, 0, "line");
    setIDSafe<CCSprite>(this, 1, "shadow-left");
    setIDSafe<CCSprite>(this, 2, "shadow-right");
    setIDs(this, 3, "ground-sprites", "ground-sprites-2");
}

struct GJGroundLayerIDs : Modify<GJGroundLayerIDs, GJGroundLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("GJGroundLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set GJGroundLayer::init hook priority, node IDs may not work properly");
        }
    }

    bool init(int p0, int p1) {
        if (!GJGroundLayer::init(p0, p1)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};
