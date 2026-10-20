#include <Geode/Bindings.hpp>
#include <Geode/modify/ProfilePage.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

// parental controls stuff
static bool isProfileDisabled() {
    return GameManager::get()->getGameVariable("0219");
}

static bool isSocialDisabled() {
    auto gm = GameManager::get();
    return gm->getGameVariable("0218") || gm->getGameVariable("0219");
}

$register_ids(ProfilePage) {
    size_t buttonOffset = 0;
    size_t labelOffset = 0;
    size_t spriteOffset = 0;

    auto winSize = CCDirector::get()->getWinSize();

    m_buttonMenu->setID("main-menu");

    m_mainLayer->getChildByType<CCScale9Sprite>(0)->setID("background");

    if (isProfileDisabled()) {
        m_mainLayer->getChildByType<CCLabelBMFont>(0)->setID("parental-controls-label");
        m_buttonMenu->getChildByType<CCMenuItemSpriteExtra>(0)->setID("close-button");
        return;
    }

    m_mainLayer->getChildByType<CCLabelBMFont>(labelOffset)->setID("username-label");
    labelOffset++;

    m_mainLayer->getChildByType<CCSprite>(spriteOffset)->setID("floor-line");
    spriteOffset++;

    m_mainLayer->getChildByType<CCScale9Sprite>(1)->setID("icon-background");
    m_mainLayer->getChildByType<CCScale9Sprite>(2)->setID("icon-background-border");

    m_buttonMenu->getChildByType<CCMenuItemSpriteExtra>(buttonOffset)->setID("close-button");
    buttonOffset++;

    m_mainLayer->getChildByType<CCLabelBMFont>(labelOffset)->setID("something-went-wrong");
    labelOffset++;

    m_buttonMenu->getChildByType<CCMenuItemSpriteExtra>(buttonOffset)->setID("prev-page-button");
    buttonOffset++;

    m_buttonMenu->getChildByType<CCMenuItemSpriteExtra>(buttonOffset)->setID("next-page-button");
    buttonOffset++;

    if(m_accountID != GJAccountManager::sharedState()->m_accountID && !isSocialDisabled()) {
        m_buttonMenu->getChildByType<CCMenuItemSpriteExtra>(buttonOffset)->setID("follow-button");
        buttonOffset++;
    }

    if (auto followHint = getChildBySpriteFrameName(m_mainLayer, "GJ_followTxt_001.png")) {
        followHint->setID("follow-hint");
    }

    m_mainLayer->getChildByType<LoadingCircle>(0)->setID("loading-circle");

    m_buttonMenu->getChildByType<CCMenuItemSpriteExtra>(buttonOffset)->setID("refresh-button");
    buttonOffset++;

    auto rightMenu = CCMenu::create();
    rightMenu->setLayout(
        ColumnLayout::create()
            ->setGap(3.f)
            ->setAxisAlignment(AxisAlignment::Start)
            ->setAxisReverse(false)
    );
    rightMenu->setID("right-menu");
    rightMenu->setPosition({(winSize.width / 2) + 197.5f, (winSize.height / 2) + 15.f});
    rightMenu->setContentSize({60, 84});
    rightMenu->setZOrder(10);
    m_mainLayer->addChild(rightMenu);

    auto statsMenu = CCMenu::create();
    statsMenu->setLayout(
        RowLayout::create()
            ->setGap(6.f)
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
            ->setGap(3.5f)
            ->setAxisAlignment(AxisAlignment::End)
            ->setAxisReverse(true)
    );
    socialsMenu->setID("socials-menu");
    socialsMenu->setPosition({(winSize.width / 2) + 197.5f, (winSize.height / 2) + 57.75f});
    socialsMenu->setContentSize({60, 160});
    socialsMenu->setZOrder(10);
    m_mainLayer->addChild(socialsMenu);

    auto usernameMenu = CCMenu::create();
    usernameMenu->setLayout(
        RowLayout::create()
            ->setGap(3.f)
            ->setAxisAlignment(AxisAlignment::Center)
            ->setCrossAxisOverflow(false)
            ->setAutoScale(false)
    );
    usernameMenu->setID("username-menu");
    usernameMenu->setPosition({(winSize.width / 2), (winSize.height / 2) + 125.f});
    usernameMenu->setContentSize({286, 40});
    usernameMenu->setZOrder(20);
    m_mainLayer->addChild(usernameMenu);

    switchToMenu(m_usernameLabel, usernameMenu);
    m_usernameLabel->setZOrder(20);
    usernameMenu->updateLayout();

}

