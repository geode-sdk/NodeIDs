#include <Geode/Geode.hpp>
#include <Geode/modify/LevelSettingsLayer.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(LevelSettingsLayer) {
	/*
		This layer is used in two places:
		1. Start Pos menu, which has fewer buttons and labels because you can't set colors or music.
		2. Level settings from the Editor UI button, which has song selection too.
	*/
	// Common elements with the same indexes
	m_mainLayer->getChildByType<CCScale9Sprite>(0)->setID("background");

	bool isStartPos = m_mainLayer->getChildrenCount() < 15;  // Startpos has 13, level settings has 22 by default
	if (isStartPos) {
		m_mainLayer->getChildByType<CCScale9Sprite>(1)->setID("order-background");
		m_mainLayer->getChildByType<CCScale9Sprite>(2)->setID("channel-background");

		m_mainLayer->getChildByType<CCLabelBMFont>(0)->setID("disable-label");
		m_mainLayer->getChildByType<CCLabelBMFont>(1)->setID("reset-camera-label");
		m_mainLayer->getChildByType<CCLabelBMFont>(2)->setID("target-order-label");
		m_mainLayer->getChildByType<CCLabelBMFont>(3)->setID("target-channel-label");

		m_mainLayer->getChildByType<CCLabelBMFont>(4)->setID("speed-label");
		m_mainLayer->getChildByType<CCLabelBMFont>(5)->setID("mode-label");
		m_mainLayer->getChildByType<CCLabelBMFont>(6)->setID("options-label");

		m_mainLayer->getChildByType<CCTextInputNode>(0)->setID("order-input");
		m_mainLayer->getChildByType<CCTextInputNode>(1)->setID("channel-input");

		if (auto menu = m_mainLayer->getChildByType<CCMenu>(0)) {
			menu->setID("main-menu");

			menu->getChildByType<CCMenuItemSpriteExtra>(0)->setID("ok-button");

			menu->getChildByType<CCMenuItemSpriteExtra>(1)->setID("speed-button");
			menu->getChildByType<CCMenuItemSpriteExtra>(2)->setID("mode-button");
			menu->getChildByType<CCMenuItemSpriteExtra>(3)->setID("options-button");

			menu->getChildByType<CCMenuItemToggler>(0)->setID("disable-toggle");
			menu->getChildByType<CCMenuItemToggler>(1)->setID("reset-camera-toggle");
		}
	}
	else {
		m_mainLayer->getChildByType<CCScale9Sprite>(1)->setID("song-background");

		m_mainLayer->getChildByType<CCLabelBMFont>(0)->setID("select-color-label");
		m_mainLayer->getChildByType<CCLabelBMFont>(1)->setID("bg-color-label");
		m_mainLayer->getChildByType<CCLabelBMFont>(2)->setID("g-color-label");
		m_mainLayer->getChildByType<CCLabelBMFont>(3)->setID("g2-color-label");
		m_mainLayer->getChildByType<CCLabelBMFont>(4)->setID("line-color-label");
		m_mainLayer->getChildByType<CCLabelBMFont>(5)->setID("mg-color-label");
		m_mainLayer->getChildByType<CCLabelBMFont>(6)->setID("mg2-color-label");
		m_mainLayer->getChildByType<CCLabelBMFont>(7)->setID("more-color-label");

		m_mainLayer->getChildByType<CCLabelBMFont>(8)->setID("game-type-label");  // Only one that doesn't follow the order after z ordering

		m_mainLayer->getChildByType<CCLabelBMFont>(9)->setID("bg-label");
		m_mainLayer->getChildByType<CCLabelBMFont>(10)->setID("g-label");
		m_mainLayer->getChildByType<CCLabelBMFont>(11)->setID("mg-label");

		m_mainLayer->getChildByType<CCLabelBMFont>(12)->setID("select-song-label");
		m_mainLayer->getChildByType<CCLabelBMFont>(13)->setID("song-label");

		m_mainLayer->getChildByType<CCLabelBMFont>(14)->setID("speed-label");
		m_mainLayer->getChildByType<CCLabelBMFont>(15)->setID("mode-label");
		m_mainLayer->getChildByType<CCLabelBMFont>(16)->setID("options-label");

		if (auto menu = m_mainLayer->getChildByType<CCMenu>(0)) {
			menu->setID("main-menu");

			menu->getChildByType<CCMenuItemSpriteExtra>(0)->setID("bg-color-button");
			menu->getChildByType<CCMenuItemSpriteExtra>(1)->setID("g-color-button");
			menu->getChildByType<CCMenuItemSpriteExtra>(2)->setID("g2-color-button");
			menu->getChildByType<CCMenuItemSpriteExtra>(3)->setID("line-color-button");
			menu->getChildByType<CCMenuItemSpriteExtra>(4)->setID("mg-color-button");
			menu->getChildByType<CCMenuItemSpriteExtra>(5)->setID("mg2-color-button");
			menu->getChildByType<CCMenuItemSpriteExtra>(6)->setID("more-color-button");

			menu->getChildByType<CCMenuItemSpriteExtra>(7)->setID("bg-color-quick-edit-button");
			menu->getChildByType<CCMenuItemSpriteExtra>(8)->setID("g-color-quick-edit-button");
			menu->getChildByType<CCMenuItemSpriteExtra>(9)->setID("g2-color-quick-edit-button");
			menu->getChildByType<CCMenuItemSpriteExtra>(10)->setID("line-color-quick-edit-button");
			menu->getChildByType<CCMenuItemSpriteExtra>(11)->setID("mg-color-quick-edit-button");
			menu->getChildByType<CCMenuItemSpriteExtra>(12)->setID("mg2-color-quick-edit-button");

			menu->getChildByType<CCMenuItemSpriteExtra>(13)->setID("classic-button");
			menu->getChildByType<CCMenuItemSpriteExtra>(14)->setID("platformer-button");

			menu->getChildByType<CCMenuItemSpriteExtra>(15)->setID("bg-button");
			menu->getChildByType<CCMenuItemSpriteExtra>(16)->setID("g-button");
			menu->getChildByType<CCMenuItemSpriteExtra>(17)->setID("mg-button");
			menu->getChildByType<CCMenuItemSpriteExtra>(18)->setID("font-button");

			menu->getChildByType<CCMenuItemSpriteExtra>(19)->setID("ok-button");

			menu->getChildByType<CCMenuItemSpriteExtra>(20)->setID("prev-song-button");
			menu->getChildByType<CCMenuItemSpriteExtra>(21)->setID("next-song-button");
			menu->getChildByType<CCMenuItemSpriteExtra>(22)->setID("normal-song-button");
			menu->getChildByType<CCMenuItemSpriteExtra>(23)->setID("custom-song-button");
			menu->getChildByType<CCMenuItemSpriteExtra>(24)->setID("select-custom-song-button");
			menu->getChildByType<CCMenuItemSpriteExtra>(25)->setID("new-song-button");

			menu->getChildByType<CCMenuItemSpriteExtra>(26)->setID("speed-button");
			menu->getChildByType<CCMenuItemSpriteExtra>(27)->setID("mode-button");
			menu->getChildByType<CCMenuItemSpriteExtra>(28)->setID("options-button");
		}

		/*
			Unset because they are unique:
			- CustomSongWidget
			- SongSelectNode
		*/
	}
}

struct LevelSettingsLayerIDs : Modify<LevelSettingsLayerIDs, LevelSettingsLayer> {
    static void onModify(auto& self) {
	    if (!self.setHookPriority("LevelSettingsLayer::init", GEODE_ID_PRIORITY)) {
		    log::warn("Failed to set LevelSettingsLayer::init hook priority, node IDs may not work properly");
		}
	}

	bool init(LevelSettingsObject* levelSettings, LevelEditorLayer* editor) {
	    if (!LevelSettingsLayer::init(levelSettings, editor)) return false;
	
	    NodeIDs::get()->provide(this);

	    return true;
	}
};
