// #include "AddIDs.hpp"

#include <Geode/modify/GameToolbox.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

struct GameToolboxIDs : Modify<GameToolboxIDs, GameToolbox> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("GameToolbox::addBackButton", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set GameToolbox::addBackButton hook priority, node IDs may not work properly");
        }
        if (!self.setHookPriority("GameToolbox::addRThumbScrollButton", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set GameToolbox::addRThumbScrollButton hook priority, node IDs may not work properly");
        }
    }

    static void addBackButton(CCLayer* layer, CCMenuItem* item) {
        GameToolbox::addBackButton(layer, item);

        static_cast<CCNode*>(layer->getChildren()->objectAtIndex(layer->getChildrenCount() - 1))->setID("controller-back-hint");
    }

    static void addRThumbScrollButton(CCLayer* layer) {
        GameToolbox::addRThumbScrollButton(layer);

        static_cast<CCNode*>(layer->getChildren()->objectAtIndex(layer->getChildrenCount() - 1))->setID("controller-scroll-down");
        static_cast<CCNode*>(layer->getChildren()->objectAtIndex(layer->getChildrenCount() - 2))->setID("controller-scroll-up");
        static_cast<CCNode*>(layer->getChildren()->objectAtIndex(layer->getChildrenCount() - 3))->setID("controller-scroll-rthumb");
    }
};
