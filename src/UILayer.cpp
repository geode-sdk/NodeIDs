#include <Geode/Bindings.hpp>
#include <Geode/modify/UILayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(UILayer) {
    setIDs(
        this,
        0,
        "platformer-p1-move-button",
        "platformer-p2-move-button",
        "platformer-p1-jump-button",
        "platformer-p2-jump-button",
        "pause-button-menu",
        "checkpoint-menu"
    );

    setIDs(
        this->getChildByID("pause-button-menu"), 
        0, 
        "pause-button"
    );

    setIDs(
        this->getChildByID("checkpoint-menu"), 
        0, 
        "add-checkpoint-button", 
        "remove-checkpoint-button"
    );

    auto addButton = this->getChildByIDRecursive("add-checkpoint-button");
    if (addButton->getChildrenCount() > 0) {
        setIDs(addButton, 0, "add-checkpoint-hint");
    }

    auto removeButton = this->getChildByIDRecursive("remove-checkpoint-button");
    if (removeButton->getChildrenCount() > 0) {
        setIDs(removeButton, 0, "remove-checkpoint-hint");
    }
}

struct UILayerIDs : Modify<UILayerIDs, UILayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("UILayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set UILayer::init hook priority, node IDs may not work properly");
        }
    }

    bool init(GJBaseGameLayer* gameLayer) {
        if (!UILayer::init(gameLayer)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};
