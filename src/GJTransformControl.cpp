#include <Geode/Bindings.hpp>
#include <Geode/Enums.hpp>
#include <Geode/modify/GJTransformControl.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(GJTransformControl) {
    setContentSize({0.f, 0.f});
    ignoreAnchorPointForPosition(false);

    m_warpLockButton->setID("warp-lock-toggle");
    m_oppositeAnchorButton->setID("opposite-anchor-toggle");
    m_gridSnapButton->setID("grid-snap-toggle");
    m_freeRotationButton->setID("free-rotation-toggle");

    m_mainNode->setID("transform-container");
    m_mainNodeParent->setID("transform-node");

    auto togglesMenu = setIDSafe<CCMenu>(m_mainNodeParent, 0, "toggles-menu");
    if (togglesMenu) {
        togglesMenu->ignoreAnchorPointForPosition(false);
        togglesMenu->setLayout(SimpleRowLayout::create()
            ->setGap(5.f)
            ->setMainAxisScaling(AxisScaling::Fit)
            ->setCrossAxisScaling(AxisScaling::Fit)
        );

        togglesMenu->updateLayout();
    }

    std::vector<std::string> warpSpriteIDs = {
        "anchor",
        "center-left",
        "center-right",
        "center-top",
        "center-bottom",
        "top-left",
        "top-right",
        "bottom-left",
        "bottom-right",
        "warp-x",
        "warp-y",
        "rotation",
    };

    for (auto sprite : m_warpSprites->asExt<CCSprite>()) {
        if (sprite->getTag() - 1 >= warpSpriteIDs.size()) continue;

        sprite->setID(warpSpriteIDs[sprite->getTag() - 1]);
    }
}

struct GJTransformControlIDs : Modify<GJTransformControlIDs, GJTransformControl> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("GJTransformControl::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set GJTransformControl::init hook priority, node IDs may not work properly");
        }
    }

    bool init() {
        if (!GJTransformControl::init()) return false;

        NodeIDs::get()->provide(this);

        return true;
    }

};