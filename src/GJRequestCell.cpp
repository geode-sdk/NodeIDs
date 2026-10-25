#include "IDCheck.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/GJRequestCell.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(GJRequestCell) {
	setIDs(
	    m_mainLayer,
	    0,
	    "main-menu",
	    "player-icon",
	    "stars-label",
	    "stars-icon",
	    "moons-label",
	    "moons-icon",
	    "demons-label",
	    "demons-icon"
	);

	if (auto menu = m_mainLayer->getChildByID("main-menu")) {
		setIDs(
		    menu,
		    0,
		    "player-name",
		    "view-button",
		    "select-toggler"
		);

		auto viewMenu = CCMenu::create();
		viewMenu->setLayout(
		    RowLayout::create()
		        ->setGap(7.25f)
		        ->setAxisAlignment(AxisAlignment::End));
		viewMenu->setID("view-menu");
		viewMenu->setContentSize({100, m_height - 2});
		viewMenu->setPosition({m_width - 61.5f, m_height / 2});
		viewMenu->setZOrder(10);
		m_mainLayer->addChild(viewMenu);

		switchToMenu(menu->getChildByID("view-button"), viewMenu);
		switchToMenu(menu->getChildByID("select-toggler"), viewMenu);
		viewMenu->updateLayout();
	}

	verifyIDSafe(m_toggler, "select-toggler");
}

struct GJRequestCellIDs : Modify<GJRequestCellIDs, GJRequestCell> {
	static void onModify(auto &self) {
		if (!self.setHookPriority("GJRequestCell::loadFromScore", GEODE_ID_PRIORITY)) {
			log::warn("Failed to set GJRequestCell::loadFromScore hook priority, node IDs may not work properly");
		}
	}

	void loadFromScore(GJUserScore *message) {
		GJRequestCell::loadFromScore(message);

		NodeIDs::get()->provide(this);
	}
};