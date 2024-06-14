#include <Geode/Bindings.hpp>
#include <Geode/modify/GJListLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(GJListLayer) {
    if (m_listView)
        m_listView->setID("list-view");

    setIDSafe<CCSprite>(this, 0, "bottom-border");
    setIDSafe<CCSprite>(this, 1, "top-border");
    setIDSafe<CCSprite>(this, 2, "left-border");
    setIDSafe<CCSprite>(this, 3, "right-border");

    setIDSafe<CCLabelBMFont>(this, 0, "title");
}

struct GJListLayerIDs : Modify<GJListLayerIDs, GJListLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("GJListLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set GJListLayer::init hook priority, node IDs may not work properly");
        }
    }

    bool init(BoomListView* p0, char const* p1, cocos2d::ccColor4B p2, float p3, float p4, int p5) {
        if (!GJListLayer::init(p0, p1, p2, p3, p4, p5)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};