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
        if (!self.setHookPriority("GJCommentListLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set GJCommentListLayer::init hook priority, node IDs may not work properly");
        }
    }

    bool init(BoomListView* listView, char const* title, cocos2d::ccColor4B color, float width, float height, bool blueBorder) {
        if(!GJCommentListLayer::init(listView, title, color, width, height, blueBorder)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};
