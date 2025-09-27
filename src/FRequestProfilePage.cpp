#include "IDCheck.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/FRequestProfilePage.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(FRequestProfilePage) {
	size_t offset = 6;
	setIDs(
			m_mainLayer,
			0,
			"background",
            m_sent ? "sent-requests-label" : "friend-requests-label",
			"user-tap-label",
            "page-label",
            "main-menu",
            "loading-circle"
	    );
	if (!m_sent) {
		setIDs(m_mainLayer,
		       offset,
		       "all-label");
		    offset++;
	};
	setIDs(m_mainLayer,
	       offset,
	       "something-went-wrong-label");

	    if (auto menu = m_mainLayer->getChildByID("main-menu")) {
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		offset = 0;
		setIDs(
		    menu,
		    offset,
		    "back-button");
		offset++;
		if (!m_sent) {
			setIDs(
			    menu,
			    offset,
			    "sent-request-button",
			    "delete-button",
			    "all-toggle");
			offset += 3;
		}
		setIDs(
		    menu,
		    offset,
		    "previous-page-button",
		    "next-previous-button",
		    "refresh-button");
		
		auto bottomRightMenu = detachAndCreateMenu(
			m_mainLayer, "bottom-right-menu",
			ColumnLayout::create()->setAxisAlignment(AxisAlignment::Start),
			m_buttonMenu->getChildByID("refresh-button")
		);
		bottomRightMenu->setContentSize({bottomRightMenu->getContentSize().width, 100.f});
		bottomRightMenu->setPositionY(bottomRightMenu->getPositionY() + 25);
		
		auto topLeftMenu = detachAndCreateMenu(
			m_mainLayer, "top-left-menu",
			ColumnLayout::create()->setAxisAlignment(AxisAlignment::End),
			m_buttonMenu->getChildByID("back-button")
		);
		topLeftMenu->setContentSize({topLeftMenu->getContentSize().width, 100.f});
		topLeftMenu->setPositionY(topLeftMenu->getPositionY() - 25);

		auto topRightMenu = CCMenu::create();
        topRightMenu->setID("top-right-menu");
        topRightMenu->setLayout(ColumnLayout::create()->setAxisAlignment(AxisAlignment::End));
		topRightMenu->setPosition({winSize.width  * 0.5f + 210.0f, winSize.height * 0.5f + 105.0f}); 
		topRightMenu->setContentSize({topRightMenu->getContentSize().width, 100.f});
        m_mainLayer->addChild(topRightMenu);
		switchToMenu(menu->getChildByID("sent-request-button"), topRightMenu);

		auto bottomLeftMenu = CCMenu::create();
        bottomLeftMenu->setID("bottom-left-menu");
        bottomLeftMenu->setLayout(ColumnLayout::create()->setAxisAlignment(AxisAlignment::Start));
		bottomLeftMenu->setPosition({winSize.width  * 0.5f - 200, winSize.height * 0.5f - 86}); 
		bottomLeftMenu->setContentSize({bottomLeftMenu->getContentSize().width, 100.f});
		switchToMenu(menu->getChildByID("delete-button"), bottomLeftMenu);
        m_mainLayer->addChild(bottomLeftMenu);


		topRightMenu->updateLayout();
		topLeftMenu->updateLayout();
		bottomRightMenu->updateLayout();
		bottomLeftMenu->updateLayout();

		handleTouchPriority(this);
	};
	verifyIDSafe(m_buttonMenu, "main-menu");
}

struct FRequestProfilePageIDs : Modify<FRequestProfilePageIDs, FRequestProfilePage> {
	static void onModify(auto &self) {
		if (!self.setHookPriority("FRequestProfilePage::init", GEODE_ID_PRIORITY)) {
			log::warn("Failed to set FRequestProfilePage::init hook priority, node IDs may not work properly");
		}
	}

	bool init(bool sentrequest) {
		if (!FRequestProfilePage::init(sentrequest))
			return false;
		NodeIDs::get()->provide(this);
		return true;
	}
};
