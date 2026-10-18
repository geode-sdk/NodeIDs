#include <Geode/Bindings.hpp>
#include <Geode/modify/ShardsPage.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(ShardsPage) {
	if (auto mainLayer = setIDSafe<CCLayer>(this, 0, "main-layer")) {
		setIDSafe<CCScale9Sprite>(mainLayer, 0, "background");
		if (auto mainMenu = setIDSafe<CCMenu>(mainLayer, 0, "main-menu")) {
			int offset = 0;
			setIDSafe<CCMenuItemSpriteExtra>(mainMenu, offset, "close-button");
			auto mainMenuChildren = CCArrayExt<CCNode*>(mainMenu->getChildren());
			for (int i = offset + 1; i < mainMenuChildren.size(); i++) {
				if (auto unlockable = typeinfo_cast<CCMenuItemSpriteExtra*>(mainMenuChildren[i])) {
					std::string shardType = "unknown";
					if (unlockable->getTag() == 0) { shardType = "fire"; }
					else if (unlockable->getTag() == 1) { shardType = "ice"; }
					else if (unlockable->getTag() == 2) { shardType = "poison"; }
					else if (unlockable->getTag() == 3) { shardType = "shadow"; }
					else if (unlockable->getTag() == 4) { shardType = "lava"; }
					else if (unlockable->getTag() == 5) { shardType = "bonus-one"; }
					else if (unlockable->getTag() == 6) { shardType = "earth"; }
					else if (unlockable->getTag() == 7) { shardType = "blood"; }
					else if (unlockable->getTag() == 8) { shardType = "metal"; }
					else if (unlockable->getTag() == 9) { shardType = "light"; }
					else if (unlockable->getTag() == 10) { shardType = "soul"; }
					else if (unlockable->getTag() == 11) { shardType = "bonus-two"; }
					int column = i % 5;
					if (column == 0) { column = 5; }
					setIDSafe<CCMenuItemSpriteExtra>(
						mainMenu,
						i,
						fmt::format(
							"{}-unlockable-{}",
							shardType,
							column
						).c_str()
					);
				}
			}
		}
		if (auto arrowButtonsMenu = setIDSafe<CCMenu>(mainLayer, 1, "arrow-buttons-menu")) {
			setIDSafe<CCMenuItemSpriteExtra>(arrowButtonsMenu, 0, "prev-button");
			setIDSafe<CCMenuItemSpriteExtra>(arrowButtonsMenu, 1, "next-button");
		}
		auto mainLayerChildren = CCArrayExt<CCNode*>(mainLayer->getChildren());
		for (int i = mainLayerChildren.size(); i-- > 0; ) {
			if (auto tierSprite = typeinfo_cast<CCSprite*>(mainLayerChildren[i])) {
				tierSprite->setID("shards-tier-sprite");
				break; // only set *one* of the sprites to that specific node ID
			}
		}
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
