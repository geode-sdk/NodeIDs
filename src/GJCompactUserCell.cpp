#include <Geode/modify/GJCompactUserCell.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

struct GJCompactUserCellIDs : Modify<GJCompactUserCellIDs, GJCompactUserCell> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("GJCompactUserCell::buildUserRow", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set GJCompactUserCell::buildUserRow hook priority, node IDs may not work properly");
        }
    }

    static cocos2d::CCLabelBMFont* buildUserRow(GJUserScore* score, CCNode* fakeMainLayer, CCNode* playerNameMenu, CCObject* selectorTarget, SEL_MenuHandler selector, float y, bool dimmed, bool showFriendIcon) {
        auto label = GJCompactUserCell::buildUserRow(score, fakeMainLayer, playerNameMenu, selectorTarget, selector, y, dimmed, showFriendIcon);

        label->setID("player-name-label");

        // workaround for MemberListPopup
        auto mainLayer = fakeMainLayer;
        if (auto parent = label->getParent()) {
            parent->setID("player-name");
            if (auto parent2 = parent->getParent()) {
                playerNameMenu = parent2;
                if (auto parent3 = parent2->getParent(); parent3 && parent3->getParent() == fakeMainLayer) {
                    mainLayer = parent3;
                }
            }
        }

        size_t offset = mainLayer->getChildrenCount() - 6;
        size_t menuOffset = playerNameMenu->getChildrenCount() - 1;

        if(auto player = mainLayer->getChildByType<SimplePlayer>(-1)) {
            player->setID("player-icon");
        }

        if (auto newLabel = mainLayer->getChildByTag(100)) {
            newLabel->setID("new-label");
        }

        if(score->m_creatorPoints > 0) {
            offset -= 2;
        }

        setIDs(
            mainLayer,
            offset,
            "stars-label",
            "stars-icon",
            "moons-label",
            "moons-icon",
            "demons-label",
            "demons-icon"
        );
        offset += 6;
        
        if(score->m_creatorPoints > 0) {
            setIDs(
                mainLayer,
                offset,
                "creator-points-label",
                "creator-points-icon"
            );
            offset += 2;
        }

        int friendSince = score->m_friendTimestamp;
        bool isStoredFriend = false;
        if (score->m_friendStatus == 0 && friendSince <= 0) {
            if (auto stored = GameLevelManager::get()->storedFriendForAccountID(score->m_accountID)) {
                isStoredFriend = true;
                friendSince = stored->m_friendTimestamp;
            }
        }

        if (showFriendIcon && (score->m_friendStatus == 1 || friendSince > 0 || isStoredFriend)) {
            if (auto friendIcon = getChildBySpriteFrameName(mainLayer, "GJ_sFriendsIcon_001.png", -1)) {
                friendIcon->setID("friend-icon");
            }
        }

        if (friendSince > 0) {
            if (auto btn = playerNameMenu->getChildByType<InfoAlertButton>(-1)) {
                btn->setID("info-button");
            }
        }

        // building stats menu
        std::array nodes = {
            "stars-label",
            "stars-icon",
            "moons-label",
            "moons-icon",
            "demons-label",
            "demons-icon",
            "creator-points-label",
            "creator-points-icon"
        };

        auto statsMenu = CCMenu::create();
        statsMenu->setLayout(
            RowLayout::create()
                ->setGap(1.f)
                ->setAxisAlignment(AxisAlignment::Start)
        );
        statsMenu->setID("stats-menu");
        
        size_t idx = 0;
        for(auto node: nodes) {
            if(auto child = mainLayer->getChildByID(node)) {
                switchToMenu(child, statsMenu);

                auto options = AxisLayoutOptions::create()
                    ->setScaleLimits(.0f, 1.f)
                    ->setRelativeScale(child->getScale()
                );
                if(idx++ % 2 == 1) options->setNextGap(8.f);

                child->setLayoutOptions(options);
            }
        }

        mainLayer->addChild(statsMenu);
        statsMenu->setPosition({46.f, y - 8.f});
        statsMenu->setContentSize({ 192.f, 60.f });
        statsMenu->setAnchorPoint({ 0.f, 0.5f });
        statsMenu->updateLayout();

        return label;
    }
};
