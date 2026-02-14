#include <Geode/Geode.hpp>
#include <Geode/modify/SetupObjectOptionsPopup.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(SetupObjectOptionsPopup) {
    int labelOffset = 2;
    int menuOffset = 0;
    
    bool show_reverse = m_gameObject && m_gameObject->m_classType == GameObjectClassType::Effect && m_gameObject->canReverse();
    
    setIDSafe<CCLabelBMFont>(this, 0, "title-label");
    if (auto mainLayer = setIDSafe<CCLayer>(this, 0, "main-layer")) {
        setIDSafe<CCScale9Sprite>(mainLayer, 0, "background");
        setIDs(
            mainLayer,
            &labelOffset,
            "dont-fade-label",
            "dont-enter-label",
            "no-effects-label",
            "group-parent-label",
            "area-parent-label",
            "dont-boosty-label",
            "dont-boostx-label"
        );
        if(m_effectObject) setIDs(mainLayer, &labelOffset, "single-ptouch-label");

        setIDs(
            mainLayer,
            &labelOffset,
            "high-detail-label",
            "notouch-label",
            "passable-label",
            "hide-label",
            "nonstickx-label",
            "extrastrickyy-label",
            "extended-collision-label"
        );
        if(m_effectObject) setIDs(mainLayer, &labelOffset, "center-effect-label");

        setIDs(
            mainLayer,
            &labelOffset,
            "iceblock-label",
            "gripslope-label",
            "noglow-label",
            "noparticle-label",
            "nonsticky-label",
            "scalestick-label",
            "no-audio-scale-label"
        );
        if(show_reverse) setIDs(mainLayer, &labelOffset, "reverse-label");

        if(auto mainMenu = setIDSafe<CCMenu>(mainLayer, 0, "main-menu")){
            setIDs(
                mainMenu,
                &menuOffset,
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
            if(m_effectObject) setIDs(mainMenu, &menuOffset, "single-ptouch-toggle");

            setIDs(
                mainMenu,
                &menuOffset,
                "high-detail-toggle",
                "notouch-toggle",
                "passable-toggle",
                "hide-toggle",
                "nonstickx-toggle",
                "extrastrickyy-toggle",
                "extended-collision-toggle"
            );
            if(m_effectObject) setIDs(mainMenu, &menuOffset, "center-effect-toggle");

            setIDs(
                mainMenu,
                &menuOffset,
                "iceblock-toggle",
                "gripslope-toggle",
                "noglow-toggle",
                "noparticle-toggle",
                "nonsticky-toggle",
                "scalestick-toggle",
                "no-audio-scale-toggle"
            );
            if(show_reverse) setIDs(mainMenu, &menuOffset, "reverse-toggle");
        }
    }
    
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
