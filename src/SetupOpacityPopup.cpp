#include <Geode/Geode.hpp>
#include <Geode/modify/SetupOpacityPopup.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(SetupOpacityPopup) {
	auto mainLayer = setIDSafe<CCLayer>(this, 0, "main-layer");
	if (mainLayer) {
		setIDSafe<CCScale9Sprite>(mainLayer, 0, "background");
		setIDSafe<CCScale9Sprite>(mainLayer, 1, "group-id-background");
		setIDSafe<CCScale9Sprite>(mainLayer, 2, "fade-time-background");

		setIDSafe<CCLabelBMFont>(mainLayer, 0, "title-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 1, "group-id-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 2, "fade-time-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 3, "opacity-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 4, "touch-trigger-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 5, "spawn-trigger-label");
		setIDSafe<CCLabelBMFont>(mainLayer, 6, "multi-trigger-label");

		setIDSafe<Slider>(mainLayer, 0, "fade-time-slider");
		setIDSafe<Slider>(mainLayer, 1, "opacity-slider");

		setIDSafe<CCTextInputNode>(mainLayer, 0, "group-id-input");
		setIDSafe<CCTextInputNode>(mainLayer, 1, "fade-time-input");

		auto menu = setIDSafe<CCMenu>(mainLayer, 0, "buttons");
		if (menu) {
			setIDSafe<CCMenuItemSpriteExtra>(menu, 0, "ok-button");
			setIDSafe<CCMenuItemSpriteExtra>(menu, 1, "info-button");
			setIDSafe<CCMenuItemSpriteExtra>(menu, 2, "group-id-left");
			setIDSafe<CCMenuItemSpriteExtra>(menu, 3, "group-id-right");

			setIDSafe<CCMenuItemToggler>(menu, 0, "touch-trigger-toggle");
			setIDSafe<CCMenuItemToggler>(menu, 1, "spawn-trigger-toggle");
			setIDSafe<CCMenuItemToggler>(menu, 2, "multi-trigger-toggle");
		}
	}
}

struct SetupOpacityPopupIDs : Modify<SetupOpacityPopupIDs, SetupOpacityPopup> {
	static void onModify(auto& self) {
		if (!self.setHookPriority("SetupOpacityPopup::init", GEODE_ID_PRIORITY)) {
			log::warn("Failed to set SetupOpacityPopup::init hook priority, node IDs may not work properly");
		}
	}

	bool init(EffectGameObject* p0, CCArray* p1) {
		if (!SetupOpacityPopup::init(p0, p1)) return false;

		NodeIDs::get()->provide(this);

		return true;
	}
};
