// #include "AddIDs.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/GJLevelScoreCell.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(GJLevelScoreCell) {
	if (!m_userScore) return;
	int coins = m_userScore->m_scoreType == 1 ? 0 : m_userScore->m_secretCoins;

	setIDs(
	    m_mainLayer,
	    0,
	    "player-icon",
	    "main-menu",
		m_userScore->m_playerRank >= 4 ? "rank-label" : "rank-icon",
		"percentage-label"
	);

	for (size_t i = 0; i < coins; i++) {
		setIDSafe(m_mainLayer, 4 + i, fmt::format("user-coin-{}", i + 1));
	}
	
	setIDSafe(m_mainLayer, 4 + coins, "date-label");

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
