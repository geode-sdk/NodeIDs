#include <Geode/Bindings.hpp>
#include <Geode/modify/VideoOptionsLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(VideoOptionsLayer) {
    auto mainLayer = static_cast<cocos2d::CCLayer*>(this->getChildren()->objectAtIndex(0));
    mainLayer->setID("main-layer");

    setIDSafe<CCMenuItemSpriteExtra>(mainLayer, 0, "prev-resolution-button");
    setIDSafe<CCMenuItemSpriteExtra>(mainLayer, 1, "next-resolution-button");

    setIDSafe<CCLabelBMFont>(mainLayer, 0,         "title");
    setIDSafe<CCLabelBMFont>(mainLayer, 1,         "fullscreen-label");
    setIDSafe<CCLabelBMFont>(mainLayer, 2,         "borderless-label");
    setIDSafe<CCLabelBMFont>(mainLayer, 3,         "fix-label");
    setIDSafe<CCLabelBMFont>(mainLayer, 4,         "res-quality");
    setIDSafe<CCLabelBMFont>(mainLayer, 5,         "texture-quality");
    setIDSafe<CCLabelBMFont>(mainLayer, 6,         "texture-label");
    setIDSafe<CCLabelBMFont>(mainLayer, 7,         "res-label");

    auto buttonMenu = mainLayer->getChildByType<cocos2d::CCMenu>(0);
    buttonMenu->setID("buttons-menu");

    setIDSafe<CCMenuItemToggler>(buttonMenu, 0,     "fullscreen-toggle");
    setIDSafe<CCMenuItemToggler>(buttonMenu, 1,     "borderless-toggle");
    setIDSafe<CCMenuItemToggler>(buttonMenu, 2,     "fix-toggle");

    setIDSafe<CCMenuItemSpriteExtra>(buttonMenu, 0, "resolution-left-button");
    setIDSafe<CCMenuItemSpriteExtra>(buttonMenu, 1, "resolution-right-button");

    setIDSafe<CCMenuItemSpriteExtra>(buttonMenu, 2, "texture-left-button");
    setIDSafe<CCMenuItemSpriteExtra>(buttonMenu, 3, "texture-right-button");

    //setIDSafe<CCMenuItemSpriteExtra>(buttonMenu, 4, "back-button");
    //setIDSafe<CCMenuItemSpriteExtra>(buttonMenu, 5, "apply-button");

    setIDSafe<CCMenuItemSpriteExtra>(buttonMenu, 6, "close-button");

    // setIDSafe<CCMenuItemSpriteExtra>(buttonMenu, 7,"advanced-button");

    // BACK BUTTON
    auto backButton = buttonMenu->getChildByType<CCMenuItemSpriteExtra>(4);
    auto backButtonSpr = backButton->getChildByType<ButtonSprite>(0);
    backButton->setID("back-button");
    backButtonSpr->setID("button-sprite");
    
    setIDSafe<ButtonSprite>(backButton, 0,          "button-sprite");
    setIDSafe<CCLabelBMFont>(backButtonSpr, 0,      "back-label");

    // APPLY BUTTON
    auto applyButton = buttonMenu->getChildByType<CCMenuItemSpriteExtra>(5);
    auto applyButtonSpr = applyButton->getChildByType<ButtonSprite>(0);
    applyButton->setID("apply-button");
    applyButtonSpr->setID("button-sprite");
    
    setIDSafe<ButtonSprite>(applyButton, 0,         "button-sprite");
    setIDSafe<CCLabelBMFont>(applyButtonSpr, 0,     "apply-label");

    // ADVANCED BUTTON

    auto advancedButton = buttonMenu->getChildByType<CCMenuItemSpriteExtra>(7);
    auto advancedButtonSpr = advancedButton->getChildByType<ButtonSprite>(0);
    advancedButton->setID("advanced-button");
    advancedButtonSpr->setID("button-sprite");

    setIDSafe<ButtonSprite>(advancedButton, 0,      "button-sprite");
    setIDSafe<CCLabelBMFont>(advancedButtonSpr, 0,  "advanced-label");
    
}

struct VideoOptionsLayerIDs : Modify<VideoOptionsLayerIDs, VideoOptionsLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("VideoOptionsLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set VideoOptionsLayer::init hook priority, node IDs may not work properly");
        }
    }

    bool init() {
        if (!VideoOptionsLayer::init()) return false;

        NodeIDs::get()->provide(this);
        return true;
    }
};
