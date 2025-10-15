#include <Geode/Geode.hpp>
#include <Geode/modify/SetupObjectOptionsPopup.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(SetupObjectOptionsPopup) {
    int label_offset = 2;
    int toggle_offset = 0;
    
    
    if (auto mainLayer = setIDSafe(this, 0, "main-layer") ){
        setIDSafe(mainLayer, 0, "background");
    
        setIDs(
            mainLayer,
            &label_offset,
            "dont-fade-label",
            "dont-enter-label",
            "no-effects-label",
            "group-parent-label",
            "area-parent-label",
            "dont-boosty-label",
            "dont-boostx-label"
        );
        if(!m_gameObjects) setIDs(mainLayer, &label_offset, "single-ptouch-label");
        setIDs(
            mainLayer,
            &label_offset,
            "high-detail-label",
            "notouch-label",
            "passable-label",
            "hide-label",
            "nonstickx-label",
            "extrastrickyy-label",
            "extended-collision-label"
        );
        if(!m_gameObjects) setIDs(mainLayer, &label_offset, "center-effect-label");
        setIDs(
            mainLayer,
            &label_offset,
            "iceblock-label",
            "gripslope-label",
            "noglow-label",
            "noparticle-label",
            "nonsticky-label",
            "scalestick-label",
            "no-audio-scale-label"
        );
        if(!m_gameObjects) setIDs(mainLayer, &label_offset, "reverse-label");

        if(auto mainMenu = setIDSafe<CCMenu>(mainLayer, 0, "main-menu")){
            setIDs(
                mainMenu,
                &toggle_offset,
                "ok-button",
                "info-button",
                "dont-fade-toggle",
                "dont-enter-toggle",
                "no-effects-toggle",
                "group-parent-toggle",
                "area-parent-toggle",
                "dont-boosty-toggle",
                "dont-boostx-toggle"
            );
            if(!m_gameObjects) setIDs(mainMenu, &toggle_offset, "single-ptouch-toggle");
            setIDs(
                mainMenu,
                &toggle_offset,
                "high-detail-toggle",
                "notouch-toggle",
                "passable-toggle",
                "hide-toggle",
                "nonstickx-toggle",
                "extrastrickyy-toggle",
                "extended-collision-toggle"
            );
            if(!m_gameObjects) setIDs(mainMenu, &toggle_offset, "center-effect-toggle");
            setIDs(
                mainMenu,
                &toggle_offset,
                "iceblock-toggle",
                "gripslope-toggle",
                "noglow-toggle",
                "noparticle-toggle",
                "nonsticky-toggle",
                "scalestick-toggle",
                "no-audio-scale-toggle"
            );
            if(!m_gameObjects) setIDs(mainMenu, &toggle_offset, "reverse-toggle");
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
