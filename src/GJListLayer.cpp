#include <Geode/Bindings.hpp>
#include <Geode/modify/GJListLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

struct GJListLayerIDs : Modify<GJListLayerIDs, GJListLayer> {
    struct Fields {
        int m_listType = 0;
    };

    static void onModify(auto& self) {
        if (!self.setHookPriority("GJListLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set GJListLayer::init hook priority, node IDs may not work properly");
        }
    }

    bool init(BoomListView* p0, char const* p1, cocos2d::ccColor4B p2, float p3, float p4, int listType) {
        if (!GJListLayer::init(p0, p1, p2, p3, p4, listType)) return false;

        m_fields->m_listType = listType;
        NodeIDs::get()->provide(this);

        return true;
    }
};

$register_ids(GJListLayer) {
    if (m_listView)
        m_listView->setID("list-view");

    if(reinterpret_cast<GJListLayerIDs*>(this)->m_fields->m_listType == 1) {
        setIDSafe<CCSprite>(this, 0, "bottom-border");
        setIDSafe<CCSprite>(this, 1, "top-border");
        setIDSafe<CCSprite>(this, 2, "top-left-corner");
        setIDSafe<CCSprite>(this, 3, "top-right-corner");
        setIDSafe<CCSprite>(this, 4, "bottom-left-corner");
        setIDSafe<CCSprite>(this, 5, "bottom-right-corner");
        setIDSafe<CCSprite>(this, 6, "left-border");
        setIDSafe<CCSprite>(this, 7, "right-border");
    } else {
        setIDSafe<CCSprite>(this, 0, "bottom-border");
        setIDSafe<CCSprite>(this, 1, "top-border");
        setIDSafe<CCSprite>(this, 2, "left-border");
        setIDSafe<CCSprite>(this, 3, "right-border");
    }

    setIDSafe<CCLabelBMFont>(this, 0, "title");
}