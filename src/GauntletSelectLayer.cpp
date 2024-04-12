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

    if (auto arrowsMenu = this->getChildByID("scroll-buttons-menu")) {
        setIDs(
            arrowsMenu,
            0,
            "left-button",
            "right-button"
        );
    }

    if (auto miscMenu = this->getChildByID("left-menu")) {
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

        if (auto gauntletsList = getChildOfType<BoomScrollLayer>(this, 0)) {
            gauntletsList->setID("gauntlets-list");

            if (auto gauntletPages = getChildOfType<ExtendedLayer>(gauntletsList, 0)) {
                gauntletPages->setID("gauntlet-pages");

                auto gauntletPagesArray = CCArrayExt<CCLayer*>(gauntletPages->getChildren());
                for (int i = 0; i < gauntletPagesArray.size(); i++) {
                    auto gauntletPage = gauntletPagesArray[i];
                    gauntletPage->setID(fmt::format("gauntlet-page-{}", i + 1));

                    if (auto gauntletMenu = getChildOfType<CCMenu>(gauntletPage, 0)) {
                        gauntletMenu->setID("gauntlet-menu");

                        auto gauntletButtons = CCArrayExt<CCMenuItemSpriteExtra*>(gauntletMenu->getChildren());
                        for (int i = 0; i < gauntletButtons.size(); i++) {
                            auto gauntletButton = gauntletButtons[i];

                            gauntletButton->setID(fmt::format("gauntlet-button-{}", i + 1));

                            if (auto gauntletNodeParent = getChildOfType<CCNode>(gauntletButton, 0)) {
                                gauntletNodeParent->setID("gauntlet-node-parent");

                                getChildOfType<GauntletNode>(gauntletNodeParent, 0)->setID("gauntlet-node");
                            }
                        }
                    }
                }
            }

            getChildOfType<CCSpriteBatchNode>(gauntletsList, 0)->setID("page-buttons");
        }
    }
};
