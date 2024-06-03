#include <Geode/Geode.hpp>
#include <Geode/binding/LevelInfoLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(LevelInfoLayer) {
    auto winSize = CCDirector::get()->getWinSize();

    setIDSafe<CCSprite>(this, 0, "background");

    size_t iconOffset = 0;

    setIDSafe<CCSprite>(this, 1, "bottom-left-art");
    setIDSafe<CCSprite>(this, 2, "bottom-right-art");

    if (m_level->m_objectCount > 40000 || m_level->m_originalLevel != 0) {
        if(m_level->m_originalLevel != 0) {
            setIDSafe<CCSprite>(this, 3, "copy-indicator");
            iconOffset++;
        }

        if(m_level->m_objectCount > 40000) {
            setIDSafe<CCSprite>(this, 3 + iconOffset, "high-object-indicator");
            iconOffset++;
        }
    //} else if(!GameManager::sharedState()->getGameVariable("0047") && !m_challenge && GameLevelManager::sharedState()->accountIDForUserID(m_level->m_userID) > 0) {
    } else if(auto viewSprite = getChildBySpriteFrameName(this, "GJ_viewProfileTxt_001.png")) {
        if(getChildOfType<CCSprite>(this, 3) != viewSprite) log::warn("View Profile sprite not in expected place! Node IDs may be incorrect!");
        viewSprite->setID("view-profile");
        iconOffset++;
    }

    setIDSafe<CCSprite>(this, 3 + iconOffset, "length-icon");
    setIDSafe<CCSprite>(this, 4 + iconOffset, "downloads-icon");
    setIDSafe<CCSprite>(this, 5 + iconOffset, "orbs-icon");
    setIDSafe<CCSprite>(this, 6 + iconOffset, "likes-icon");

    size_t labelOffset = 0;

    setIDSafe<CCLabelBMFont>(this, labelOffset++, "title-label");

    if(m_level->m_dailyID > 0) {
        setIDSafe<CCLabelBMFont>(this, labelOffset++, "daily-label");
    }

    setIDSafe<CCLabelBMFont>(this, labelOffset++, "downloads-label");
    setIDSafe<CCLabelBMFont>(this, labelOffset++, "length-label");
    setIDSafe<CCLabelBMFont>(this, labelOffset++, "exact-length-label");
    setIDSafe<CCLabelBMFont>(this, labelOffset++, "likes-label");
    setIDSafe<CCLabelBMFont>(this, labelOffset++, "orbs-label");
    setIDSafe<CCLabelBMFont>(this, labelOffset++, "stars-label");

    setIDSafe<CCSprite>(this, 8 + iconOffset, "stars-icon");

    if (m_level->m_dailyID > 0 || m_level->m_gauntletLevel) {
        setIDSafe<CCLabelBMFont>(this, labelOffset++, "diamond-label");
        setIDSafe<CCSprite>(this, 9 + iconOffset, "diamond-icon");
    }

    /*if(m_ldmLabel) m_ldmLabel->setID("ldm-label");
    if(m_ldmToggler) m_ldmToggler->setID("ldm-toggler");*/
    if(m_difficultySprite) m_difficultySprite->setID("difficulty-sprite");
    if(m_songWidget) m_songWidget->setID("custom-songs-widget");
    if(m_circle) m_circle->setID("loading-circle");

    size_t coinIdx = 1;
    for(auto& coin : CCArrayExt<CCSprite*>(m_coins)) {
        coin->setID(fmt::format("coin-icon-{}", coinIdx++));
    }

    if (auto menu = getChildOfType<CCMenu>(this, 0)) {
        menu->setID("play-menu");
        setIDSafe(menu, 0, "play-button");
    }

    if (auto menu = getChildOfType<CCMenu>(this, 2)) {
        menu->setID("back-menu");
        auto backBtn = setIDSafe(menu, 0, "back-button");
        menu->setPositionX(
            menu->getPositionX() + 100.f / 2 - 
                getSizeSafe(backBtn).width / 2
        );
        menu->setContentSize({ 100.f, 50.f });
        menu->setLayout(
            RowLayout::create()
                ->setAxisAlignment(AxisAlignment::Start)
        );
    }

    if (auto menu = getChildOfType<CCMenu>(this, 1)) {
        menu->setID("right-side-menu");

        if (auto name = setIDSafe(menu, 0, "creator-name")) {
            auto menu = detachAndCreateMenu(
                this,
                "creator-info-menu",
                ColumnLayout::create()
                    ->setAxisReverse(true)
                    ->setAxisAlignment(AxisAlignment::End),
                name
            );
            menu->setPositionY(
                menu->getPositionY() - 40.f / 2 + 
                    name->getScaledContentSize().height / 2
            );
            menu->setContentSize({ 60.f, 40.f });
            menu->updateLayout();
        }

        auto leftSideMenu = CCMenu::create();
        leftSideMenu->setPosition(30.f, winSize.height / 2);
        leftSideMenu->setLayout(ColumnLayout::create());
        leftSideMenu->setID("left-side-menu");
        leftSideMenu->setContentSize({ 50.f, 145.f });
        this->addChild(leftSideMenu);

        menu->setPosition(winSize.width - 30.f, winSize.height / 2);

        for (auto child : CCArrayExt<CCNode*>(menu->getChildren())) {
            if (child->getPositionX() < 0.f) {
                child->retain();
                child->removeFromParent();
                leftSideMenu->addChild(child);
                child->release();
            }
            child->setPositionX(0.f);
        }

        setIDSafe(menu, 0, "delete-button");
        setIDSafe(menu, 1, "refresh-button");
        setIDSafe(menu, 2, "info-button");
        setIDSafe(menu, 3, "leaderboards-button");
        setIDSafe(menu, 4, "like-button");
        setIDSafe(menu, 5, "rate-button");

        menu->setPosition(
            menu->getPositionX() + static_cast<CCNode*>(
                menu->getChildren()->objectAtIndex(0)
            )->getPositionX(),
            winSize.height / 2
        );
        menu->setContentSize({ 60.f, winSize.height - 15.f });
        menu->setLayout(
            ColumnLayout::create()
                ->setGap(3.f)
                ->setAxisAlignment(AxisAlignment::End)
                ->setAxisReverse(true)
        );

        if(auto modRateBtn = getChildBySpriteFrameName(leftSideMenu, "GJ_starBtnMod_001.png")) {
            modRateBtn->setID("mod-rate-button");
        }

        if(auto deleteServerBtn = getChildBySpriteFrameName(leftSideMenu, "GJ_deleteServerBtn_001.png")) {
            deleteServerBtn->setID("delete-button");
        }

        if(auto deleteServerBtn = getChildBySpriteFrameName(menu, "GJ_deleteServerBtn_001.png")) {
            deleteServerBtn->setID("delete-server-button");
        }

        if(auto copyBtn = getChildBySpriteFrameName(leftSideMenu, "GJ_duplicateBtn_001.png")) {
            copyBtn->setID("copy-button");
        }

        if(auto copyBtn = getChildBySpriteFrameName(leftSideMenu, "GJ_duplicateLockedBtn_001.png")) {
            copyBtn->setID("copy-button");
        }

        if(auto btn = leftSideMenu->getChildByID("mod-rate-button")) btn->setZOrder(-1);
        if(auto btn = leftSideMenu->getChildByID("delete-button")) btn->setZOrder(-2);
        if(auto btn = leftSideMenu->getChildByID("copy-button")) btn->setZOrder(-3);

        menu->updateLayout();
        leftSideMenu->updateLayout();
    }

    if (auto menu = getChildOfType<CCMenu>(this, 3)) {
        menu->setID("other-menu");

        setIDSafe(menu, 0, "info-button");
        setIDSafe(menu, 1, "favorite-button");
        setIDSafe(menu, 2, "move-up-button");
        setIDSafe(menu, 3, "move-down-button");
        setIDSafe(menu, 4, "folder-button");
        setIDSafe(menu, 5, "list-button");
    }

    if (auto menu = getChildOfType<CCMenu>(this, 4)) {
        menu->setID("garage-menu");

        setIDSafe(menu, 0, "garage-button");
    }

    if (auto menu = getChildOfType<CCMenu>(this, 5)) {
        menu->setID("settings-menu");

        setIDSafe(menu, 0, "settings-button");
    }

    /**
     * Verify node IDs
     */
    if(m_orbsLabel != getChildByID("orbs-label")) {
        log::warn("Node IDs are incorrect: m_orbsLabel != getChildByID(\"orbs-label\")");
    }

    if(m_orbsIcon != getChildByID("orbs-icon")) {
        log::warn("Node IDs are incorrect: m_orbsIcon != getChildByID(\"orbs-icon\")");
    }

    if(m_lengthLabel != getChildByID("length-label")) {
        log::warn("Node IDs are incorrect: m_lengthLabel != getChildByID(\"length-label\")");
    }

    if(m_downloadsLabel != getChildByID("downloads-label")) {
        log::warn("Node IDs are incorrect: m_downloadsLabel != getChildByID(\"downloads-label\")");
    }

    if(m_likesLabel != getChildByID("likes-label")) {
        log::warn("Node IDs are incorrect: m_likesLabel != getChildByID(\"likes-label\")");
    }

    if(m_starsIcon != getChildByID("stars-icon")) {
        log::warn("Node IDs are incorrect: m_starsIcon != getChildByID(\"stars-icon\")");
    }

    if(m_starsLabel != getChildByID("stars-label")) {
        log::warn("Node IDs are incorrect: m_starsLabel != getChildByID(\"stars-label\")");
    }

}

