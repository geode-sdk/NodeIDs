#include <Geode/Bindings.hpp>
#include <Geode/modify/MoreVideoOptionsLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(MoreVideoOptionsLayer) {
    auto mainLayer = static_cast<cocos2d::CCLayer*>(this->getChildren()->objectAtIndex(0));
    mainLayer->setID("main-layer");

    setIDSafe<CCLabelBMFont>(mainLayer, 0,          "title");
    setIDSafe<CCLabelBMFont>(mainLayer, 1,          "fps-label");

    auto buttonMenu = mainLayer->getChildByType<cocos2d::CCLayer>(0);
    buttonMenu->setID("buttons-menu");

    setIDSafe<CCMenuItemToggler>(buttonMenu, 0,     "vsync-toggle");
    setIDSafe<CCMenuItemToggler>(buttonMenu, 1,     "smoothfix-toggle");
    setIDSafe<CCMenuItemToggler>(buttonMenu, 2,     "showfps-toggle");
    setIDSafe<CCMenuItemToggler>(buttonMenu, 3,     "unlockfps-toggle");

    setIDSafe<CCMenuItemSpriteExtra>(buttonMenu, 0, "info-vsync");
    setIDSafe<CCMenuItemSpriteExtra>(buttonMenu, 1, "info-smoothfix");
    setIDSafe<CCMenuItemSpriteExtra>(buttonMenu, 2, "info-showfps");
    setIDSafe<CCMenuItemSpriteExtra>(buttonMenu, 3, "info-unlockfps");
    // setIDSafe<CCMenuItemSpriteExtra>(buttonMenu, 4, "fps-bypass-apply");
    setIDSafe<CCMenuItemSpriteExtra>(buttonMenu, 5, "close");

    // APPLY BUTTON
    auto applyButton = buttonMenu->getChildByType<CCMenuItemSpriteExtra>(4);
    auto applyButtonSpr = applyButton->getChildByType<ButtonSprite>(0);
    applyButton->setID("apply-button");
    applyButtonSpr->setID("button-sprite");
    
    setIDSafe<ButtonSprite>(applyButton, 0,         "button-sprite");
    setIDSafe<CCLabelBMFont>(applyButtonSpr, 0,     "apply-label");

    

    auto labelLayer = mainLayer->getChildByType<cocos2d::CCLayer>(1);
    labelLayer->setID("label-layer");

    setIDSafe<CCLabelBMFont>(labelLayer, 0,         "vsync-label");
    setIDSafe<CCLabelBMFont>(labelLayer, 1,         "smoothfix-label");
    setIDSafe<CCLabelBMFont>(labelLayer, 2,         "showfps-label");
    setIDSafe<CCLabelBMFont>(labelLayer, 3,         "unlockfps-label");

}

struct MoreVideoOptionsLayerIDs : Modify<MoreVideoOptionsLayerIDs, MoreVideoOptionsLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("MoreVideoOptionsLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set MoreVideoOptionsLayer::init hook priority, node IDs may not work properly");
        }
    }

    bool init() {
        if (!MoreVideoOptionsLayer::init()) return false;

        NodeIDs::get()->provide(this);
        return true;
    }
};
