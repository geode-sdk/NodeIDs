#include <Geode/Bindings.hpp>
#include <Geode/modify/LevelListLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>
#include <Geode/utils/NodeIDs.hpp>
using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(LevelListLayer) {
    size_t idx = 0;
    size_t menuIdx = 0;
	setIDs(
        this,
        idx,
        "background",
        "left-corner",
        "right-corner",
        "button-menu"
    );
    idx += 4;

    setIDs(
        this->getChildByID("button-menu"),
        menuIdx,
        "back-button"
    );
    menuIdx += 1;

    if(m_levelList->m_listType == GJLevelType::Editor) {
        setIDs(
            this,
            idx,
            "title-background",
            "title-label"
        );
        idx += 2;

        setIDs(
            this->getChildByID("button-menu"),
            menuIdx,
            "delete-button",
            "refresh-button",
            "description-button",
            "edit-mode-button",
            "difficulty-button",
            "copy-button",
            "upload-button"
        );
        menuIdx += 7;
    } else {
        setIDs(
            this,
            idx,
            "title-label",
            "difficulty-sprite",
            "featured-coin"
        );
        idx += 3;

        setIDs(
            this->getChildByID("button-menu"),
            menuIdx,
            "creator-name",
            "refresh-button",
            "info-button",
            "like-button",
            "copy-button",
            "favorite-button"
        );
        menuIdx += 6;

        if(GJAccountManager::sharedState()->m_accountID == m_levelList->m_accountID) {
            setIDs(
                this,
                idx,
                "delete-server-button"
            );
            idx += 1;
        }
    }

    setIDs(
        this->getChildByID("button-menu"),
        menuIdx,
        "small-info-button"
    );
    menuIdx += 1;

    setIDs(
        this,
        idx,
        "loading-circle",
        "no-internet-label"
    );
    idx += 2;

    //layouts
    auto winSize = CCDirector::sharedDirector()->getWinSize();

    auto mainMenu = this->getChildByID("button-menu");
    if(!mainMenu) return;

    auto rightSideMenu = CCMenu::create();
    rightSideMenu->setPosition(winSize.width - 25.f, winSize.height / 2);
    rightSideMenu->setLayout(
        ColumnLayout::create()
            ->setAxisReverse(true)
            ->setAxisAlignment(AxisAlignment::End)
            ->setGap(3.f)
    );
    rightSideMenu->setID("right-side-menu");
    rightSideMenu->setContentSize({ 50.f, winSize.height - 12.f });
    rightSideMenu->setZOrder(10);
    this->addChild(rightSideMenu);

    switchToMenu(mainMenu->getChildByID("delete-button"), rightSideMenu);
    switchToMenu(mainMenu->getChildByID("refresh-button"), rightSideMenu);
    switchToMenu(mainMenu->getChildByID("info-button"), rightSideMenu);
    switchToMenu(mainMenu->getChildByID("description-button"), rightSideMenu);
    switchToMenu(mainMenu->getChildByID("edit-mode-button"), rightSideMenu);
    switchToMenu(mainMenu->getChildByID("difficulty-button"), rightSideMenu);
    switchToMenu(mainMenu->getChildByID("like-button"), rightSideMenu);
    switchToMenu(mainMenu->getChildByID("copy-button"), rightSideMenu);
    switchToMenu(mainMenu->getChildByID("upload-button"), rightSideMenu);
    switchToMenu(mainMenu->getChildByID("favorite-button"), rightSideMenu);
    if(auto heart = rightSideMenu->getChildByID("favorite-button")) {
        heart->setContentSize(heart->getContentSize() + CCSize(8.f, 8.f));
        if(auto item = typeinfo_cast<CCMenuItemSpriteExtra*>(heart)->getNormalImage()) {
            item->setPosition(heart->getContentSize() / 2);
        }
        heart->setZOrder(2); //always at the bottom
    }
    rightSideMenu->updateLayout();
}

