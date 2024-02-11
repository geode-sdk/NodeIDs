#include <Geode/Bindings.hpp>
#include <Geode/modify/LevelAreaInnerLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(LevelAreaInnerLayer) {
    auto GSM = GameStatsManager::sharedState();

    if(auto menu = setIDSafe(this, 0, "back-menu")) {
        setIDs(
            menu,
            0,
            "back-button",
            "info-button"
        );
    }

    if(auto layer = static_cast<CCNode*>(this->getChildren()->objectAtIndex(getChildrenCount() - 1))) {
        size_t idx = 0;

        layer->setID("main-node");
        setIDSafe(layer, idx++, "background");

        for(int i = 5001; i <= 5004; i++) {
            if(!GSM->hasCompletedMainLevel(i)) continue;
            
            for(int j = 1; j <= 3; j++) {
                setIDSafe(layer, idx++, fmt::format("coin-{}-{}", i, j).c_str());
            }
        }

        if(auto menu = setIDSafe(layer, idx++, "main-menu")) {
            size_t menuIdx = 0;

            for(int i = 5001; i <= 5004; i++) setIDSafe(menu, menuIdx++, fmt::format("level-{}-button", i).c_str());

            setIDSafe(menu, menuIdx++, "second-floor-button");
        }

        setIDs(
            layer,
            idx,
            "left-torch-handle",
            "left-torch-flame-outline",
            "left-torch-flame",
            "left-torch-big-glow",
            "left-torch-small-glow",

            
            "right-torch-handle",
            "right-torch-flame-outline",
            "right-torch-flame",
            "right-torch-big-glow",
            "right-torch-small-glow"
        );
    }
}

struct LevelAreaInnerLayerIDs : Modify<LevelAreaInnerLayerIDs, LevelAreaInnerLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("LevelAreaInnerLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set LevelAreaInnerLayer::init hook priority, node IDs may not work properly");
        }
    }

    bool init(bool a) {
        if (!LevelAreaInnerLayer::init(a)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};