std::array<std::pair<const char*, const char*>, 7> STAT_ICONS = {{
    {"GJ_starsIcon_001.png", "stars"},
    {"GJ_moonsIcon_001.png", "moons"},
    {"GJ_coinsIcon_001.png", "coins"},
    {"GJ_coinsIcon2_001.png", "user-coins"},
    {"GJ_demonIcon_001.png", "demons"},
    {"GJ_followIcon_001.png", "followers"},
    {"GJ_hammerIcon_001.png", "creator-points"},
}};

std::array<const char*, 9> PLAYER_IDS = {
    "player-icon", "player-ship", "player-ball", "player-ufo", "player-wave",
    "player-robot", "player-spider", "player-swing", "player-jetpack"
};

std::array<std::pair<const char*, const char*>, 28> FRAME_IDS = {{
    {"gj_ytIcon_001.png", "youtube-button"},
    {"gj_twIcon_001.png", "twitter-button"},
    {"gj_twitchIcon_001.png", "twitch-button"},
    {"gj_instaIcon_001.png", "instagram-button"},
    {"gj_tiktokIcon_001.png", "tiktok-button"},
    {"accountBtn_social_001.png", "socials-button"},
    {"GJ_youtubeTxt_001.png", "my-stuff-hint"},
    {"GJ_twitterTxt_001.png", "my-stuff-hint"},
    {"GJ_twitchTxt_001.png", "my-stuff-hint"},
    {"GJ_stuffTxt_001.png", "my-stuff-hint"},
    {"btn_chatHistory_001.png", "comment-history-button"},
    {"gj_globalRankTxt_001.png", "global-rank-hint"},
    {"GJ_infoIcon_001.png", "info-button"},
    {"whiteSquare60_001.png", "copy-username-button"},
    {"accountBtn_unblock_001.png", "unblock-button"},
    {"accountBtn_messages_001.png", "message-button"},
    {"accountBtn_friends_001.png", "friend-button"},
    {"accountBtn_removeFriend_001.png", "friend-button"},
    {"accountBtn_pendingRequest_001.png", "friend-button"},
    {"accountBtn_pending_001.png", "friend-button"},
    {"accountBtn_blocked_001.png", "block-button"},
    {"accountBtn_notifications_001.png", "notifications-button"},
    {"accountBtn_settings_001.png", "settings-button"},
    {"GJ_chatBtn_001.png", "comment-button"},
    {"accountBtn_myLevels_001.png", "my-levels-button"},
    {"GJ_myLevelsTxt_001.png", "my-levels-hint"},
    {"accountBtn_myLists_001.png", "my-lists-button"},
    {"GJ_myListsTxt_001.png", "my-lists-hint"},
}};

std::array<const char*, 11> RANK_ICONS = {
    "rankIcon_1_001.png", "rankIcon_top10_001.png", "rankIcon_top50_001.png",
    "rankIcon_top100_001.png", "rankIcon_top200_001.png", "rankIcon_top500_001.png",
    "rankIcon_top1000_001.png", "rankIcon_top2500_001.png", "rankIcon_top5000_001.png",
    "rankIcon_top10000_001.png", "rankIcon_all_001.png"
};

