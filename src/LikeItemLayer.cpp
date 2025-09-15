#include "IDCheck.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/LikeItemLayer.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(LikeItemLayer) {
	setIDs(
			m_mainLayer,
			0,
			"background",
			"main-menu",
			"vote-label"
	    );
	if (auto menu = m_mainLayer->getChildByID("main-menu")) {
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        setIDs(
            menu,
            0,
            "close-button",
            "like-button",
            "dislike-button"
        );
		auto actionMenu = CCMenu::create();
		auto layout = RowLayout::create()
			->setMainAxisScaling(geode::AxisScaling::Grow)
			->setMainAxisAlignment(geode::MainAxisAlignment::Between);
		layout->ignoreInvisibleChildren(true);
		actionMenu->setLayout(layout);
		actionMenu->setID("action-menu");
		actionMenu->setContentSize({180, 57});
		actionMenu->setPosition(winSize / 2 + ccp(1, -15));
		actionMenu->setZOrder(13);
		switchToMenu(menu->getChildByID("like-button"), actionMenu);
		switchToMenu(menu->getChildByID("dislike-button"), actionMenu);
		m_mainLayer->addChild(actionMenu);
		actionMenu->updateLayout();
		handleTouchPriority(this);
	};
	verifyIDSafe(m_buttonMenu, "main-menu");
}

struct LikeItemLayerIDs : Modify<LikeItemLayerIDs, LikeItemLayer> {
	static void onModify(auto &self) {
		if (!self.setHookPriority("LikeItemLayer::init", GEODE_ID_PRIORITY)) {
			log::warn("Failed to set LikeItemLayer::init hook priority, node IDs may not work properly");
		}
	}

	bool init(LikeItemType p0, int p1, int p2) {
		if (!LikeItemLayer::init(p0, p1, p2))
			return false;
		NodeIDs::get()->provide(this);
		return true;
	}
};
