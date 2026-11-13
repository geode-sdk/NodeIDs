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

        if (!self.setHookPriority("ScrollableContentLayer::ensureScrollThumb", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set ScrollableContentLayer::ensureScrollThumb hook priority, node IDs may not work properly");
        }

        if (!self.setHookPriority("ScrollableContentLayer::ensureOwnedContentNode", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set ScrollableContentLayer::ensureOwnedContentNode hook priority, node IDs may not work properly");
        }
    }

    static ScrollableContentLayer* create(CCSize size) {
        auto ret = ScrollableContentLayer::create(size);
        if (!ret) return nullptr;

        NodeIDs::get()->provide(ret);

        return ret;
    }

    void ensureScrollThumb() {
        ScrollableContentLayer::ensureScrollThumb();
        if (m_thumb && m_thumb->getID().empty()) m_thumb->setID("scroll-thumb");
    }

    void ensureOwnedContentNode() {
        ScrollableContentLayer::ensureOwnedContentNode();
        if (m_content && m_content->getID().empty()) m_content->setID("content-layer");
    }
};

#endif
