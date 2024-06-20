#include <Geode/Bindings.hpp>
#include <Geode/modify/InfoLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(InfoLayer) {
    auto* GM = GameManager::sharedState();

    bool descNotVisible = GM->getGameVariable("0089") || m_score;

    size_t buttonOffset = 0;
    size_t labelOffset = 0;
    size_t menuOffset = 0;

    auto winSize = CCDirector::get()->getWinSize();

    getChildOfType<CCScale9Sprite>(m_mainLayer, 0)->setID("background");
    
    //this label is created at a different points in init for m_score and !m_score but the index happens to match, since they're right after each other
    getChildOfType<CCLabelBMFont>(m_mainLayer, 0)->setID("title-label");
    labelOffset++;

    getChildOfType<CCMenu>(m_mainLayer, 0)->setID("main-menu");
    menuOffset++;

    if(!m_score) {
        getChildOfType<CCMenuItemSpriteExtra>(m_buttonMenu, buttonOffset)->setID("creator-button");
        buttonOffset++;

        if(!descNotVisible) {
            getChildOfType<CCScale9Sprite>(m_mainLayer, 1)->setID("desc-background");
            getChildOfType<TextArea>(m_mainLayer, 0)->setID("description-area");
        }

        //InfoLayer::setupLevelInfo stuff
        if(m_level || m_levelList) {
            getChildOfType<CCMenu>(m_mainLayer, menuOffset)->setID("id-menu");
            menuOffset++;

            getChildOfType<CCLabelBMFont>(m_mainLayer, labelOffset)->setID("version-label");
            labelOffset++;
        }
        //end of InfoLayer::setupLevelInfo stuff

        //0077 = featured levels only; 0089 = small comments mode
        if(m_level && m_level->m_originalLevel != 0 && m_level->m_originalLevel != m_level->m_levelID && !GameManager::sharedState()->getGameVariable("0077") && !GameManager::sharedState()->getGameVariable("0089")) {
            getChildOfType<CCMenuItemSpriteExtra>(m_buttonMenu, buttonOffset)->setID("original-level-button");
            buttonOffset++;
        }

        getChildOfType<CCMenuItemSpriteExtra>(m_buttonMenu, buttonOffset)->setID("comment-button");
        buttonOffset++;

        getChildOfType<CCMenuItemSpriteExtra>(m_buttonMenu, buttonOffset)->setID("report-button");
        buttonOffset++;
        
    }

    getChildOfType<CCMenuItemSpriteExtra>(m_buttonMenu, buttonOffset)->setID("close-button");
    buttonOffset++;

    getChildOfType<LoadingCircle>(m_mainLayer, 0)->setID("loading-circle");

    
    if(auto menu = getChildOfType<CCMenu>(m_mainLayer, menuOffset)){
        menu->setID("switch-page-menu");
        menuOffset++;
        
        getChildOfType<CCMenuItemSpriteExtra>(menu, 0)->setID("prev-page-button");
        getChildOfType<CCMenuItemSpriteExtra>(menu, 1)->setID("next-page-button");
    }

    getChildOfType<CCLabelBMFont>(m_mainLayer, labelOffset)->setID("comment-count-label");
    labelOffset++;

    if(auto menu = getChildOfType<CCMenu>(m_mainLayer, menuOffset)){
        menu->setID("left-side-menu");
        menuOffset++;
        
        size_t buttonOffset = 0;
        getChildOfType<CCMenuItemSpriteExtra>(menu, buttonOffset)->setID("sort-likes-button");
        buttonOffset++;

        getChildOfType<CCMenuItemSpriteExtra>(menu, buttonOffset)->setID("sort-recent-button");
        buttonOffset++;

        if (!GM->getGameVariable("0075")) {
            if(!m_score) {
                getChildOfType<CCMenuItemSpriteExtra>(menu, buttonOffset)->setID("extend-button");
                buttonOffset++;
            }

            getChildOfType<CCMenuItemSpriteExtra>(menu, buttonOffset)->setID("small-mode-button");
            buttonOffset++;
        }

        menu->setContentSize({10, 140});
        menu->setLayout(
            ColumnLayout::create()
                ->setGap(6.f)
                ->setAxisAlignment(AxisAlignment::Center)
                ->setAxisReverse(true)
        );

        //the default autoscale options make the buttons too big
        for(auto& child : CCArrayExt<CCNode*>(menu->getChildren())) {
            child->setLayoutOptions(
                AxisLayoutOptions::create()
                    ->setScaleLimits(.1f, .7f)
            );
        }
    }

    //now it calls InfoLayer::updateCommentModeButtons but that doesn't do anything important

    getChildOfType<CCMenuItemSpriteExtra>(m_buttonMenu, buttonOffset)->setID("load-comments-button");
    buttonOffset++;

    getChildOfType<CCLabelBMFont>(m_mainLayer, labelOffset)->setID("no-comments");
    labelOffset++;

    if(!m_score) {
        getChildOfType<CCMenuItemSpriteExtra>(m_buttonMenu, buttonOffset)->setID("info-button");
        buttonOffset++;
    }

    getChildOfType<CCMenuItemSpriteExtra>(m_buttonMenu, buttonOffset)->setID("refresh-button");
    buttonOffset++;

    auto refreshMenu = detachAndCreateMenu(
        m_mainLayer, "refresh-menu",
        ColumnLayout::create()->setAxisAlignment(AxisAlignment::Start),
        m_buttonMenu->getChildByID("refresh-button")
    );
    refreshMenu->setContentSize({refreshMenu->getContentSize().width, 100.f});
    refreshMenu->setPositionY(refreshMenu->getPositionY() + 35);

    /**
     * Sanity checks
    */
    verifyIDSafe(m_loadingCircle, "loading-circle");
    verifyIDSafe(m_pageLabel, "comment-count-label");
    verifyIDSafe(m_noComments, "no-comments");
    verifyIDSafe(m_rightArrow, "next-page-button");
    verifyIDSafe(m_leftArrow, "prev-page-button");
    verifyIDSafe(m_likeBtn, "sort-likes-button");
    verifyIDSafe(m_timeBtn, "sort-recent-button");
    //verifyIDSafe(m_reportBtn, "report-button"); //not necessarily nullptr
    verifyIDSafe(m_commentsBtn, "load-comments-button");
    verifyIDSafe(m_refreshCommentsBtn, "refresh-button");

    verifyParentIDSafe(m_rightArrow, "switch-page-menu");
    verifyParentIDSafe(m_leftArrow, "switch-page-menu");
    verifyParentIDSafe(m_likeBtn, "left-side-menu");
    verifyParentIDSafe(m_timeBtn, "left-side-menu");
    //verifyParentIDSafe(m_reportBtn, "main-menu");
    verifyParentIDSafe(m_commentsBtn, "main-menu");
    verifyParentIDSafe(m_refreshCommentsBtn, "refresh-menu");
}

struct InfoLayerIDs : Modify<InfoLayerIDs, InfoLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("InfoLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set InfoLayer::init hook priority, node IDs may not work properly");
        }

        if (!self.setHookPriority("InfoLayer::setupCommentsBrowser", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set InfoLayer::setupCommentsBrowser hook priority, node IDs may not work properly");
        }
    }

    bool init(GJGameLevel* level, GJUserScore* score, GJLevelList* list) {
        if (!InfoLayer::init(level, score, list)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }

    void setupCommentsBrowser(CCArray* a3) {
        InfoLayer::setupCommentsBrowser(a3);

        // this fixes comment lists in nested infolayers
        handleTouchPriority(this);
    }
};
