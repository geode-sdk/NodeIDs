#include <Geode/Geode.hpp>
#include <Geode/modify/SetupArtSwitchPopup.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(SetupArtSwitchPopup) {
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
			"art-type-label"
		);
	}

	auto buttonMenu = this->m_buttonMenu;
	buttonMenu->setID("button-menu");

	setIDs(
		buttonMenu,
		0,

		"ok-button",
		"info-button",
		"touch-trigger-toggle",
		"spawn-trigger-toggle",
		"multi-trigger-toggle",
		"art-picker-button"
	);
}

struct SetupArtSwitchPopupIDs : Modify<SetupArtSwitchPopupIDs, SetupArtSwitchPopup> {
	static void onModify(auto &self) {
		if (!self.setHookPriority("SetupArtSwitchPopup::init", GEODE_ID_PRIORITY)) {
			log::warn("Failed to set SetupArtSwitchPopup::init hook priority, node IDs may not work properly");
		}
	}

	bool init(ArtTriggerGameObject* object, CCArray* objects, int id) {
		if (!SetupArtSwitchPopup::init(object, objects, id)) return false;

		NodeIDs::get()->provide(this);

		return true;
	}
};