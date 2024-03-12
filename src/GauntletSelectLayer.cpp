#include <Geode/Geode.hpp>
#include <Geode/binding/GauntletSelectLayer.hpp>
#include <Geode/modify/GauntletSelectLayer.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(GauntletSelectLayer) {
    this->setID("main-layer");

    getChildOfType<CCSprite>(this, 0)->setID("background");
    getChildOfType<CCSprite>(this, 1)->setID("title-sprite");

    setIDs(
        this,
        PlatformToolbox::isControllerConnected() ? 3 : 2,
        "bottom-left-corner",
        "bottom-right-corner",
        "top-left-corner",
        "top-right-corner",
        "arrows-menu",
        "misc-menu",
        "loading-circle",
        "error-text-area"
    );

    if (auto arrowsMenu = this->getChildByID("arrows-menu")) {
        setIDs(
            arrowsMenu,
            0,
            "left-button",
            "right-button"
        );
    }

    if (auto miscMenu = this->getChildByID("misc-menu")) {
        setIDs(
            miscMenu,
            0,
            "back-button",
            "info-button",
            "reload-button"
        );
    }
}

struct GauntletSelectLayerIDs : Modify<GauntletSelectLayerIDs, GauntletSelectLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("GauntletSelectLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set GauntletSelectLayer::init hook priority, node IDs may not work properly");
        }
        if (!self.setHookPriority("GauntletSelectLayer::setupGauntlets", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set GauntletSelectLayer::setupGauntlets hook priority, node IDs may not work properly");
        }
    }

    bool init(int p0) {
        if (!GauntletSelectLayer::init(p0)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }

    void setupGauntlets() {
        GauntletSelectLayer::setupGauntlets();

        getChildOfType<BoomScrollLayer>(this, 0)->setID("gauntlets-list");
    }
};
