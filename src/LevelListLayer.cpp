// #include <Geode/Bindings.hpp>
// #include <Geode/modify/LevelListLayer.hpp>
// #include <Geode/utils/cocos.hpp>
// #include <Geode/ui/BasedButtonSprite.hpp>
// #include <Geode/utils/NodeIDs.hpp>

// using namespace geode::prelude;
// using namespace geode::node_ids;

// $register_ids(LevelListLayer) {
// 	setIDSafe<CCSprite>(this, 0, "background");
// 	setIDSafe<CCSprite>(this, 1, "bottom-left-corner");
// 	setIDSafe<CCSprite>(this, 2, "bottom-right-corner");
	
// 	setIDSafe<CCScale9Sprite>(this, 0, "list-title-input-bg");
// 	setIDSafe<CCTextInputNode>(this, 0, "list-title-input");
	
// 	setIDSafe<LoadingCircle>(this, 0, "loading-circle");
	
// 	setIDSafe<TextArea>(this, 0, "no-internet-label");
	
// 	bool isPublishedList = (!getChildByIDRecursive("list-title-input-bg") && !getChildByIDRecursive("list-title-input"));
	
// 	if (isPublishedList) {
// 		setIDSafe<CCLabelBMFont>(this, 0, "title-label");
// 		setIDSafe<CCLabelBMFont>(this, 1, "progress-label");
// 		setIDSafe<CCLabelBMFont>(this, 2, "downloads-label");
// 		setIDSafe<CCLabelBMFont>(this, 3, "likes-label");
// 	} else {
// 		if (!getChildByIDRecursive("list-title-input")) {
// 			setIDSafe<CCLabelBMFont>(this, 1, "progress-label");
// 			setIDSafe<CCLabelBMFont>(this, 0, "published-list-label");
// 		} else {
// 			setIDSafe<CCLabelBMFont>(this, 0, "progress-label");
// 		}
// 	}
	
// 	std::map<const char*, const char*> frameToNodeID = {
// 		{ "GJ_likesIcon_001.png", "likes-icon" },
// 		{ "GJ_downloadsIcon_001.png", "downloads-icon" },
// 		{ "GJ_featuredCoin_001.png", "featured-icon" }
// 	};
	
// 	for (auto &entry : frameToNodeID) {
// 		if (auto icon = ::getChildBySpriteFrameName(this, entry.first)) {
// 			icon->setID(entry.second);
// 		}
// 	}
	
// 	if (auto diamondsIcon = ::getChildBySpriteFrameName(this, "GJ_diamondsIcon_001.png")) {
// 		diamondsIcon->setID("diamonds-icon");
// 		setIDSafe<CCLabelBMFont>(this, 4, "diamonds-label");
// 	} else if (auto completetionIcon = ::getChildBySpriteFrameName(this, "GJ_completesIcon_001.png")) {
// 		completetionIcon->setID("completion-icon");
// 		setIDSafe<CCLabelBMFont>(this, 4, "completion-label");
// 	}
	
// 	bool isIncompleteRatedList = getChildByIDRecursive("completion-icon");
	
// 	if (auto menu = setIDSafe<CCMenu>(this, 0, "main-menu")) {
//         setIDs(menu, 0, "back-button");
//         if (auto backBtn = menu->getChildByID("back-button")) {
//             auto backMenu = detachAndCreateMenu(
//                 this,
//                 "back-menu",
//                 RowLayout::create()
//                     ->setAxisAlignment(AxisAlignment::Start),
//                 backBtn
//             );
//             backMenu->setContentSize({ 100.f, 50.f });
//             backMenu->setPositionX(
//                 backMenu->getPositionX() + 100.f / 2 - 
//                     getSizeSafe(backBtn).width / 2
//             );
//             backMenu->updateLayout();
//         }
	
