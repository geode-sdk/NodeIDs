#include <Geode/Bindings.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(LevelEditorLayer) {
	setIDSafe<GJEffectManager>(this, 0, "effect-manager");
    
	if (auto shaderLayer = getChildOfType<ShaderLayer>(this, 0)) {
		setIDSafe(shaderLayer, 1, "main-node");
		setIDSafe<CCSprite>(static_cast<CCNode*>(shaderLayer->getChildren()->objectAtIndex(1)), 0, "background");
	} else {
		setIDSafe(this, 1, "main-node");
		setIDSafe<CCSprite>(static_cast<CCNode*>(this->getChildren()->objectAtIndex(1)), 0, "background");
	}
}

struct LevelEditorLayerIDs : Modify<LevelEditorLayerIDs, LevelEditorLayer> {
	static void onModify(auto& self) {
		if (!self.setHookPriority("LevelEditorLayer::init", GEODE_ID_PRIORITY)) {
			log::warn("Failed to set LevelEditorLayer::init hook priority, node IDs may not work properly");
		}
	}
	
	bool init(GJGameLevel* level, bool p1) {
		if (!LevelEditorLayer::init(level, p1)) return false;

		NodeIDs::get()->provide(this);

		return true;
	}
};