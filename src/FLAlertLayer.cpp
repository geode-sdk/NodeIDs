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
    if(!m_containsBorder) m_mainLayer->getChildByType<CCSprite>(spriteOffset++)->setID("content-text-area");

    m_mainLayer->getChildByType<CCScale9Sprite>(0)->setID("background");
    m_mainLayer->getChildByType<CCLabelBMFont>(labelOffset++)->setID("title");

    if(m_containsBorder) {
        if(auto scrollLayer = m_mainLayer->getChildByType<ScrollingLayer>(0)) {
            scrollLayer->setID("scroll-layer");
            scrollLayer->getChildByType<CCLayer>(1)->getChildByType<TextArea>(0)->setID("content-text-area");
        }
    }

    m_buttonMenu->setID("main-menu");
    m_button1->getParent()->setID("button-1");
    if(!m_noAction) m_button2->getParent()->setID("button-2");

    if(PlatformToolbox::isControllerConnected()) {
        m_mainLayer->getChildByType<CCSprite>(spriteOffset++)->setID("controller-back-hint");
        if(!m_noAction) m_mainLayer->getChildByType<CCSprite>(spriteOffset++)->setID("controller-ok-hint");
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
