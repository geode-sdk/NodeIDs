#include <Geode/Geode.hpp>
#include <Geode/modify/LevelSettingsLayer.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(LevelSettingsLayer) {
	m_mainLayer->getChildByType<CCScale9Sprite>(0)->setID("background");

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
