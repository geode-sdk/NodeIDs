#include <Geode/Bindings.hpp>
#include <Geode/modify/DemonFilterSelectLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(DemonFilterSelectLayer) {
	if (auto mainLayer = setIDSafe<CCLayer>(this, 0, "main-layer")) {
		setIDSafe<CCScale9Sprite>(mainLayer, 0, "background");
		setIDSafe<CCLabelBMFont>(mainLayer, 0, "demon-filter-text");
		if (auto demonFilters = setIDSafe<CCMenu>(mainLayer, 0, "demon-filters")) {
			auto demonFiltersChildren = CCArrayExt<CCNode*>(demonFilters->getChildren());
			for (int i = 0; i < demonFiltersChildren.size(); i++) {
				if (auto child = typeinfo_cast<CCMenuItemSpriteExtra*>(demonFiltersChildren[i])) {
					if (child->getTag() != -1) {
						std::string prefix = "unknown";
						if (child->getTag() == 0) { prefix = "all"; }
						else if (child->getTag() == 6) { prefix = "hard"; }
						else if (child->getTag() == 7) { prefix = "easy"; }
						else if (child->getTag() == 8) { prefix = "medium"; }
						else if (child->getTag() == 9) { prefix = "insane"; }
						else if (child->getTag() == 10) { prefix = "extreme"; }
						setIDSafe<CCMenuItemSpriteExtra>(
							demonFilters,
							i,
							fmt::format(
								"{}-demon-filter-button",
								prefix
							).c_str()
						);
					} else {
						setIDSafe<CCMenuItemSpriteExtra>(demonFilters, i, "close-button");
					}
				}
			}
		}
	}
}

struct DemonFilterSelectLayerIDs : Modify<DemonFilterSelectLayerIDs, DemonFilterSelectLayer> {
	static void onModify(auto& self) {
		if (!self.setHookPriority("DemonFilterSelectLayer::init", GEODE_ID_PRIORITY)) {
			log::warn("Failed to set DemonFilterSelectLayer::init hook priority, node IDs may not work properly");
		}
	}

	bool init() {
		if (!DemonFilterSelectLayer::init()) return false;

		NodeIDs::get()->provide(this);

		return true;
	}
};
