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

    auto statsMenu = CCMenu::create();
    statsMenu->setLayout(
        RowLayout::create()
            ->setGap(11.f)
            ->setAxisAlignment(AxisAlignment::Center)
    );
    statsMenu->setID("stats-menu");
    statsMenu->setPosition({(winSize.width / 2), (winSize.height / 2) + 85.f});
    statsMenu->setContentSize({420, 90});
    statsMenu->setZOrder(10);
    m_mainLayer->addChild(statsMenu);

    auto socialsMenu = CCMenu::create();
    socialsMenu->setLayout(
        ColumnLayout::create()
            ->setGap(4.f)
            ->setAxisAlignment(AxisAlignment::End)
            ->setAxisReverse(true)
    );
    socialsMenu->setID("socials-menu");
    socialsMenu->setPosition({(winSize.width / 2) + 198.f, (winSize.height / 2) + 78.75f});
    socialsMenu->setContentSize({60, 120});
    socialsMenu->setZOrder(10);
    m_mainLayer->addChild(socialsMenu);

}

void wrapSimplePlayer(CCNode* player, CCArray* buttons, CCSize size = {42.6f, 42.6f}) {
    if(!player) {
        log::warn("Failed to wrap simple player, node is null");
        return;
    }

    auto parent = player->getParent();

    auto container = CCNode::create();
    container->setContentSize(size);
    container->setPosition(player->getPosition());
    container->setAnchorPoint({.5f, .5f});
    container->setZOrder(player->getZOrder());
    container->setID(player->getID());

    player->setPosition((container->getContentSize() / 2) - CCPoint((size.width - 42.6f) / 2, 0));
    container->addChild(player);

    parent->removeChild(player);
    parent->addChild(container);
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

        auto winSize = CCDirector::get()->getWinSize();
        size_t idx = 0;

        std::array<const char*, 7> labels = {"stars", "moons", "diamonds", "coins", "user-coins", "demons", m_score->m_creatorPoints > 0 ? "creator-points" : nullptr};
        for(auto label : labels) {
            if(!label) continue;

            auto bmFont = static_cast<CCNode*>(m_buttons->objectAtIndex(idx++));
            auto icon = static_cast<CCNode*>(m_buttons->objectAtIndex(idx++));
            auto parentNode = bmFont->getParent();
            bmFont->setID(fmt::format("{}-label", label));
            icon->setID(fmt::format("{}-icon", label));

            auto container = CCNode::create();
            container->setContentSize({bmFont->getScaledContentSize().width + icon->getScaledContentSize().width + 3.f, bmFont->getScaledContentSize().height});

            bmFont->setPosition({0, container->getContentSize().height / 2});
            icon->setPosition({(bmFont->getScaledContentSize().width) + 3.f + (icon->getScaledContentSize().width / 2), container->getContentSize().height / 2});

            container->addChild(bmFont);
            container->addChild(icon);

            parentNode->removeChild(bmFont);
            parentNode->removeChild(icon);

            if(auto statsMenu = m_mainLayer->getChildByID("stats-menu")) {
                statsMenu->addChild(container);
                statsMenu->updateLayout();
            }

            m_buttons->addObject(container);
        }

        static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("player-icon");
        static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("player-ship");
        static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("player-ball");
        static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("player-ufo");
        static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("player-wave");
        static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("player-robot");
        static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("player-spider");
        static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("player-swing");

        wrapSimplePlayer(m_mainLayer->getChildByID("player-icon"), m_buttons);
        wrapSimplePlayer(m_mainLayer->getChildByID("player-ship"), m_buttons);
        wrapSimplePlayer(m_mainLayer->getChildByID("player-ball"), m_buttons);
        wrapSimplePlayer(m_mainLayer->getChildByID("player-ufo"), m_buttons);
        wrapSimplePlayer(m_mainLayer->getChildByID("player-wave"), m_buttons, {36.6f, 42.6f});
        wrapSimplePlayer(m_mainLayer->getChildByID("player-robot"), m_buttons);
        wrapSimplePlayer(m_mainLayer->getChildByID("player-spider"), m_buttons);
        wrapSimplePlayer(m_mainLayer->getChildByID("player-swing"), m_buttons, {44.6f, 42.6f});

        auto playerMenu = detachAndCreateMenu(
            m_mainLayer, "player-menu",
            RowLayout::create()
                ->setGap(0.f)
                ->setAxisAlignment(AxisAlignment::Center),
            m_mainLayer->getChildByID("player-icon"),
            m_mainLayer->getChildByID("player-ship"),
            m_mainLayer->getChildByID("player-ball"),
            m_mainLayer->getChildByID("player-ufo"),
            m_mainLayer->getChildByID("player-wave"),
            m_mainLayer->getChildByID("player-robot"),
            m_mainLayer->getChildByID("player-spider"),
            m_mainLayer->getChildByID("player-swing")
        );
        playerMenu->setPositionX(winSize.width / 2);
        playerMenu->setContentSize({340, 35});
        playerMenu->updateLayout();
        playerMenu->setZOrder(10);


        size_t socialMediaCount = 0;
        if(!m_score->m_youtubeURL.empty()) {
            static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("youtube-button");
            socialMediaCount++;
        }
        if(!m_score->m_twitterURL.empty()) {
            static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("twitter-button");
            socialMediaCount++;
        }
        if(!m_score->m_twitchURL.empty()) {
            static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("twitch-button");
            socialMediaCount++;
        }
        if(m_score->m_commentHistoryStatus != 2 && (m_score->m_commentHistoryStatus != 1 || m_score->m_friendReqStatus == 1)
            || m_ownProfile
            || GameManager::sharedState()->m_hasRP == 2
        ) {
            static_cast<CCNode*>(m_buttons->objectAtIndex(idx++))->setID("comment-history-button");
        }
        if(socialMediaCount > 0) {
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

            auto bottomMenu = detachAndCreateMenu(
                m_mainLayer, "bottom-menu",
                RowLayout::create()
                    ->setGap(12.f)
                    ->setAxisAlignment(AxisAlignment::Center),
                m_buttonMenu->getChildByID("message-button"),
                m_buttonMenu->getChildByID("friend-button"),
                m_buttonMenu->getChildByID("block-button")
            );
            bottomMenu->setPositionX(winSize.width / 2);
            bottomMenu->setContentSize({164, 35});
            bottomMenu->updateLayout();

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

            auto bottomMenu = detachAndCreateMenu(
                m_mainLayer, "bottom-menu",
                RowLayout::create()
                    ->setGap(30.f)
                    ->setAxisAlignment(AxisAlignment::Center),
                m_buttonMenu->getChildByID("message-button"),
                m_buttonMenu->getChildByID("friend-button"),
                m_buttonMenu->getChildByID("requests-button"),
                m_buttonMenu->getChildByID("settings-button")
            );
            bottomMenu->setPositionX(winSize.width / 2);
            bottomMenu->setContentSize({340, 35});
            bottomMenu->updateLayout();
        }

        if(auto statsMenu = m_mainLayer->getChildByID("stats-menu")) {
            statsMenu->setContentSize(socialMediaCount >= 2 ? CCSize(342, 120) : CCSize(420, 120));
            statsMenu->updateLayout();
        }

        if(auto socialsMenu = m_mainLayer->getChildByID("socials-menu")) {
            if(auto youtubeButton = m_buttonMenu->getChildByID("youtube-button")) {
                socialsMenu->addChild(youtubeButton);
                m_buttonMenu->removeChild(youtubeButton, false);
            }
            if(auto twitterButton = m_buttonMenu->getChildByID("twitter-button")) {
                socialsMenu->addChild(twitterButton);
                m_buttonMenu->removeChild(twitterButton, false);
            }
            if(auto twitchButton = m_buttonMenu->getChildByID("twitch-button")) {
                socialsMenu->addChild(twitchButton);
                m_buttonMenu->removeChild(twitchButton, false);
            }
            socialsMenu->updateLayout();
        }

    }
};
