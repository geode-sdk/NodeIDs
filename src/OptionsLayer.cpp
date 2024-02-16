#include <Geode/Bindings.hpp>
#include <Geode/modify/OptionsLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;


$register_ids(OptionsLayer) {
    size_t labelOffset = 0;
    size_t menuOffset = 0;
    size_t sliderOffset = 0;
    size_t optionsMenuOffset = 0;

    auto optionsLayer = static_cast<cocos2d::CCLayer*>(this->getChildren()->objectAtIndex(0));
    auto winSize = CCDirector::get()->getWinSize();

    getChildOfType<cocos2d::CCLabelBMFont>(optionsLayer, labelOffset)->setID("music-label");
    labelOffset++;

    getChildOfType<cocos2d::CCLabelBMFont>(optionsLayer, labelOffset)->setID("sfx-label");
    labelOffset++;

    getChildOfType<cocos2d::CCLabelBMFont>(optionsLayer, labelOffset)->setID("menu-music-label");

    getChildOfType<Slider>(optionsLayer, sliderOffset)->setID("music-slider");
    sliderOffset++;

    getChildOfType<Slider>(optionsLayer, sliderOffset)->setID("sfx-slider");

    auto topLeftMenu = getChildOfType<cocos2d::CCMenu>(optionsLayer, menuOffset);
    topLeftMenu->setID("top-left-menu");

    auto exitButton = getChildOfType<CCMenuItemSpriteExtra>(topLeftMenu, 0);
    exitButton->setID("exit-button");

    topLeftMenu->setPosition(0, winSize.height - exitButton->getContentSize().height / 1);
    topLeftMenu->setContentSize(ccp(32.5, 40));
    exitButton->setPosition(topLeftMenu->getContentSize().width / 2, topLeftMenu->getContentSize().height / 2);
    menuOffset++;



    getChildOfType<cocos2d::CCMenu>(optionsLayer, menuOffset)->setID("options-menu");
    getChildOfType<cocos2d::CCMenu>(optionsLayer, menuOffset)->setContentSize(ccp(306, 114));
    getChildOfType<cocos2d::CCMenu>(optionsLayer, menuOffset)->setPosition(ccp(winSize.width / 2, 200));
    getChildOfType<cocos2d::CCMenu>(optionsLayer, menuOffset)->setLayout(
    RowLayout::create()
        ->setGap(12.f)
        ->setGrowCrossAxis(true)
        ->setAxisAlignment(AxisAlignment::Start)
    );
    getChildOfType<cocos2d::CCMenu>(optionsLayer, menuOffset)->updateLayout();
    menuOffset++;

    CCMenu* optionsMenu = getChildOfType<cocos2d::CCMenu>(optionsLayer, 1);

    getChildOfType<CCMenuItemSpriteExtra>(optionsMenu, optionsMenuOffset)->setID("account-button");
    optionsMenuOffset++;

    getChildOfType<CCMenuItemSpriteExtra>(optionsMenu, optionsMenuOffset)->setID("how-to-play-button");
    optionsMenuOffset++;

    #ifdef GEODE_IS_DESKTOP
    getChildOfType<CCMenuItemSpriteExtra>(optionsMenu, optionsMenuOffset)->setID("options-button");
    optionsMenuOffset++;

    getChildOfType<CCMenuItemSpriteExtra>(optionsMenu, optionsMenuOffset)->setID("graphics-button");
    optionsMenuOffset++;

    getChildOfType<CCMenuItemSpriteExtra>(optionsMenu, optionsMenuOffset)->setID("rate-button");
    optionsMenuOffset++;

    getChildOfType<CCMenuItemSpriteExtra>(optionsMenu, optionsMenuOffset)->setID("songs-button");
    optionsMenuOffset++;

    getChildOfType<CCMenuItemSpriteExtra>(optionsMenu, optionsMenuOffset)->setID("help-button");
    optionsMenuOffset++;
    
    #else
    getChildOfType<CCMenuItemSpriteExtra>(optionsMenu, optionsMenuOffset)->setID("rate-button");
    optionsMenuOffset++;

    getChildOfType<CCMenuItemSpriteExtra>(optionsMenu, optionsMenuOffset)->setID("songs-button");
    optionsMenuOffset++;

    getChildOfType<CCMenuItemSpriteExtra>(optionsMenu, optionsMenuOffset)->setID("help-button");
    optionsMenuOffset++;

    getChildOfType<CCMenuItemSpriteExtra>(optionsMenu, optionsMenuOffset)->setID("options-button");
    #endif
}

struct OptionsLayerIDs : Modify<OptionsLayerIDs, OptionsLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("OptionsLayer::customSetup", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set OptionsLayer::customSetup hook priority, node IDs may not work properly");
        }
    }

    void customSetup() {
        OptionsLayer::customSetup();

        NodeIDs::get()->provide(this);
    }
};