// 		std::map<const char*, const char*> buttonToNodeID = {
// 			{ "GJ_deleteBtn_001.png", "delete-button" },
// 			{ "GJ_updateBtn_001.png", "refresh-button" },
// 			{ "GJ_chatBtn_001.png", "desc-button" },
// 			{ "GJ_infoBtn_001.png", "info-button" },
// 			{ "GJ_editModeBtn_001.png", "edit-button" },
// 			{ "GJ_duplicateBtn_001.png", "copy-button" },
// 			{ "GJ_shareBtn_001.png", "share-button" },
// 			{ "GJ_like2Btn_001.png", "like-button" },
// 			{ "GJ_like2Btn2_001.png", "like-button" },
// 			{ "GJ_plainBtn_001.png", "rate-button" },
// 			{ "gj_heartOff_001.png", "favorite-button" },
// 			{ "gj_heartOn_001.png", "favorite-button" },
// 			{ "GJ_infoIcon_001.png", "info-icon" }
// 		};
	
// 		for (auto& entry : buttonToNodeID) {
// 			if (auto icon = getChildBySpriteFrameName(menu, entry.first)) {
// 				icon->setID(entry.second);
// 			}
// 		}
		
// 		if (isPublishedList) {
// 			setIDSafe(menu, 1, "creator-name");
// 			if (auto creatorBtn = menu->getChildByID("creator-name")) {
// 				auto creatorMenu = detachAndCreateMenu(
// 					this,
// 					"creator-menu",
// 					RowLayout::create()
// 						->setAxisAlignment(AxisAlignment::Start),
// 					creatorBtn
// 				);
// 				creatorMenu->setContentSize({ 100.f, 50.f });
// 				creatorMenu->setPositionX(
// 					creatorMenu->getPositionX() + 100.f / 2 - 
// 						getSizeSafe(creatorBtn).width / 2
// 				);
// 				creatorMenu->updateLayout();
// 			}

// 			if (isIncompleteRatedList) {
// 				// todo: All the rewards stuff should in one menu with a ColumnLayout
// 				// for future proofing, this assigns the button and its contents an ID, but 
// 				// does NOT give its containing menu an ID as doing so would have to result in
// 				// an API break later on when the button gets moved into the proper menu
// 				setIDSafe(menu, 8, "claim-rewards-button");
// 				if (auto rewardsBtn = menu->getChildByID("claim-rewards-button")) {
// 					auto rewardsMenu = detachAndCreateMenu(this, "", nullptr, rewardsBtn);
// 					rewardsMenu->setAnchorPoint({ .5f, .5f });
// 					rewardsMenu->ignoreAnchorPointForPosition(false);
// 					rewardsMenu->setContentSize({ 50.f, 50.f });
// 					rewardsMenu->updateLayout();

// 					if (auto rewardsSpr = getChild(rewardsBtn, 0)) {
// 						setIDSafe(rewardsSpr, 0, "claim-rewards-sprite");
// 						setIDSafe(rewardsSpr, 1, "diamonds-sprite");
// 						setIDSafe(rewardsSpr, 2, "diamonds-label");
// 					}
// 				}
// 			}
// 		}
// 	}
	
// 	auto children = CCArrayExt<CCNode*>(getChildren());
// 	if (isPublishedList) {
// 		if (children[5]->getID() == "" && typeinfo_cast<CCSprite*>(children[5])) {
// 			children[5]->setID("difficulty-sprite");
// 			children[9]->setID("progress-bar");
// 			if (isIncompleteRatedList) {
// 				children[15]->setID("completion-diamond");
// 			}
// 		}
// 	} else {
// 		if (!getChildByIDRecursive("list-title-input")) {
// 			setIDSafe<CCLabelBMFont>(this, 0, "published-list-label");
// 			setIDSafe<CCLabelBMFont>(this, 1, "progress-label");
// 		}
// 		if (children[8]->getID() == "" && typeinfo_cast<CCSprite*>(children[8])) {
// 			children[8]->setID("progress-bar");
// 		}
// 	}
// }

// struct LevelListLayerIDs : Modify<LevelListLayerIDs, LevelListLayer> {
// 	static void onModify(auto& self) {
// 		if (!self.setHookPriority("LevelListLayer::init", GEODE_ID_PRIORITY)) {
// 			log::warn("Failed to set LevelListLayer::init hook priority, node IDs may not work properly");
// 		}
// 	}

// 	bool init(GJLevelList* p0) {
// 		if (!LevelListLayer::init(p0)) return false;

// 		NodeIDs::get()->provide(this);

// 		return true;
// 	}
// };
