#include <Geode/Bindings.hpp>
#include <Geode/modify/LevelListCell.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(LevelListCell) {
	setIDSafe<CCLayerColor>(this, 0, "background");
	auto mainLayer = setIDSafe<CCLayer>(this, 1, "main-layer");

	bool hasReward = m_levelList->m_diamonds > 0 && m_levelList->m_levelsToClaim > 0;
	bool isClaimed = hasReward && GameStatsManager::sharedState()->hasClaimedListReward(m_levelList);

	size_t i = 0;
	setIDSafe(mainLayer, i++, "difficulty-sprite");

	if (hasReward) {
		setIDSafe(mainLayer, i++, "diamond-icon");
		setIDSafe(mainLayer, i++, "diamond-label");
	}

	if (m_levelList->m_featured) {
		setIDSafe(mainLayer, i++, "featured-icon");
	}

	setIDSafe(mainLayer, i++, "list-name-label");

	if (m_levelList->m_listRevision > 0) {
		setIDSafe(mainLayer, i++, "revision-label");
	}

	setIDSafe(mainLayer, i++, "main-menu");
	setIDSafe(mainLayer, i++, "progress-bar");
	setIDSafe(mainLayer, i++, "progress-label");

	if (m_levelList->m_listType == GJLevelType::Editor) {
		setIDSafe(mainLayer, i++, "info-sprite");
		setIDSafe(mainLayer, i++, "info-label");
	} else {
		setIDSafe(mainLayer, i++, "downloads-icon");
		setIDSafe(mainLayer, i++, "likes-icon");
		setIDSafe(mainLayer, i++, "downloads-label");
		setIDSafe(mainLayer, i++, "likes-label");
		if (hasReward && !isClaimed) {
			setIDSafe(mainLayer, i++, "completion-diamond");
			setIDSafe(mainLayer, i++, "completion-icon");
			setIDSafe(mainLayer, i++, "completion-label");
		}
	}

	if (auto menu = mainLayer->getChildByID("main-menu")) {
		setIDSafe(menu, 0, "view-button");
		setIDSafe(menu, 1, "creator-name");
		setIDSafe(menu, 2, "info-button");
	}
}

struct LevelListCellIDs : Modify<LevelListCellIDs, LevelListCell> {
	static void onModify(auto& self) {
		if (!self.setHookPriority("LevelListCell::loadFromList", GEODE_ID_PRIORITY)) {
			log::warn("Failed to set LevelListCell::loadFromList hook priority, node IDs may not work properly");
		}
	}

	void loadFromList(GJLevelList* p0) {
		LevelListCell::loadFromList(p0);

		NodeIDs::get()->provide(this);
	}
};