// #include "AddIDs.hpp"

#include <Geode/modify/GJScoreCell.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(GJScoreCell) {
    setIDs(
        m_mainLayer,
        0,
        "player-icon",
        "main-menu"
    );

    if(m_score->m_scoreType != 2) {
        setIDs(
            m_mainLayer,
            2,
            "rank-label"
        );
    }
    
    setIDs(
        m_mainLayer,
        m_score->m_scoreType == 2 ? 2 : 3,
        "stars-label",
        "stars-icon",
        "moons-label",
        "moons-icon",
        "diamonds-label",
        "diamonds-icon",
        "coins-label",
        "coins-icon",
        "user-coins-label",
        "user-coins-icon",
        "demons-label",
        "demons-icon",
        "creator-points-label",
        "creator-points-icon"
    );

    if(auto menu = m_mainLayer->getChildByID("main-menu")) {
        if(menu->getChildrenCount() > 0) {
            static_cast<CCNode*>(menu->getChildren()->objectAtIndex(0))->setID("player-name");
        }
    }
}

struct GJScoreCellIDs : Modify<GJScoreCellIDs, GJScoreCell> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("GJScoreCell::loadFromScore", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set GJScoreCell::loadFromScore hook priority, node IDs may not work properly");
        }
    }

    void loadFromScore(GJUserScore* score) {
        GJScoreCell::loadFromScore(score);

        NodeIDs::get()->provide(this);
    }
};
