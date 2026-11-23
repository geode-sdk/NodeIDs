#include <Geode/Bindings.hpp>
#include <Geode/modify/ShardsPage.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

static void assignUnlock(CCLayer* mainLayer, const char* type, size_t& idx, size_t& unlockableIdx) {
	setIDs(
		mainLayer,
		idx,
		fmt::format("{}-unlockable-{}-label", type, unlockableIdx).c_str(),
		fmt::format("{}-unlockable-{}-icon", type, unlockableIdx).c_str()
	);
	idx += 2;
	unlockableIdx++;
}

static void assignUnlocksRow(CCLayer* mainLayer, const char* type, size_t& idx) {
	setIDs(
		mainLayer,
		idx,
		fmt::format("{}-title", type).c_str(),
		fmt::format("{}-count", type).c_str(),
		fmt::format("{}-icon", type).c_str()
	);
	idx += 3;

	size_t unlockableIdx = 1;
	assignUnlock(mainLayer, type, idx, unlockableIdx);
	assignUnlock(mainLayer, type, idx, unlockableIdx);
	setIDSafe(mainLayer, idx++, fmt::format("{}-divider-{}", type, unlockableIdx - 1).c_str());
	assignUnlock(mainLayer, type, idx, unlockableIdx);
	setIDSafe(mainLayer, idx++, fmt::format("{}-divider-{}", type, unlockableIdx - 1).c_str());
	assignUnlock(mainLayer, type, idx, unlockableIdx);
	setIDSafe(mainLayer, idx++, fmt::format("{}-divider-{}", type, unlockableIdx - 1).c_str());
	assignUnlock(mainLayer, type, idx, unlockableIdx);
	setIDSafe(mainLayer, idx++, fmt::format("{}-divider-{}", type, unlockableIdx - 1).c_str());
}

$register_ids(ShardsPage) {
	if (auto mainLayer = setIDSafe<CCLayer>(this, 0, "main-layer")) {
		size_t idx = 0;
		setIDs(
			mainLayer,
			0,
			"background",
			"bottom-left-corner",
			"top-left-corner",
			"top-right-corner",
			"bottom-right-corner",
			"title-shards",
			"title-of",
			"title-power",
			"main-menu"
		);
		idx += 9;

		std::array unlockables = {"fire", "ice", "poison", "shadow", "lava", "bonus-one", "earth", "blood", "metal", "light", "soul", "bonus-two"};
		for(auto& unlockable : unlockables) {
			assignUnlocksRow(mainLayer, unlockable, idx);
		}

		if (auto mainMenu = setIDSafe<CCMenu>(mainLayer, 0, "main-menu")) {
			size_t offset = 0;
			setIDSafe<CCMenuItemSpriteExtra>(mainMenu, offset, "close-button");

			auto mainMenuChildren = CCArrayExt<CCNode*>(mainMenu->getChildren());
			for (size_t i = offset + 1; i < mainMenuChildren.size(); i++) {

				if (auto unlockable = typeinfo_cast<CCMenuItemSpriteExtra*>(mainMenuChildren[i])) {
					std::string shardType = "unknown";
					if (unlockable->getTag() < unlockables.size()) {
						shardType = unlockables[unlockable->getTag()];
					}
					else {
						log::warn("Unknown shard type for unlockable with tag {}", unlockable->getTag());
					}
					
					size_t column = i % 5;
					if (column == 0) { column = 5; }
					setIDSafe<CCMenuItemSpriteExtra>(
						mainMenu,
						i,
						fmt::format("{}-unlockable-{}", shardType, column)
					);
				}
			}
		}

		if (auto arrowButtonsMenu = setIDSafe<CCMenu>(mainLayer, 1, "arrow-buttons-menu")) {
			setIDSafe<CCMenuItemSpriteExtra>(arrowButtonsMenu, 0, "prev-button");
			setIDSafe<CCMenuItemSpriteExtra>(arrowButtonsMenu, 1, "next-button");
		}

		setIDSafe(mainLayer, mainLayer->getChildrenCount() - 1, "shards-tier-sprite");
	}
}

struct ShardsPageIDs : Modify<ShardsPageIDs, ShardsPage> {
	static void onModify(auto& self) {
		if (!self.setHookPriority("ShardsPage::init", GEODE_ID_PRIORITY)) {
			log::warn("Failed to set ShardsPage::init hook priority, node IDs may not work properly");
		}
	}

	bool init() {
		if (!ShardsPage::init()) return false;

		NodeIDs::get()->provide(this);

		return true;
	}
};
