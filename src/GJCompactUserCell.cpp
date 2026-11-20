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

    static cocos2d::CCLabelBMFont* buildUserRow(GJUserScore* score, CCNode* mainLayer, CCMenu* playerNameMenu, CCObject* selectorTarget, SEL_MenuHandler selector, float y, bool dimmed, bool showFriendIcon) {
        auto label = GJCompactUserCell::buildUserRow(score, mainLayer, playerNameMenu, selectorTarget, selector, y, dimmed, showFriendIcon);

        size_t offset = mainLayer->getChildrenCount() - 6;
        size_t menuOffset = playerNameMenu->getChildrenCount() - 1;

        label->setID("player-name-label");
        if(auto parent = label->getParent()) {
            parent->setID("player-name");
        }

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

        bool skipFriendInfo = false;

        int friendState = score->m_friendStatus;
        int friendSince = score->m_friendTimestamp;
        if (auto btn = typeinfo_cast<InfoAlertButton*>(playerNameMenu->getChildren()->objectAtIndex(menuOffset))) {
            btn->setID("info-button");
            menuOffset--;
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