struct LevelListLayerIDs : Modify<LevelListLayerIDs, LevelListLayer> {
	static void onModify(auto& self) {
		if (!self.setHookPriority("LevelListLayer::init", GEODE_ID_PRIORITY)) {
			log::warn("Failed to set LevelListLayer::init hook priority, node IDs may not work properly");
		}
	}
	bool init(GJLevelList* p0) {
		if (!LevelListLayer::init(p0)) return false;
		NodeIDs::get()->provide(this);

        createLeftMenu();
		return true;
	}
    void updateStatsArt() {
        LevelListLayer::updateStatsArt();

        size_t idx = 0;
        static_cast<CCNode*>(m_objects->objectAtIndex(idx++))->setID("progress-bar");
        static_cast<CCNode*>(m_objects->objectAtIndex(idx++))->setID("progress-bar-label");

        bool isRated = m_levelList->m_diamonds > 0 && m_levelList->m_levelsToClaim > 0;

        if(m_levelList->m_listType != GJLevelType::Editor) {
            static_cast<CCNode*>(m_objects->objectAtIndex(idx++))->setID("downloads-icon");
            static_cast<CCNode*>(m_objects->objectAtIndex(idx++))->setID("downloads-label");
            static_cast<CCNode*>(m_objects->objectAtIndex(idx++))->setID("likes-icon");
            static_cast<CCNode*>(m_objects->objectAtIndex(idx++))->setID("likes-label");

            if(isRated) {
                if(GameStatsManager::sharedState()->hasClaimedListReward(m_levelList)) {
                    static_cast<CCNode*>(m_objects->objectAtIndex(idx++))->setID("diamonds-icon");
                    static_cast<CCNode*>(m_objects->objectAtIndex(idx++))->setID("diamonds-count");
                } else {
                    static_cast<CCNode*>(m_objects->objectAtIndex(idx++))->setID("small-diamonds-icon");
                    static_cast<CCNode*>(m_objects->objectAtIndex(idx++))->setID("completed-icon");
                    static_cast<CCNode*>(m_objects->objectAtIndex(idx++))->setID("completed-label");
                    static_cast<CCNode*>(m_objects->objectAtIndex(idx++))->setID("claim-button");
                }
            }
        }

        //layouts
        createLeftMenu();

        auto leftSideMenu = this->getChildByID("left-side-menu");
        if(!leftSideMenu) return;

        std::array<char const*, 8> nodes = {
            "downloads-icon",
            "downloads-label",
            "likes-icon",
            "likes-label",
            "completed-icon",
            "completed-label",
            "diamonds-icon",
            "diamonds-count"
        };

        for(auto node : nodes) {
            moveNodeWithOptions(this->getChildByID(node), leftSideMenu, -4);    
        }
        moveNodeWithOptions(m_buttonMenu->getChildByID("claim-button"), leftSideMenu, -2);

        if(!isRated) {
            if(auto like = leftSideMenu->getChildByID("likes-icon")) like->setContentSize(like->getContentSize() + CCSize(0.f, 13.f));
        } else {
            if(auto like = leftSideMenu->getChildByID("likes-icon")) like->setContentSize(like->getContentSize() + CCSize(0.f, 4.f));
            if(auto like = leftSideMenu->getChildByID("completed-icon")) like->setContentSize(like->getContentSize() + CCSize(0.f, 4.f));
            if(auto like = leftSideMenu->getChildByID("claim-button")) like->setContentSize(like->getContentSize() + CCSize(0.f, -4.f));
        }

        leftSideMenu->updateLayout();
        
    }

    //custom
    void createLeftMenu() {
        if(this->getChildByID("left-side-menu")) return;
        auto winSize = CCDirector::sharedDirector()->getWinSize();

        auto leftSideMenu = CCMenu::create();
        leftSideMenu->setPosition(26.f, winSize.height / 2);
        leftSideMenu->setLayout(
            ColumnLayout::create()
                ->setAxisReverse(true)
                ->setAxisAlignment(AxisAlignment::End)
        );
        leftSideMenu->setID("left-side-menu");
        leftSideMenu->setContentSize({ 50.f, 195.f });
        leftSideMenu->setZOrder(10);
        this->addChild(leftSideMenu);
    }

    void moveNodeWithOptions(CCNode* node, CCNode* menu, int zOrder = 0) {
        if(!node || !menu) return;
        switchToMenu(node, menu);
        node->setZOrder(-4);
        node->setLayoutOptions(
            AxisLayoutOptions::create()
                ->setRelativeScale(node->getScale())
        );

    }
};