struct LevelInfoLayerIDs : Modify<LevelInfoLayerIDs, LevelInfoLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("LevelInfoLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set LevelInfoLayer::init hook priority, node IDs may not work properly");
        }
    }

    bool init(GJGameLevel* level, bool challenge) {
        if (!LevelInfoLayer::init(level, challenge)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }

    void updateLabelValues() {
        LevelInfoLayer::updateLabelValues();

        size_t coinIdx = 1;
        for(auto& coin : CCArrayExt<CCSprite*>(m_coins)) {
            coin->setID(fmt::format("coin-icon-{}", coinIdx++));
        }
    }

    void setupPlatformerStats() {
        LevelInfoLayer::setupPlatformerStats();

        size_t labelOffset = 1;
        if(m_level->m_bestPoints) {
            static_cast<CCNode*>(this->getChildren()->objectAtIndex(this->getChildrenCount() - labelOffset))->setID("points-label");
            labelOffset++;
        }

        static_cast<CCNode*>(this->getChildren()->objectAtIndex(this->getChildrenCount() - labelOffset))->setID("best-time-label");
        labelOffset++;
    }

    void setupProgressBars() {
        LevelInfoLayer::setupProgressBars();

        static_cast<CCNode*>(this->getChildren()->objectAtIndex(this->getChildrenCount() - 1))->setID("practice-mode-label");
        static_cast<CCNode*>(this->getChildren()->objectAtIndex(this->getChildrenCount() - 2))->setID("normal-mode-label");
        static_cast<CCNode*>(this->getChildren()->objectAtIndex(this->getChildrenCount() - 3))->setID("practice-mode-percentage");
        static_cast<CCNode*>(this->getChildren()->objectAtIndex(this->getChildrenCount() - 4))->setID("normal-mode-percentage");
        static_cast<CCNode*>(this->getChildren()->objectAtIndex(this->getChildrenCount() - 5))->setID("practice-mode-bar");
        static_cast<CCNode*>(this->getChildren()->objectAtIndex(this->getChildrenCount() - 6))->setID("normal-mode-bar");
    }
};
