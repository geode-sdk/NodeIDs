#include <Geode/Bindings.hpp>
#include <Geode/modify/ProfilePage.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(ProfilePage) {
    size_t buttonOffset = 0;
    size_t labelOffset = 0;
    size_t spriteOffset = 0;

    auto winSize = CCDirector::get()->getWinSize();

    m_buttonMenu->setID("main-menu");

    getChildOfType<CCScale9Sprite>(m_mainLayer, 0)->setID("background");

    getChildOfType<CCLabelBMFont>(m_mainLayer, labelOffset)->setID("username-label");
    labelOffset++;

    getChildOfType<CCSprite>(m_mainLayer, spriteOffset)->setID("floor-line");
    spriteOffset++;

    getChildOfType<CCMenuItemSpriteExtra>(m_buttonMenu, buttonOffset)->setID("close-button");
    buttonOffset++;

    getChildOfType<CCLabelBMFont>(m_mainLayer, labelOffset)->setID("something-went-wrong");
    labelOffset++;

    getChildOfType<CCMenuItemSpriteExtra>(m_buttonMenu, buttonOffset)->setID("prev-page-button");
    buttonOffset++;

    getChildOfType<CCMenuItemSpriteExtra>(m_buttonMenu, buttonOffset)->setID("next-page-button");
    buttonOffset++;

    if(m_accountID != GJAccountManager::sharedState()->m_accountID) {

        getChildOfType<CCMenuItemSpriteExtra>(m_buttonMenu, buttonOffset)->setID("follow-button");
        buttonOffset++;

        if(!GameLevelManager::sharedState()->isFollowingUser(m_accountID)) {
            getChildOfType<CCSprite>(m_mainLayer, spriteOffset)->setID("follow-hint");
            spriteOffset++;
        }

    }

    getChildOfType<LoadingCircle>(m_mainLayer, 0)->setID("loading-circle");

    getChildOfType<CCMenuItemSpriteExtra>(m_buttonMenu, buttonOffset)->setID("refresh-button");
    buttonOffset++;

    getChildOfType<GJCommentListLayer>(m_mainLayer, 0)->setID("icon-background");
    //getChildOfType<GJCommentListLayer>(m_mainLayer, 1)->setID("comment-list");

    auto leftMenu = CCMenu::create();
    leftMenu->setLayout(
        ColumnLayout::create()
            ->setGap(6.f)
            ->setAxisAlignment(AxisAlignment::End)
            ->setAxisReverse(true)
    );
    leftMenu->setID("left-menu");
    leftMenu->setPosition({(winSize.width / 2) - 195.f, (winSize.height / 2) + 12.f});
    leftMenu->setContentSize({60, 90});
    leftMenu->setZOrder(10);
    m_mainLayer->addChild(leftMenu);

}

struct ProfilePageIDs : Modify<ProfilePageIDs, ProfilePage> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("ProfilePage::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set ProfilePage::init hook priority, node IDs may not work properly");
        }
        if (!self.setHookPriority("ProfilePage::loadPageFromUserInfo", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set ProfilePage::loadPageFromUserInfo hook priority, node IDs may not work properly");
        }
    }

    bool init(int accountID, bool menuLayer) {
        if (!ProfilePage::init(accountID, menuLayer)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }

    void loadPageFromUserInfo(GJUserScore* score) {
        ProfilePage::loadPageFromUserInfo(score);

        NodeIDs::get()->provide(this);

        if(score->m_friendReqStatus == 2) return;

        size_t idx = 0;

        static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("stars-label");
        static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("stars-icon");
        static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("moons-label");
        static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("moons-icon");
        static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("diamonds-label");
        static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("diamonds-icon");
        static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("coins-label");
        static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("coins-icon");
        static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("user-coins-label");
        static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("user-coins-icon");
        static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("demons-label");
        static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("demons-icon");
        if(m_score->m_creatorPoints > 0) {
            static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("creator-points-label");
            static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("creator-points-icon");
        }
        static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("player-icon");
        static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("player-ship");
        static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("player-ball");
        static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("player-ufo");
        static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("player-wave");
        static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("player-robot");
        static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("player-spider");
        static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("player-swing");
        bool hasStuffTxt = false;
        if(!m_score->m_youtubeURL.empty()) {
            static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("youtube-button");
            hasStuffTxt = true;
        }
        if(!m_score->m_twitterURL.empty()) {
            static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("twitter-button");
            hasStuffTxt = true;
        }
        if(!m_score->m_twitchURL.empty()) {
            static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("twitch-button");
            hasStuffTxt = true;
        }
        if(m_score->m_commentHistoryStatus != 2 && (m_score->m_commentHistoryStatus != 1 || m_score->m_friendReqStatus == 1)
            || m_ownProfile
            || GameManager::sharedState()->m_hasRP == 2
        ) {
            static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("comment-history-button");
        }
        if(hasStuffTxt) {
            static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("my-stuff-hint");
        }
        if(m_score->m_globalRank > 0) {
            static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("global-rank-icon");
            static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("global-rank-hint");
            static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("global-rank-label");
        }
        if(m_score->m_modBadge > 0) {
            static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("mod-badge");
        }
        if(!m_ownProfile) {
            if(GJAccountManager::sharedState()->m_accountID != m_accountID) {
                if(m_score->m_messageState != 2 && (m_score->m_messageState != 1 || m_score->m_friendReqStatus == 1)) {
                    static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("message-button");
                }
                if(m_score->m_friendStatus != 1 || m_score->m_friendReqStatus) {
                    static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("friend-button");
                }
                static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("block-button");
            }
            //only allow featured levels calls setVisible so we're safe here
            static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("my-levels-button");
            static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("my-levels-hint");
            static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("my-lists-button");
            static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("my-lists-hint");
        } else {
            static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("message-button");
            static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("friend-button");
            static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("requests-button");
            static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("settings-button");
            static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("comment-button");
        }

    }
};
