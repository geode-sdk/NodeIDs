#include <Geode/Bindings.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(PlayLayer) {
    setIDSafe(this, 1, "main-node");
    setIDSafe<CCSprite>(static_cast<CCNode*>(this->getChildren()->objectAtIndex(1)), 0, "background");

    setIDSafe(this, 3, "hitbox-node");
    setIDSafe<GJEffectManager>(this, 0, "effect-manager");
    //setIDSafe<UILayer>(this, 0, "ui-layer"); //changing this id is unsafe because mods depend on "UILayer", which is actually fairly safe to do, since this is the only UILayer in the whole layer
    setIDSafe<CCLabelBMFont>(this, 0, "debug-text");
    setIDSafe<CCSprite>(this, 0, "progress-bar");

    auto level = PlayLayer::get()->m_level;
    if (level->isPlatformer()) {
        setIDSafe<CCLabelBMFont>(this, 1, "time-label");
    }
    else {
        setIDSafe<CCLabelBMFont>(this, 1, "percentage-label");
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