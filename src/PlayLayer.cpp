#include <Geode/Bindings.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

#if 0

$register_ids(PlayLayer) {
    setIDSafe(this, 1, "main-node");
    setIDSafe(this, 3, "hitbox-node");
    setIDSafe(this, 4, "effect-manager");
    setIDSafe(this, 6, "ui-layer");
    setIDSafe(this, 7, "debug-text");
    setIDSafe(this, 8, "progress-bar");

    auto level = PlayLayer::get()->m_level;
    if (level->isPlatformer()) {
        setIDSafe(this, 9, "time-label");
    }
    else {
        setIDSafe(this, 9, "percentage-label");
    }
}

struct PlayLayerIDs : Modify<PlayLayerIDs, PlayLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("PlayLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set PlayLayer::init hook priority, node IDs may not work properly");
        }
    }

    bool init(GJGameLevel* level, bool p1, bool p2) {
        if (!PlayLayer::init(level, p1, p2)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};
#endif
