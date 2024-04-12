#include <Geode/Geode.hpp>
#include <Geode/binding/LevelSelectLayer.hpp>
#include <Geode/modify/LevelSelectLayer.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(LevelSelectLayer) {
    this->setID("main-layer");

    setIDs(
        this,
        0,
        "background",
        "ground-layer",
        "top-bar-sprite",
        "bottom-left-corner",
        "bottom-right-corner",
        "levels-list",
        "bottom-center-menu",
        "arrows-menu",
        "back-menu",
        "info-menu"
    );

    if (auto levelsList = this->getChildByID("levels-list")) {
        if (auto levelPages = getChildOfType<ExtendedLayer>(levelsList, 0)) {
            levelPages->setID("level-pages");

            setIDs(
                levelPages,
                0,
                "level-page-1",
                "level-page-2",
                "level-page-3"
            );
        }

        getChildOfType<CCSpriteBatchNode>(levelsList, 0)->setID("page-buttons");
    }

    if (auto bottomCenterMenu = this->getChildByID("bottom-center-menu")) {
        if (auto soundtrackButton = getChildOfType<CCMenuItemSpriteExtra>(bottomCenterMenu, 0)) {
            soundtrackButton->setID("download-soundtrack-button");

            getChildOfType<CCLabelBMFont>(soundtrackButton, 0)->setID("download-soundtrack-label");
        }
    }

    getChildOfType<CCMenuItemSpriteExtra>(this->getChildByID("info-menu"), 0)->setID("info-button");
    getChildOfType<CCMenuItemSpriteExtra>(this->getChildByID("back-menu"), 0)->setID("back-button");

    if (auto arrowsMenu = this->getChildByID("arrows-menu")) {
        setIDs(
            arrowsMenu,
            0,
            "left-button",
            "right-button"
        );
    }
}

struct LevelSelectLayerIDs : Modify<LevelSelectLayerIDs, LevelSelectLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("LevelSelectLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set LevelSelectLayer::init hook priority, node IDs may not work properly");
        }
    }

    bool init(int p0) {
        if (!LevelSelectLayer::init(p0)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};
