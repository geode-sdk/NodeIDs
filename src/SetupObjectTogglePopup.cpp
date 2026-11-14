#include <Geode/Geode.hpp>
#include <Geode/modify/SetupObjectTogglePopup.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(SetupObjectTogglePopup) {
	if (auto mainLayer = setIDSafe<CCLayer>(this, 0, "main-layer")) {
		setIDs(
			mainLayer,
			0,

			"background",
			"button-menu",
			"title-label",
			"group-id-label",
			"group-id-background",
			"group-id-input",
			"touch-trigger-label",
			"spawn-trigger-label",
			"multi-trigger-label",
			"activate-group-label"
		);
	}

	auto buttonMenu = this->m_buttonMenu;
	buttonMenu->setID("button-menu");

	setIDs(
		buttonMenu,
		0,

		"info-button",
		"ok-button",
		"group-id-left",
		"group-id-right",
		"touch-trigger-toggle",
		"spawn-trigger-toggle",
		"multi-trigger-toggle",
		"activate-group-toggle"
	);
}

struct SetupObjectTogglePopupIDs : Modify<SetupObjectTogglePopupIDs, SetupObjectTogglePopup> {
	static void onModify(auto &self) {
		if (!self.setHookPriority("SetupObjectTogglePopup::init", GEODE_ID_PRIORITY)) {
			log::warn("Failed to set SetupObjectTogglePopup::init hook priority, node IDs may not work properly");
		}
	}

	bool init(EffectGameObject* object, CCArray* objects, bool platformer) {
		if (!SetupObjectTogglePopup::init(object, objects, platformer)) return false;

		NodeIDs::get()->provide(this);

		return true;
	}
};