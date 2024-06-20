#include <Geode/Bindings.hpp>
#include <Geode/modify/LevelLeaderboard.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(LevelLeaderboard) {
    size_t buttonOffset = 0;
    size_t labelOffset = 0;
    size_t spriteOffset = 0;

    auto winSize = CCDirector::get()->getWinSize();

    m_buttonMenu->setID("main-menu");

    getChildOfType<CCScale9Sprite>(m_mainLayer, 0)->setID("background");

    getChildOfType<CCLabelBMFont>(m_mainLayer, labelOffset)->setID("title-label");
    labelOffset++;

    if(m_level->isPlatformer()) {

        getChildOfType<CCSprite>(m_mainLayer, spriteOffset)->setID("mode-icon");
        spriteOffset++;

        getChildOfType<CCMenuItemSpriteExtra>(m_buttonMenu, buttonOffset)->setID("time-button");
        buttonOffset++;

        getChildOfType<CCMenuItemSpriteExtra>(m_buttonMenu, buttonOffset)->setID("points-button");
        buttonOffset++;

        if(m_level->m_levelType == GJLevelType::Editor) {
            getChildOfType<CCMenuItemSpriteExtra>(m_buttonMenu, buttonOffset)->setID("clear-button");
            buttonOffset++;
        }
    }

    getChildOfType<CCMenuItemSpriteExtra>(m_buttonMenu, buttonOffset)->setID("close-button");
    buttonOffset++;

    getChildOfType<CCMenuItemSpriteExtra>(m_buttonMenu, buttonOffset)->setID("update-button");
    buttonOffset++;

    getChildOfType<LoadingCircle>(m_mainLayer, 0)->setID("loading-circle");
    getChildOfType<TextArea>(m_mainLayer, 0)->setID("no-internet-text");

    if(m_level->m_levelType != GJLevelType::Editor) {
        if(auto secondMenu = getChildOfType<CCMenu>(m_mainLayer, 1)) {
            secondMenu->setID("type-menu");
            setIDs(
                secondMenu,
                0,
                "friends-button",
                "global-button",
                "weekly-button",
                "local-button"
            );

            bool has4buttons = secondMenu->getChildByID("local-button") != nullptr;

            secondMenu->setPosition((winSize.width / 2) + 195.f, winSize.height / 2 - (has4buttons ? 30.f : 35.f));
            secondMenu->setContentSize({ 60.f, has4buttons ? 210.f : 190.f });
            secondMenu->setLayout(
                ColumnLayout::create()
                    ->setGap(8.5f)
                    ->setAxisAlignment(AxisAlignment::End)
                    ->setAxisReverse(true)
            );
        }
    } else {
        //let's make the menu available for mods to use if needed
        auto secondMenu = CCMenu::create();
        secondMenu->setID("type-menu");
        secondMenu->setPosition((winSize.width / 2) + 195.f, winSize.height / 2 - 30.f);
        secondMenu->setContentSize({ 50.f, 210.f});
        secondMenu->setLayout(
            ColumnLayout::create()
                ->setGap(8.5f)
                ->setAxisAlignment(AxisAlignment::End)
                ->setAxisReverse(true)
        );
        m_mainLayer->addChild(secondMenu);
    }
    
    auto modeMenu = detachAndCreateMenu(
        m_mainLayer,
        "mode-menu",
        ColumnLayout::create()
            ->setGap(17.f)
            ->setAxisAlignment(AxisAlignment::End)
            ->setAxisReverse(true),
        m_buttonMenu->getChildByID("time-button"),
        m_buttonMenu->getChildByID("points-button")
    );
    
    for(auto& child : CCArrayExt<CCNode*>(modeMenu->getChildren())) {
        child->setLayoutOptions(
            AxisLayoutOptions::create()
                ->setScaleLimits(.1f, .7f)
        );
    }

    modeMenu->setPosition((winSize.width / 2) - 195.f, winSize.height / 2 - 31.f);
    modeMenu->setContentSize({ 50.f, 210.f });
    modeMenu->updateLayout();

}

struct LevelLeaderboardIDs : Modify<LevelLeaderboardIDs, LevelLeaderboard> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("LevelLeaderboard::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set LevelLeaderboard::init hook priority, node IDs may not work properly");
        }
    }

    bool init(GJGameLevel* level, LevelLeaderboardType type, LevelLeaderboardMode mode) {
        if (!LevelLeaderboard::init(level, type, mode)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};