std::array<const char*, 3> MOD_BADGES = {
    "modBadge_01_001.png", "modBadge_02_001.png", "modBadge_03_001.png"
};

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

    const char* getButtonID(CCNode* node, std::string_view prevID, bool& seenReport) {
        if (isSpriteFrameName(node, "GJ_reportBtn_001.png")) {
            seenReport = true;
            return "report-button";
        }
        for (auto frame : MOD_BADGES) {
            if (isSpriteFrameName(node, frame)) return seenReport ? "mod-button" : "mod-badge";
        }
        if (isSpriteFrameName(node, "accountBtn_requests_001.png")) {
            return m_ownProfile ? "requests-button" : "friend-button";
        }
        for (auto& [frame, id] : FRAME_IDS) {
            if (isSpriteFrameName(node, frame)) return id;
        }
        for (auto frame : RANK_ICONS) {
            if (isSpriteFrameName(node, frame)) return "global-rank-icon";
        }
        if (prevID == "global-rank-hint" && typeinfo_cast<CCLabelBMFont*>(node)) {
            return "global-rank-label";
        }
        return nullptr;
    }

    void setRemainingIDs(std::vector<CCNode*> const& nodes, size_t idx) {
        bool seenReport = false;
        std::string_view prevID;
        for (; idx < nodes.size(); idx++) {
            if (auto id = getButtonID(nodes[idx], prevID, seenReport)) {
                nodes[idx]->setID(id);
                prevID = id;
            }
            else {
                prevID = "";
            }
        }
    }

    void createBottomMenu(float gap, CCSize size, std::initializer_list<const char*> ids) {
        auto winSize = CCDirector::get()->getWinSize();

        std::vector<CCNode*> buttons;
        for (auto id : ids) {
            if (auto btn = m_buttonMenu->getChildByID(id)) buttons.push_back(btn);
        }
        if (buttons.empty()) return;

        auto bottomMenu = CCMenu::create();
        bottomMenu->setID("bottom-menu");
        bottomMenu->setLayout(
            RowLayout::create()
                ->setGap(gap)
                ->setAxisAlignment(AxisAlignment::Center)
        );
        bottomMenu->setPosition(m_mainLayer->convertToNodeSpace(m_buttonMenu->convertToWorldSpace(buttons[0]->getPosition())));
        bottomMenu->setPositionX(winSize.width / 2);
        bottomMenu->setZOrder(20);
        bottomMenu->setContentSize(size);
        m_mainLayer->addChild(bottomMenu);

        for (auto btn : buttons) switchToMenu(btn, bottomMenu);

        bottomMenu->updateLayout();
        m_buttons->addObject(bottomMenu);
    }

    void loadPageFromUserInfo(GJUserScore* score) {
        ProfilePage::loadPageFromUserInfo(score);

        NodeIDs::get()->provide(this);

        if (!score) return;

        auto winSize = CCDirector::get()->getWinSize();

        std::vector<CCNode*> nodes;
        for (auto node : CCArrayExt<CCNode*>(m_buttons)) {
            nodes.push_back(node);
        }
        size_t idx = 0;

        // blocked users only get the account buttons
        if (score->m_friendReqStatus == 2) {
            setRemainingIDs(nodes, idx);
            createBottomMenu(12.f, {270, 35}, {"unblock-button", "report-button", "mod-button"});
            return;
        }

        auto statsMenu = m_mainLayer->getChildByID("stats-menu");

        while (idx + 1 < nodes.size()) {
            const char* label = nullptr;
            for (auto& [frame, name] : STAT_ICONS) {
                if (isSpriteFrameName(nodes[idx + 1], frame)) {
                    label = name;
                    break;
                }
            }
            if (!label) break;

            auto bmFont = nodes[idx++];
            auto icon = nodes[idx++];

            bmFont->setID(fmt::format("{}-label", label));
            bmFont->setZOrder(0);
            bmFont->removeFromParent();

            auto bmFontContainer = CCNode::create();
            bmFontContainer->setContentSize({bmFont->getScaledContentSize().width, bmFont->getScaledContentSize().height});
            bmFontContainer->addChild(bmFont);
            bmFontContainer->setID(fmt::format("{}-label-container", label));
            bmFontContainer->setLayoutOptions(
                AxisLayoutOptions::create()
                    ->setScaleLimits(.0f, 1.f)
            );

            bmFont->setPosition({0, bmFontContainer->getContentSize().height / 2});

            icon->removeFromParent();
            icon->setID(fmt::format("{}-icon", label));
            icon->setZOrder(0);
            icon->setLayoutOptions(
                AxisLayoutOptions::create()
                    ->setRelativeScale(.9f)
                    ->setScaleLimits(.0f, 1.f)
                    ->setNextGap(7.0f)
            );
            if(typeinfo_cast<CCMenuItemSpriteExtra*>(icon)) {
                auto child = static_cast<CCNode*>(icon->getChildren()->objectAtIndex(0));
                child->setScale(1.f);

                icon->setContentSize(child->getContentSize());
                child->setPosition(
                    icon->getContentWidth() / 2,
                    icon->getContentHeight() / 2
                );
            }

            if(statsMenu) {
                statsMenu->addChild(bmFontContainer);
                statsMenu->addChild(icon);
                m_buttons->addObject(bmFontContainer);
            }
        }

        if (statsMenu) {
            statsMenu->setContentSize({420, 120});
            statsMenu->updateLayout();
        }

        std::vector<CCNode*> players;
        for (auto id : PLAYER_IDS) {
            if (idx >= nodes.size() || !nodes[idx]->getChildByType<SimplePlayer>(0)) break;
            nodes[idx]->setID(id);
            players.push_back(nodes[idx++]);
        }

        if (!players.empty()) {
            auto playerMenu = CCMenu::create();
            playerMenu->setID("player-menu");
            playerMenu->setLayout(
                RowLayout::create()
                    ->setGap(13.f)
                    ->setAxisAlignment(AxisAlignment::Center)
            );
            playerMenu->setPosition(m_mainLayer->convertToNodeSpace(m_buttonMenu->convertToWorldSpace(players[0]->getPosition())));
            playerMenu->setPositionX(winSize.width / 2);
            playerMenu->setContentSize({380, 35});
            playerMenu->setZOrder(10);
            m_mainLayer->addChild(playerMenu);

            for (auto player : players) switchToMenu(player, playerMenu);

            playerMenu->updateLayout();
            m_buttons->addObject(playerMenu);
        }

        setRemainingIDs(nodes, idx);

        if(auto commentBtn = m_buttonMenu->getChildByID("comment-history-button")) {
            if(auto rightMenu = m_mainLayer->getChildByID("right-menu")) {
                commentBtn->setZOrder(-2);
                switchToMenu(commentBtn, rightMenu);
                rightMenu->updateLayout();
            }
        }

        if(m_ownProfile) {
            createBottomMenu(20.f, {340, 35}, {"message-button", "friend-button", "requests-button", "notifications-button", "settings-button"});
        }
        else {
            createBottomMenu(12.f, {270, 35}, {"message-button", "friend-button", "block-button", "report-button", "mod-button"});
        }

        if(auto socialsMenu = m_mainLayer->getChildByID("socials-menu")) {
            for (auto id : {"socials-button", "youtube-button", "twitter-button", "twitch-button", "instagram-button", "tiktok-button"}) {
                if (auto button = m_buttonMenu->getChildByID(id)) {
                    button->removeFromParent();
                    socialsMenu->addChild(button);
                }
            }
            socialsMenu->updateLayout();
        }

        if(auto usernameMenu = m_mainLayer->getChildByID("username-menu")) {
            if(auto modBadge = m_buttonMenu->getChildByID("mod-badge")) {
                modBadge->retain();
                modBadge->removeFromParent();
                usernameMenu->addChild(modBadge);
                if(usernameMenu->getPositionX() == (winSize.width / 2)) usernameMenu->setPositionX((winSize.width / 2) - 13.f);
                modBadge->release();
            } else {
                if(usernameMenu->getPositionX() == (winSize.width / 2) - 13.f) usernameMenu->setPositionX(winSize.width / 2);
            }
            usernameMenu->updateLayout();

            if(auto infoButton = m_buttonMenu->getChildByID("info-button")) {
                infoButton->setPosition(
                    (usernameMenu->getPosition() - m_buttonMenu->getPosition()) + (m_usernameLabel->getScaledContentSize() / 2) + CCPoint(8.f, -5.f) - ( (usernameMenu->getContentSize() / 2) - m_usernameLabel->getPosition() )
                );
            }

            if(auto copyButton = m_buttonMenu->getChildByID("copy-username-button")) {
                copyButton->setPosition(
                    (usernameMenu->getPosition() - m_buttonMenu->getPosition()) - ( (usernameMenu->getContentSize() / 2) - m_usernameLabel->getPosition() )
                );
            }
        }

    }
};
