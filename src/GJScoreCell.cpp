// #include "AddIDs.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/GJScoreCell.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(GJScoreCell) {
    setIDs(
        m_mainLayer,
        0,
        "player-icon",
        "main-menu"
    );

    if(m_score->m_scoreType != 2) {
        setIDs(
            m_mainLayer,
            2,
            "rank-label"
        );
    }

    auto starsLabel = "stars-label";
    auto starsIcon = "stars-icon";
    auto moonsLabel = "moons-label";
    auto moonsIcon = "moons-icon";
    auto demonsLabel = "demons-label";
    auto demonsIcon = "demons-icon";
    auto userCoinsLabel = "user-coins-label";
    auto userCoinsIcon = "user-coins-icon";
    
    switch (m_score->m_leaderboardStat) {
        case LeaderboardStat::Stars:
            starsLabel = "moons-label";
            starsIcon = "moons-icon";
            moonsLabel = "stars-label";
            moonsIcon = "stars-icon";
            break;
        case LeaderboardStat::Demons:
            starsLabel = "demons-label";
            starsIcon = "demons-icon";
            demonsLabel = "stars-label";
            demonsIcon = "stars-icon";
            break;
        case LeaderboardStat::UserCoins:
            starsLabel = "user-coins-label";
            starsIcon = "user-coins-icon";
            userCoinsLabel = "stars-label";
            userCoinsIcon = "stars-icon";
            break;
        default:
            break;
    }
    
    setIDs(
        m_mainLayer,
        m_score->m_scoreType == 2 ? 2 : 3,
        starsLabel,
        starsIcon,
        moonsLabel,
        moonsIcon,
        "diamonds-label",
        "diamonds-icon",
        "coins-label",
        "coins-icon",
        userCoinsLabel,
        userCoinsIcon,
        demonsLabel,
        demonsIcon,
        "creator-points-label",
        "creator-points-icon"
    );

    if(auto menu = m_mainLayer->getChildByID("main-menu")) {
        if(menu->getChildrenCount() > 0) {
            static_cast<CCNode*>(menu->getChildren()->objectAtIndex(0))->setID("player-name");
        }
    }

    std::array<const char*, 10> nodes = {
        "diamonds-label",
        "diamonds-icon",
        "coins-label",
        "coins-icon",
        userCoinsLabel,
        userCoinsIcon,
        demonsLabel,
        demonsIcon,
        "creator-points-label",
        "creator-points-icon"
    };

    auto statsMenu = CCMenu::create();
    statsMenu->setLayout(
        RowLayout::create()
            ->setGap(3.f)
            ->setAxisAlignment(AxisAlignment::Start)
    );
    statsMenu->setID("stats-menu");
    statsMenu->setPosition({(m_width / 2) + 29, (m_height / 2) - 13});
    statsMenu->setContentSize({290, 90});
    statsMenu->setZOrder(10);
    m_mainLayer->addChild(statsMenu);

    size_t idx = 0;
    for(auto node: nodes) {
        if(auto child = m_mainLayer->getChildByID(node)) {
            auto options = AxisLayoutOptions::create()
                ->setScaleLimits(.1f, 1.f)
                ->setRelativeScale(child->getScale()
            );
            if(idx++ % 2 == 1) options->setNextGap(7.f);


            child->removeFromParent();
            child->setLayoutOptions(options);
            statsMenu->addChild(child);
        }
    }

    statsMenu->updateLayout();
    
}

struct GJScoreCellIDs : Modify<GJScoreCellIDs, GJScoreCell> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("GJScoreCell::loadFromScore", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set GJScoreCell::loadFromScore hook priority, node IDs may not work properly");
        }
    }

    void loadFromScore(GJUserScore* score) {
        GJScoreCell::loadFromScore(score);

        NodeIDs::get()->provide(this);
    }
};
