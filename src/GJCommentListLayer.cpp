#include <Geode/Bindings.hpp>
#include <Geode/modify/GJCommentListLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(GJCommentListLayer) {
    setIDs(
        this,
        0,
        "bottom-border",
        "top-border",
        "left-border",
        "right-border",
        "list-view"
    );
}

struct GJCommentListLayerIDs : Modify<GJCommentListLayerIDs, GJCommentListLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("GJCommentListLayer::create", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set GJCommentListLayer::create hook priority, node IDs may not work properly");
        }
    }

    static GJCommentListLayer* create(BoomListView* listView, char const* title, cocos2d::ccColor4B color, float width, float height, bool blueBorder) {
        /**
         * GJCommentListLayer is one of the classes
         * that has its init half-inlined
         * so we need to hook create instead
         */
        auto layer = GJCommentListLayer::create(listView, title, color, width, height, blueBorder);
        if(!layer) return nullptr;

        NodeIDs::get()->provide(layer);

        return layer;
    }
};
