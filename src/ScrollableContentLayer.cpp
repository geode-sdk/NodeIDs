#include <Geode/Geode.hpp>

#if GEODE_COMP_GD_VERSION >= 22090

#include <Geode/modify/ScrollableContentLayer.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(ScrollableContentLayer) {
    setIDSafe(this, 0, "content-layer");
}

struct ScrollableContentLayerIDs : Modify<ScrollableContentLayerIDs, ScrollableContentLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("ScrollableContentLayer::create", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set ScrollableContentLayer::create hook priority, node IDs may not work properly");
        }
    }

    static ScrollableContentLayer* create(CCSize size) {
        auto ret = ScrollableContentLayer::create(size);
        if (!ret) return nullptr;

        NodeIDs::get()->provide(ret);

        return ret;
    }

    void visit() {
        if (auto thumb = this->getChildByType<CCLayerColor>(0); thumb && thumb->getID().empty()) {
            thumb->setID("scroll-thumb");
        }

        ScrollableContentLayer::visit();
    }
};

#endif
