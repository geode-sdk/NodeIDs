#include <Geode/Geode.hpp>
#include <Geode/modify/SetupMoveCommandPopup.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(SetupMoveCommandPopup) {
	auto mainLayer = setIDSafe<CCLayer>(this, 0, "main-layer");
	if (mainLayer) {
		/* Number Input Backgrounds */
		setIDSafe<CCScale9Sprite>(mainLayer, 0, "background");
		setIDSafe<CCScale9Sprite>(mainLayer, 1, "move-x-background");
		setIDSafe<CCScale9Sprite>(mainLayer, 2, "move-y-background");
		setIDSafe<CCScale9Sprite>(mainLayer, 3, "mod-x-background");
		setIDSafe<CCScale9Sprite>(mainLayer, 4, "mod-y-background");
		setIDSafe<CCScale9Sprite>(mainLayer, 5, "center-group-id-background");
		setIDSafe<CCScale9Sprite>(mainLayer, 6, "target-pos-group-id-background");
		setIDSafe<CCScale9Sprite>(mainLayer, 7, "distance-background");
		setIDSafe<CCScale9Sprite>(mainLayer, 8, "move-time-background");
		setIDSafe<CCScale9Sprite>(mainLayer, 9, "target-group-id-background");

		/* Labels */
		setIDSafe<CCLabelBMFont>(mainLayer, 0, "trigger-name-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 1, "touch-trigger-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 2, "spawn-trigger-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 3, "multi-trigger-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 4, "move-x-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 5, "move-y-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 6, "mod-x-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 7, "mod-y-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 8, "lock-x-header");
		setIDSafe<CCLabelBMFont>(mainLayer, 9, "lock-player-x-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 10, "lock-camera-x-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 11, "lock-y-header");
		setIDSafe<CCLabelBMFont>(mainLayer, 12, "lock-player-y-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 13, "lock-camera-y-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 14, "center-group-id-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 15, "center-group-id-shadow");
		setIDSafe<CCLabelBMFont>(mainLayer, 16, "center-group-id-name");
		setIDSafe<CCLabelBMFont>(mainLayer, 17, "target-pos-group-id-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 18, "target-pos-group-id-shadow");
		setIDSafe<CCLabelBMFont>(mainLayer, 19, "target-pos-group-id-name");
		setIDSafe<CCLabelBMFont>(mainLayer, 20, "target-pos-p1-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 21, "target-pos-p2-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 22, "target-x-only-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 23, "target-y-only-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 24, "distance-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 25, "target-mode-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 26, "direction-mode-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 27, "small-step-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 28, "dynamic-mode-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 29, "move-time-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 30, "easing-mode-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 31, "current-easing-mode");
		setIDSafe<CCLabelBMFont>(mainLayer, 32, "target-group-id-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 33, "target-group-id-shadow");
		setIDSafe<CCLabelBMFont>(mainLayer, 34, "target-group-id-name");
		setIDSafe<CCLabelBMFont>(mainLayer, 35, "silent-label");

		/* Sliders */
		setIDSafe<Slider>(mainLayer, 0, "move-x-slider");
		setIDSafe<Slider>(mainLayer, 1, "move-y-slider");
		setIDSafe<Slider>(mainLayer, 2, "mod-x-slider");
		setIDSafe<Slider>(mainLayer, 3, "mod-y-slider");
		setIDSafe<Slider>(mainLayer, 4, "distance-slider");
		setIDSafe<Slider>(mainLayer, 5, "move-time-slider");

		/* Text Inputs */
		setIDSafe<CCTextInputNode>(mainLayer, 0, "move-x-input");
		setIDSafe<CCTextInputNode>(mainLayer, 1, "move-y-input");
		setIDSafe<CCTextInputNode>(mainLayer, 2, "mod-x-input");
		setIDSafe<CCTextInputNode>(mainLayer, 3, "mod-y-input");
		setIDSafe<CCTextInputNode>(mainLayer, 4, "center-group-id-input");
		setIDSafe<CCTextInputNode>(mainLayer, 5, "target-pos-group-id-input");
		setIDSafe<CCTextInputNode>(mainLayer, 6, "distance-input");
		setIDSafe<CCTextInputNode>(mainLayer, 7, "move-time-input");
		setIDSafe<CCTextInputNode>(mainLayer, 8, "target-group-id-input");

		/* The CCMenu */
		auto inputMenu = setIDSafe<CCMenu>(mainLayer, 0, "input-menu");
		if (inputMenu) {
			/* Togglers */
			setIDSafe<CCMenuItemToggler>(inputMenu, 0, "touch-trigger-toggle");
			setIDSafe<CCMenuItemToggler>(inputMenu, 1, "spawn-trigger-toggle");
			setIDSafe<CCMenuItemToggler>(inputMenu, 2, "multi-trigger-toggle");
			setIDSafe<CCMenuItemToggler>(inputMenu, 3, "lock-player-x-toggle");
			setIDSafe<CCMenuItemToggler>(inputMenu, 4, "lock-camera-x-toggle");
			setIDSafe<CCMenuItemToggler>(inputMenu, 5, "lock-player-y-toggle");
			setIDSafe<CCMenuItemToggler>(inputMenu, 6, "lock-camera-y-toggle");
			setIDSafe<CCMenuItemToggler>(inputMenu, 7, "target-pos-p1-toggle");
			setIDSafe<CCMenuItemToggler>(inputMenu, 8, "target-pos-p2-toggle");
			setIDSafe<CCMenuItemToggler>(inputMenu, 9, "target-x-only-toggle");
			setIDSafe<CCMenuItemToggler>(inputMenu, 10, "target-y-only-toggle");
			setIDSafe<CCMenuItemToggler>(inputMenu, 11, "target-mode-toggle");
			setIDSafe<CCMenuItemToggler>(inputMenu, 12, "direction-mode-toggle");
			setIDSafe<CCMenuItemToggler>(inputMenu, 13, "small-step-toggle");
			setIDSafe<CCMenuItemToggler>(inputMenu, 14, "dynamic-mode-toggle");
			setIDSafe<CCMenuItemToggler>(inputMenu, 15, "silent-toggle");

			/* CCMenuItemSpriteExtra */
			setIDSafe<CCMenuItemSpriteExtra>(inputMenu, 0, "ok-button");
			setIDSafe<CCMenuItemSpriteExtra>(inputMenu, 1, "info-button");
			setIDSafe<CCMenuItemSpriteExtra>(inputMenu, 2, "center-group-id-left");
			setIDSafe<CCMenuItemSpriteExtra>(inputMenu, 3, "center-group-id-right");
			setIDSafe<CCMenuItemSpriteExtra>(inputMenu, 4, "center-group-id-next");
			setIDSafe<CCMenuItemSpriteExtra>(inputMenu, 5, "center-group-id-search");
			setIDSafe<CCMenuItemSpriteExtra>(inputMenu, 6, "target-pos-group-id-left");
			setIDSafe<CCMenuItemSpriteExtra>(inputMenu, 7, "target-pos-group-id-right");
			setIDSafe<CCMenuItemSpriteExtra>(inputMenu, 8, "target-pos-group-id-next");
			setIDSafe<CCMenuItemSpriteExtra>(inputMenu, 9, "target-pos-group-id-search");
			setIDSafe<CCMenuItemSpriteExtra>(inputMenu, 10, "edit-easing-rate");
			setIDSafe<CCMenuItemSpriteExtra>(inputMenu, 11, "easing-options	");
			setIDSafe<CCMenuItemSpriteExtra>(inputMenu, 12, "easing-right");
			setIDSafe<CCMenuItemSpriteExtra>(inputMenu, 13, "easing-left");
			setIDSafe<CCMenuItemSpriteExtra>(inputMenu, 14, "target-group-id-left");
			setIDSafe<CCMenuItemSpriteExtra>(inputMenu, 15, "target-group-id-right");
			setIDSafe<CCMenuItemSpriteExtra>(inputMenu, 16, "target-group-id-next");
			setIDSafe<CCMenuItemSpriteExtra>(inputMenu, 17, "target-group-id-search");
		}
	}
}

struct SetupMoveCommandPopupIDs : Modify<SetupMoveCommandPopupIDs, SetupMoveCommandPopup> {
	static void onModify(auto& self) {
		if (!self.setHookPriority("SetupMoveCommandPopup::init", GEODE_ID_PRIORITY)) {
			log::warn("Failed to set SetupMoveCommandPopup::init hook priority, node IDs may not work properly");
		}
	}

	bool init(EffectGameObject* p0, CCArray* p1) {
		if (!SetupMoveCommandPopup::init(p0, p1)) return false;

		NodeIDs::get()->provide(this);

		return true;
	}
};
