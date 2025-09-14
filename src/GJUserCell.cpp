// #include "AddIDs.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/GJUserCell.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(GJUserCell) {
	setIDs(
	    m_mainLayer,
	    0,
	    "player-icon",
	    "main-menu");
	if (auto menu = m_mainLayer->getChildByID("main-menu")) {

		setIDs(
		    menu,
		    0,
		    "player-name");

		auto actionMenu = CCMenu::create();
		actionMenu->setLayout(
		    RowLayout::create()
		        ->setGap(5.f)
		        ->setAxisAlignment(AxisAlignment::End));
		actionMenu->setID("action-menu");
		actionMenu->setContentSize({65, m_height - 2}); // 60
		actionMenu->setPosition({m_width - 42 + 0.25f, (m_height / 2) + 1.f});
		actionMenu->setZOrder(10);
		m_mainLayer->addChild(actionMenu);

		switch (m_userScore->m_friendReqStatus) {
		case 1: {
			bool canMessage = m_userScore->m_messageState != 2; // this is how rob does it
			if (canMessage) {
				setIDs(menu, 1, "message-button");
				switchToMenu(menu->getChildByID("message-button"), actionMenu);
			}

			setIDs(
			    menu,
			    canMessage ? 1 : 2,
			    "unfriend-button");

			switchToMenu(menu->getChildByID("unfriend-button"), actionMenu);
			if (m_userScore->m_newFriendRequest) {
				setIDs(m_mainLayer, 2, "new-label");
            }
            break;
		};
		case 2:
			setIDs(menu,
			       1,
			       "unblock-button");
			switchToMenu(menu->getChildByID("unblock-button"), actionMenu);
			break;
        // what happened to case 3, I don't know what rob was doing
		case 4:
			setIDs(menu,
			       1,
			       "cancel-button");
			switchToMenu(menu->getChildByID("cancel-button"), actionMenu);
			break;
		}
		actionMenu->updateLayout();
	};
}

struct GJUserCellIDs : Modify<GJUserCellIDs, GJUserCell> {
	static void onModify(auto &self) {
		if (!self.setHookPriority("GJUserCell::loadFromScore", GEODE_ID_PRIORITY)) {
			log::warn("Failed to set GJUserCell::loadFromScore hook priority, node IDs may not work properly");
		}
	}

	void loadFromScore(GJUserScore *score) {
		GJUserCell::loadFromScore(score);

		NodeIDs::get()->provide(this);
	}
};