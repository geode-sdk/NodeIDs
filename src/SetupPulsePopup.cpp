#include <Geode/Geode.hpp>
#include <Geode/modify/SetupPulsePopup.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(SetupPulsePopup) {
	if (auto mainLayer = setIDSafe<CCLayer>(this, 0, "main-layer")) {
		setIDs(
			mainLayer,
			0,

			"background",
			"button-menu",
			"title-label",

			"fade-in-label",
			"fade-in-background",
			"fade-in-input",
			"fade-in-slider",

			"hold-label",
			"hold-background",
			"hold-input",
			"hold-slider",

			"fade-out-label",
			"fade-out-background",
			"fade-out-input",
			"fade-out-slider",

			"target-type-label",

			"target-id-label",
			"target-id-background",
			"target-id-input",

			"pulse-mode-label",

			"touch-trigger-label",
			"spawn-trigger-label",
			"multi-trigger-label",
			"exclusive-label",

			"main-only-label",
			"detail-only-label",
			"static-hsv-label",

			"color-picker-background",
			"color-picker",
			"new-color-box",
			"old-color-box",

			"color-red-label",
			"color-red-background",
			"color-red-input",

			"color-green-label",
			"color-green-background",
			"color-green-input",

			"color-blue-label",
			"color-blue-background",
			"color-blue-input",

			"color-hex-label",
			"color-hex-background",
			"color-hex-input",

			"hsv-color-id-background",
			"hsv-color-id-input"
		);
	}

	auto buttonMenu = this->m_buttonMenu;
	buttonMenu->setID("button-menu");

	setIDs(
		buttonMenu,
		0,

		"ok-button",

		"target-type-channel",
		"target-type-group",

		"target-id-left",
		"target-id-right",

		"channel-id-plus",

		"pulse-mode-color",
		"pulse-mode-hsv",

		"touch-trigger-toggle",
		"spawn-trigger-toggle",
		"multi-trigger-toggle",
		"exclusive-toggle",

		"main-only-toggle",
		"detail-only-toggle",
		"static-hsv-toggle",

		"copy-button",
		"paste-button",

		"color-id-left",
		"color-id-right",
		"color-id-plus",

		"info-button"
	);

	setIDSafe<CCLabelBMFont>(this, 0, "hsv-color-id-label");
}

struct SetupPulsePopupIDs : Modify<SetupPulsePopupIDs, SetupPulsePopup> {
	static void onModify(auto &self) {
		if (!self.setHookPriority("SetupPulsePopup::init", GEODE_ID_PRIORITY)) {
			log::warn("Failed to set SetupPulsePopup::init hook priority, node IDs may not work properly");
		}
	}

	bool init(EffectGameObject* object, CCArray* objects) {
		if (!SetupPulsePopup::init(object, objects)) return false;

		NodeIDs::get()->provide(this);

		return true;
	}
};