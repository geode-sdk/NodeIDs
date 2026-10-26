#include <Geode/Geode.hpp>
#include <Geode/modify/SelectArtLayer.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(SelectArtLayer) {
    
    if (auto ArtLayerBody = setIDSafe<CCLayer>(this, 0, "main-layer")) {
        setIDSafe<CCScale9Sprite>(ArtLayerBody, 0, "background");

        setIDSafe<CCLabelBMFont>(ArtLayerBody, 0, "title-label");
        
        if (auto ArtLayerMenu = setIDSafe<CCMenu>(ArtLayerBody, 0, "main-menu")) {
            // would be better to make modular in the future
            setIDs(
                ArtLayerMenu,
                0,
                "block012_01",
                "block013_01c",
                "blockDesign01_01",
                "blockDesign02_01",
                "blockDesign03_01",
                "blockDesign05_01",
                "blockDesign06_01",
                "blockDesign07_01",
                "gdh_01_1",
                "gdh_01_2",
                "gdh_02_1",
                "block009_03",
                "ok-button"
            );
        };
    }
}

struct SelectArtLayerIDs : Modify<SelectArtLayerIDs, SelectArtLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("SelectArtLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set SelectArtLayer::init hook priority, node IDs may not work properly");
        }
    }

    bool init(SelectArtType type, int index) {
        if (!SelectArtLayer::init(type, index)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};