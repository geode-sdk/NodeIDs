#include <Geode/Bindings.hpp>
#include <Geode/modify/MoreSearchLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(MoreSearchLayer) {
	if (auto mainLayer = setIDSafe<CCLayer>(this, 0, "main-layer")) {
		setIDSafe<CCScale9Sprite>(mainLayer, 0, "background");
		setIDSafe<CCScale9Sprite>(mainLayer, 1, "custom-song-id-input-bg");
		
		setIDSafe<CCLabelBMFont>(mainLayer, 0, "advanced-options-label");
		
		setIDSafe<CCLabelBMFont>(mainLayer, 1, "uncompleted-filter-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 2, "completed-filter-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 3, "original-filter-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 4, "coins-filter-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 5, "two-player-filter-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 6, "song-filter-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 7, "no-star-filter-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 8, "featured-filter-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 9, "epic-filter-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 10, "legendary-filter-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 11, "mythic-filter-label");
		
		setIDSafe<CCLabelBMFont>(mainLayer, 12, "select-song-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 13, "normal-song-label");
		
		
		setIDSafe<CCTextInputNode>(mainLayer, 0, "song-id-input");
		
		if (auto mainMenu = setIDSafe<CCMenu>(mainLayer, 0, "main-menu")) {
			setIDSafe<CCMenuItemSpriteExtra>(mainMenu, 0, "close-button");
			
			setIDSafe<CCMenuItemToggler>(mainMenu, 0, "uncompleted-filter-toggler");
			setIDSafe<CCMenuItemToggler>(mainMenu, 1, "completed-filter-toggler");
			setIDSafe<CCMenuItemToggler>(mainMenu, 2, "original-filter-toggler");
			setIDSafe<CCMenuItemToggler>(mainMenu, 3, "coins-filter-toggler");
			setIDSafe<CCMenuItemToggler>(mainMenu, 4, "two-player-filter-toggler");
			setIDSafe<CCMenuItemToggler>(mainMenu, 5, "song-filter-toggler");
			setIDSafe<CCMenuItemToggler>(mainMenu, 6, "no-star-filter-toggler");
			setIDSafe<CCMenuItemToggler>(mainMenu, 7, "featured-filter-toggler");
			setIDSafe<CCMenuItemToggler>(mainMenu, 8, "epic-filter-toggler");
			setIDSafe<CCMenuItemToggler>(mainMenu, 9, "legendary-filter-toggler");
			setIDSafe<CCMenuItemToggler>(mainMenu, 10, "mythic-filter-toggler");
			
			setIDSafe<CCMenuItemSpriteExtra>(mainMenu, 1, "normal-song-button");
			setIDSafe<CCMenuItemSpriteExtra>(mainMenu, 2, "custom-song-button");
			
			setIDSafe<CCMenuItemSpriteExtra>(mainMenu, 3, "prev-normal-song-button");
			setIDSafe<CCMenuItemSpriteExtra>(mainMenu, 4, "next-normal-song-button");
			
			setIDSafe<CCMenuItemSpriteExtra>(mainMenu, 5, "info-button");
		}
	}
}

struct MoreSearchLayerIDs : Modify<MoreSearchLayerIDs, MoreSearchLayer> {
	static void onModify(auto& self) {
		if (!self.setHookPriority("MoreSearchLayer::init", GEODE_ID_PRIORITY)) {
			log::warn("Failed to set MoreSearchLayer::init hook priority, node IDs may not work properly");
		}
	}

	bool init() {
		if (!MoreSearchLayer::init()) return false;

		NodeIDs::get()->provide(this);

		return true;
	}
};
