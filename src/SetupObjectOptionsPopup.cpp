#include <Geode/Geode.hpp>
#include <Geode/modify/SetupObjectOptionsPopup.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(SetupObjectOptionsPopup) {
    size_t label_offset = 2; 
    if (auto mainLayer = setIDSafe(this, 0, "main-layer") ){
        setIDSafe(mainLayer, 0, "background");
        
        setIDs(
            mainLayer,
            label_offset,
            "dont-fade-label",
            "dont-enter-label",
            "no-effects-label",
            "group-parent-label",
            "area-parent-label",
            "dont-boosty-label",
            "dont-boostx-label",
            "single-ptouch-label",
            "high-touch-label",
            "notouch-label",
            "passable-label",
            "hide-label",
            "nonstickx-label",
            "extrastrickyy-label",
            "extended-collision-label",
            "center-effect-label",
            "iceblock-label",
            "gripslope-label",
            "noglow-label",
            "noparticle-label",
            "nonsticky-label",
            "scalestick-label",
            "no-audio-scale-label",
            "reverse-label"
        );

        if(auto mainMenu = setIDSafe<CCMenu>(mainLayer, 0, "main-menu")){
            setIDs(
                mainMenu,
                0,
                "ok-button",
                "info-button",
                "dont-fade-toggle",
                "dont-enter-toggle",
                "no-effects-toggle",
                "group-parent-toggle",
                "area-parent-toggle",
                "dont-boosty-toggle",
                "dont-boostx-toggle",
                "single-ptouch-toggle",
                "high-touch-toggle",
                "notouch-toggle",
                "passable-toggle",
                "hide-toggle",
                "nonstickx-toggle",
                "extrastrickyy-toggle",
                "extended-collision-toggle",
                "center-effect-toggle",
                "iceblock-toggle",
                "gripslope-toggle",
                "noglow-toggle",
                "noparticle-toggle",
                "nonsticky-toggle",
                "scalestick-toggle",
                "no-audio-scale-toggle",
                "reverse-toggle"
            );
        }
    }
    setIDSafe(this, 1, "title-label");
};

struct SetupObjectOptionsPopupIDs : Modify<SetupObjectOptionsPopupIDs, SetupObjectOptionsPopup> {
	static void onModify(auto& self) {
		if (!self.setHookPriority("SetupObjectOptionsPopup::init", GEODE_ID_PRIORITY)) {
			log::warn("Failed to set SetupObjectOptionsPopup::init hook priority, node IDs may not work properly");
		}
	}

	bool init(GameObject* p0, CCArray* p1, SetGroupIDLayer* p2) {
		if (!SetupObjectOptionsPopup::init(p0, p1, p2)) return false;

		NodeIDs::get()->provide(this);

		return true;
	}
};
