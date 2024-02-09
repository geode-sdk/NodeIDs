#include <Geode/Bindings.hpp>
#include <Geode/modify/FLAlertLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(FLAlertLayer) {
    size_t buttonOffset = 0;
    size_t labelOffset = 0;
    size_t spriteOffset = 0;

    auto winSize = CCDirector::get()->getWinSize();

    m_mainLayer->setID("main-layer");

    // this is a textarea but this works since textareas subclass ccsprite
    if(!m_containsBorder) getChildOfType<CCSprite>(m_mainLayer, spriteOffset++)->setID("content-text-area");

    getChildOfType<CCScale9Sprite>(m_mainLayer, 0)->setID("background");
    getChildOfType<CCLabelBMFont>(m_mainLayer, labelOffset++)->setID("title");

    if(m_containsBorder) {
        if(auto scrollLayer = getChildOfType<ScrollingLayer>(m_mainLayer, 0)) {
            scrollLayer->setID("scroll-layer");
            getChildOfType<TextArea>(getChildOfType<CCLayer>(scrollLayer, 1), 0)->setID("content-text-area");
        }
    }

    m_buttonMenu->setID("main-menu");
    m_button1->getParent()->setID("button-1");
    if(!m_noAction) m_button2->getParent()->setID("button-2");

    if(PlatformToolbox::isControllerConnected()) {
        getChildOfType<CCSprite>(m_mainLayer, spriteOffset++)->setID("controller-back-hint");
        if(!m_noAction) getChildOfType<CCSprite>(m_mainLayer, spriteOffset++)->setID("controller-ok-hint");
    }
}

struct FLAlertLayerIDs : Modify<FLAlertLayerIDs, FLAlertLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("FLAlertLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set FLAlertLayer::init hook priority, node IDs may not work properly");
        }
    }

    bool init(FLAlertLayerProtocol* a, char const* b, gd::string c, char const* d, char const* e, float f, bool g, float h, float i) {
        if (!FLAlertLayer::init(a, b, c, d, e, f, g, h, i)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};
