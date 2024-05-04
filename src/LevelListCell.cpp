#include <Geode/Bindings.hpp>
#include <Geode/modify/LevelListCell.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(LevelListCell) {
	setIDSafe<CCLayerColor>(this, 0, "background");
	
	if (auto mainLayer = setIDSafe<CCLayer>(this, 1, "main-layer")) {
		if (auto mainMenu = setIDSafe<CCMenu>(mainLayer, 0, "main-menu")) {
			setIDSafe<CCSprite>(mainLayer, 0, "difficulty-sprite");
			setIDSafe<CCMenuItemSpriteExtra>(mainMenu, 0, "view-button");
			setIDSafe<CCMenuItemSpriteExtra>(mainMenu, 1, "creator-name");
			setIDSafe<CCMenuItemSpriteExtra>(mainMenu, 2, "info-button");
			
			std::map<const char*, const char*> frameToNodeID = {
				{ "GJ_likesIcon_001.png", "likes-icon" },
				{ "GJ_downloadsIcon_001.png", "downloads-icon" },
				{ "GJ_featuredCoin_001.png", "featured-icon" },
				{ "GJ_completesIcon_001.png", "completion-icon" }
			};
	
			for (auto &entry : frameToNodeID) {
				if (auto icon = ::getChildBySpriteFrameName(mainLayer, entry.first)) {
					icon->setID(entry.second);
				}
			}
			
			if (auto diamondIcon = ::getChildBySpriteFrameName(mainLayer, "diamond_small01_001.png")) {
				diamondIcon->setID("diamond-icon");
				setIDSafe<CCLabelBMFont>(mainLayer, 0, "diamond-label");
				setIDSafe<CCLabelBMFont>(mainLayer, 1, "list-name-label");
				setIDSafe<CCLabelBMFont>(mainLayer, 2, "progress-label");
				setIDSafe<CCLabelBMFont>(mainLayer, 3, "downloads-label");
				setIDSafe<CCLabelBMFont>(mainLayer, 4, "likes-label");
				setIDSafe<CCLabelBMFont>(mainLayer, 5, "completion-label");
			} else {
				setIDSafe<CCLabelBMFont>(mainLayer, 0, "list-name-label");
				setIDSafe<CCLabelBMFont>(mainLayer, 1, "progress-label");
				setIDSafe<CCLabelBMFont>(mainLayer, 2, "downloads-label");
				setIDSafe<CCLabelBMFont>(mainLayer, 3, "likes-label");
			}
			
			auto mainLayerChildren = CCArrayExt<CCNode*>(mainLayer->getChildren());
			
			for (int i = 0; i < mainLayerChildren.size(); i++) {
				if (auto theObject = typeinfo_cast<CCLabelBMFont*>(mainLayerChildren[i])) {
					if (theObject->getID() == "progress-label") {
						if (auto theSprite = typeinfo_cast<CCSprite*>(mainLayerChildren[i - 1])) {
							theSprite->setID("progress-bar");
							if (getChildByIDRecursive("completion-label")) {
								if (auto theOtherSprite = typeinfo_cast<CCSprite*>(mainLayerChildren[12])) {
									if (theOtherSprite->getID() == "") {
										theOtherSprite->setID("completion-diamond");
									}
								}
							}
							break;
						}
					}
				}
			}
			
			if (!(getChildByIDRecursive("downloads-icon") && getChildByIDRecursive("likes-icon"))) {
				mainLayerChildren[5]->setID("info-sprite");
				if (auto theChild = typeinfo_cast<CCLabelBMFont*>(mainLayerChildren[6])) {
					if (strcmp(theChild->getID().c_str(), "downloads-label") == 0) {
						if (strcmp(theChild->getString(), "Unpublished") == 0) {
							theChild->setID("unpublished-label");
						} else if (strcmp(theChild->getString(), "Uploaded") == 0) {
							theChild->setID("uploaded-label");
						} else {
							theChild->setID("unknown-info-label");
						}
					}
				}
			}
		}
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