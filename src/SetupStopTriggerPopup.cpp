#include <Geode/Geode.hpp>
#include <Geode/modify/SetupStopTriggerPopup.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(SetupStopTriggerPopup) {
	if (auto mainLayer = setIDSafe<CCLayer>(this, 0, "main-layer")) {
		setIDs(
			mainLayer,
			0,

			"background",
			"button-menu",
			"title-label",

			"touch-trigger-label",
			"spawn-trigger-label",
			"multi-trigger-label",

			"target-id-label",
			"target-id-background",
			"target-id-input",

			"use-control-id-label",

			"stop-mode-label",
			"pause-mode-label",
			"resume-mode-label"
		);

		if (auto buttonMenu = mainLayer->getChildByID("button-menu")) {
			setIDs(
				buttonMenu,
				0,

				"ok-button",
				"info-button",

				"touch-trigger-toggle",
				"spawn-trigger-toggle",
				"multi-trigger-toggle",

				"target-id-left",
				"target-id-right",

				"use-control-id-toggle",

				"stop-mode-toggle",
				"pause-mode-toggle",
				"resume-mode-toggle"
			);
		}
	}
}

struct SetupStopTriggerPopupIDs : Modify<SetupStopTriggerPopupIDs, SetupStopTriggerPopup> {
	static void onModify(auto &self) {
		if (!self.setHookPriority("SetupStopTriggerPopup::init", GEODE_ID_PRIORITY)) {
			log::warn("Failed to set SetupStopTriggerPopup::init hook priority, node IDs may not work properly");
		}
	}

	bool init(EffectGameObject* object, CCArray* objects) {
		if (!SetupStopTriggerPopup::init(object, objects)) return false;

		NodeIDs::get()->provide(this);

		return true;
	}
};