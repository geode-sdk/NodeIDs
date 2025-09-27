// #include "AddIDs.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/GJLevelScoreCell.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(GJLevelScoreCell) {
	if (!m_userScore) return;

	setIDs(
	    m_mainLayer,
	    0,
	    "player-icon",
	    "main-menu", (this->m_userScore->m_playerRank >= 4 ? "rank-label" : "rank-icon"),"percentage-label","date-label");
	if (auto menu = m_mainLayer->getChildByID("main-menu")) {
		if (menu->getChildrenCount() > 0) {
			static_cast<CCNode *>(menu->getChildren()->objectAtIndex(0))->setID("player-name");
		}
	}
}

struct GJLevelScoreCellIDs : Modify<GJLevelScoreCellIDs, GJLevelScoreCell> {
	static void onModify(auto &self) {
		if (!self.setHookPriority("GJLevelScoreCell::loadFromScore", GEODE_ID_PRIORITY)) {
			log::warn("Failed to set GJLevelScoreCell::loadFromScore hook priority, node IDs may not work properly");
		}
	}

	void loadFromScore(GJUserScore *score) {
		GJLevelScoreCell::loadFromScore(score);

		NodeIDs::get()->provide(this);
	}
};
