#include <Geode/Bindings.hpp>
#include <Geode/modify/GJDropDownLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(GJDropDownLayer) {
    m_mainLayer->setID("main-layer");
    m_listLayer->setID("list-layer");
    m_buttonMenu->setID("back-button");

    setIDSafe<CCSprite>(m_mainLayer, 0, "left-chain");
    setIDSafe<CCSprite>(m_mainLayer, 1, "right-chain");
}

struct GJDropDownLayerIDs : Modify<GJDropDownLayerIDs, GJDropDownLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("GJDropDownLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set GJDropDownLayer::init hook priority, node IDs may not work properly");
        }
    }

#if GEODE_COMP_GD_VERSION >= 22004
    bool init(char const* p0, float p1, bool p2) {
        if (!GJDropDownLayer::init(p0, p1, p2))
            return false;

        NodeIDs::get()->provide(this);
        return true;
    }
#else
    bool init(char const* p0, float p1) {
        if (!GJDropDownLayer::init(p0, p1))
            return false;

        NodeIDs::get()->provide(this);
        return true;
    }
#endif
    
};