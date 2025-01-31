#include <Geode/Bindings.hpp>
#include <Geode/modify/OptionsLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>
#include <Geode/utils/NodeIDs.hpp>


using namespace geode::prelude;
using namespace geode::node_ids;


$register_ids(OptionsLayer) {
    size_t labelOffset = 0;
    size_t menuOffset = 0;
    size_t sliderOffset = 0;
    size_t buttonOffset = 0;

    auto optionsLayer = static_cast<cocos2d::CCLayer*>(this->getChildren()->objectAtIndex(0));
    optionsLayer->setID("main-layer");

    auto winSize = CCDirector::get()->getWinSize();

    optionsLayer->getChildByType<cocos2d::CCLabelBMFont>(labelOffset)->setID("music-label");
    labelOffset++;

    optionsLayer->getChildByType<cocos2d::CCLabelBMFont>(labelOffset)->setID("sfx-label");
    labelOffset++;

    optionsLayer->getChildByType<cocos2d::CCLabelBMFont>(labelOffset)->setID("menu-music-label");

    optionsLayer->getChildByType<Slider>(sliderOffset)->setID("music-slider");
    sliderOffset++;

    optionsLayer->getChildByType<Slider>(sliderOffset)->setID("sfx-slider");

    optionsLayer->getChildByType<cocos2d::CCSprite>(0)->setID("left-chain");
    optionsLayer->getChildByType<cocos2d::CCSprite>(1)->setID("right-chain");
    optionsLayer->getChildByType<GJListLayer>(0)->setID("background"); // sorry i had nothing other than background for this

    auto topLeftMenu = optionsLayer->getChildByType<cocos2d::CCMenu>(menuOffset);
    topLeftMenu->setID("top-left-menu");

    auto exitButton = topLeftMenu->getChildByType<CCMenuItemSpriteExtra>(0);
    exitButton->setID("exit-button");

    topLeftMenu->setPosition(0, winSize.height - exitButton->getContentSize().height / 1);
    topLeftMenu->setContentSize(ccp(32.5, 40));
    exitButton->setPosition(topLeftMenu->getContentSize().width / 2, topLeftMenu->getContentSize().height / 2);
    menuOffset++;



    auto optionsMenu = optionsLayer->getChildByType<cocos2d::CCMenu>(menuOffset);
    optionsMenu->setID("options-menu");
    optionsMenu->setContentSize(ccp(306, 114));
    optionsMenu->setPosition(ccp(winSize.width / 2, (winSize.height / 2) + 40));
    optionsMenu->setLayout(
    RowLayout::create()
        ->setGap(10.f)
        ->setGrowCrossAxis(true)
        ->setAxisAlignment(AxisAlignment::Center)
    );
    menuOffset++;

    auto vaultMenu = optionsLayer->getChildByType<cocos2d::CCMenu>(menuOffset);
    vaultMenu->setID("vault-menu");

    vaultMenu->getChildByType<CCMenuItemSpriteExtra>(0)->setID("vault-button");
    vaultMenu->getChildByType<CCMenuItemToggler>(0)->setID("menu-music-toggle");

    optionsMenu->getChildByType<CCMenuItemSpriteExtra>(buttonOffset)->setID("account-button");
    buttonOffset++;

    optionsMenu->getChildByType<CCMenuItemSpriteExtra>(buttonOffset)->setID("how-to-play-button");
    buttonOffset++;

    #ifdef GEODE_IS_DESKTOP
    optionsMenu->getChildByType<CCMenuItemSpriteExtra>(buttonOffset)->setID("options-button");
    buttonOffset++;

    optionsMenu->getChildByType<CCMenuItemSpriteExtra>(buttonOffset)->setID("graphics-button");
    buttonOffset++;

    optionsMenu->getChildByType<CCMenuItemSpriteExtra>(buttonOffset)->setID("rate-button");
    buttonOffset++;

    optionsMenu->getChildByType<CCMenuItemSpriteExtra>(buttonOffset)->setID("songs-button");
    buttonOffset++;

    optionsMenu->getChildByType<CCMenuItemSpriteExtra>(buttonOffset)->setID("help-button");
    buttonOffset++;

    #else
    auto options = optionsMenu->getChildByType<CCMenuItemSpriteExtra>(buttonOffset);
    options->setID("options-button");
    options->setZOrder(1);
    buttonOffset++;

    optionsMenu->getChildByType<CCMenuItemSpriteExtra>(buttonOffset)->setID("rate-button");
    buttonOffset++;

    optionsMenu->getChildByType<CCMenuItemSpriteExtra>(buttonOffset)->setID("songs-button");
    buttonOffset++;

    optionsMenu->getChildByType<CCMenuItemSpriteExtra>(buttonOffset)->setID("help-button");
    #endif
    
    optionsMenu->updateLayout();
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
