#include <Geode/Geode.hpp>
#include <Geode/modify/StartPosLayer.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(StartPosLayer) {
	setIDSafe<CCScale9Sprite>(m_mainLayer, 0, "background");
	setIDSafe<CCScale9Sprite>(m_mainLayer, 1, "y-velocity-background");
	setIDSafe<CCScale9Sprite>(m_mainLayer, 2, "spawn-group-id-background");
	setIDSafe<CCScale9Sprite>(m_mainLayer, 3, "p2-group-id-background");
	setIDSafe<CCScale9Sprite>(m_mainLayer, 4, "sp-name-background");
	setIDSafe<CCScale9Sprite>(m_mainLayer, 5, "order-background");
	setIDSafe<CCScale9Sprite>(m_mainLayer, 6, "channel-background");

	setIDSafe<CCLabelBMFont>(m_mainLayer, 0, "flip-label");
	setIDSafe<CCLabelBMFont>(m_mainLayer, 1, "mini-label");
	setIDSafe<CCLabelBMFont>(m_mainLayer, 2, "dual-label");
	setIDSafe<CCLabelBMFont>(m_mainLayer, 3, "mirror-label");
	setIDSafe<CCLabelBMFont>(m_mainLayer, 4, "free-label");
	setIDSafe<CCLabelBMFont>(m_mainLayer, 5, "rotate-label");
	setIDSafe<CCLabelBMFont>(m_mainLayer, 6, "reverse-label");
	setIDSafe<CCLabelBMFont>(m_mainLayer, 7, "reset-label");
	setIDSafe<CCLabelBMFont>(m_mainLayer, 8, "inactive-label");
	setIDSafe<CCLabelBMFont>(m_mainLayer, 9, "online-label");
	setIDSafe<CCLabelBMFont>(m_mainLayer, 10, "y-velocity-label");
	setIDSafe<CCLabelBMFont>(m_mainLayer, 11, "spawn-group-id-label");
	setIDSafe<CCLabelBMFont>(m_mainLayer, 12, "spawn-group-id-shadow-label");
	setIDSafe<CCLabelBMFont>(m_mainLayer, 13, "spawn-group-id-name-label");
	setIDSafe<CCLabelBMFont>(m_mainLayer, 14, "p2-group-id-label");
	setIDSafe<CCLabelBMFont>(m_mainLayer, 15, "p2-group-id-shadow-label");
	setIDSafe<CCLabelBMFont>(m_mainLayer, 16, "p2-group-id-name-label");
	setIDSafe<CCLabelBMFont>(m_mainLayer, 17, "sp-name-label");
	setIDSafe<CCLabelBMFont>(m_mainLayer, 18, "order-label");
	setIDSafe<CCLabelBMFont>(m_mainLayer, 19, "channel-label");

	setIDSafe<CCTextInputNode>(m_mainLayer, 0, "y-velocity-input");
	setIDSafe<CCTextInputNode>(m_mainLayer, 1, "spawn-group-id-input");
	setIDSafe<CCTextInputNode>(m_mainLayer, 2, "p2-group-id-input");
	setIDSafe<CCTextInputNode>(m_mainLayer, 3, "sp-name-input");
	setIDSafe<CCTextInputNode>(m_mainLayer, 4, "order-input");
	setIDSafe<CCTextInputNode>(m_mainLayer, 5, "channel-input");

	// There is some random CCMenu at index 0 that's just empty for some reason.
	if (auto menu = setIDSafe<CCMenu>(m_mainLayer, 1, "input-menu")) {
		setIDs(
			menu,
			0,
			"info-button",
			"ok-button",
			"cube-button",
			"ship-button",
			"ball-button",
			"ufo-button",
			"wave-button",
			"robot-button",
			"spider-button",
			"swing-button",
			"slow-speed-button",
			"normal-speed-button",
			"fast-speed-button",
			"faster-speed-button",
			"fastest-speed-button",
			"flip-toggle",
			"mini-toggle",
			"dual-toggle",
			"mirror-toggle",
			"free-toggle",
			"rotate-toggle",
			"reverse-toggle",
			"reset-toggle",
			"inactive-toggle",
			"online-toggle",
			"spawn-group-id-left",
			"spawn-group-id-right",
			"spawn-group-id-next",
			"spawn-group-id-search",
			"p2-group-id-left",
			"p2-group-id-right",
			"p2-group-id-next",
			"p2-group-id-search",
			"order-left",
			"order-right",
			"channel-left",
			"channel-right"
		);
	}
}

struct StartPosLayerIDs : Modify<StartPosLayerIDs, StartPosLayer> {
    static void onModify(auto& self) {
	    if (!self.setHookPriority("StartPosLayer::init", GEODE_ID_PRIORITY)) {
		    log::warn("Failed to set StartPosLayer::init hook priority, node IDs may not work properly");
		}
	}

	bool init(StartPosObject* object) {
	    if (!StartPosLayer::init(object)) return false;

	    NodeIDs::get()->provide(this);

	    return true;
	}
};
