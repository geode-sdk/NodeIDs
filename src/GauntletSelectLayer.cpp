#include <Geode/Bindings.hpp>
#include <Geode/modify/GauntletSelectLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(GauntletSelectLayer) {
    setIDs(
        this,
        0,
        "background",
        "title",
        "bottom-left-corner",
        "bottom-right-corner",
        "top-left-corner",
        "top-right-corner",
        "scroll-buttons-menu",
        "left-menu",
        "loading-circle",
        "try-again-text"
    );
}

struct GauntletSelectLayerIDs : Modify<GauntletSelectLayerIDs, GauntletSelectLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("GauntletSelectLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set GauntletSelectLayer::init hook priority, node IDs may not work properly");
        }
    }

    bool init(int idk) {
        if (!GauntletSelectLayer::init(idk)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};
