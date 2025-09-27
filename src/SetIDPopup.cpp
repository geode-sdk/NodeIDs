#include <Geode/Geode.hpp>
#include <Geode/modify/SetIDPopup.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

struct SetIDPopupIDs : Modify<SetIDPopupIDs, SetIDPopup> {
	struct Fields {
		bool m_hasbin = false;
	};

	static void onModify(auto &self) {
		if (!self.setHookPriority("SetIDPopup::init", GEODE_ID_PRIORITY)) {
			log::warn("Failed to set SetIDPopup::init hook priority, node IDs may not work properly");
		}
	}

	bool init(int current, int begin, int end, gd::string title, gd::string button, bool p1, int p2, float p3, bool p4, bool p5) {
		if (!SetIDPopup::init(current, begin, end, title, button, p1, p2, p3, p4, p5))
			return false;
		m_fields->m_hasbin = p1;

		NodeIDs::get()->provide(this);
		return true;
	}
};

$register_ids(SetIDPopup) {
	auto self = reinterpret_cast<SetIDPopupIDs *>(this);
	setIDs(this, 0, "main-layer", "title-label");
	    setIDs(
	        m_mainLayer,
	        0,
	        "background",
	        "main-menu",
	        "textbox-background",
	        "text-box");
	if (auto menu = m_mainLayer->getChildByID("main-menu")) {
		size_t index = 1;
		setIDs(
		    menu,
		    0,
		    "enter-button");
		if (self->m_fields->m_hasbin) {
			setIDs(
			    menu,
			    index,
			    "bin-button");
			index++;
		}
		setIDs(
		    menu,
		    index,
		    "left-arrow-button",
		    "right-arrow-button",
		    "close-button");
	}
}
