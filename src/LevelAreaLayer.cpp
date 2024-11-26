#include <Geode/Geode.hpp>
#include <Geode/binding/LevelAreaLayer.hpp>
#include <Geode/modify/LevelAreaLayer.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(LevelAreaLayer) {
    this->setID("main-layer");

    this->getChildByType<CCSprite>(0)->setID("background");
    this->getChildByType<CCSprite>(1)->setID("tower-sprite");
    this->getChildByType<CCSprite>(2)->setID("fade-left");
    this->getChildByType<CCSprite>(3)->setID("fade-right");
    this->getChildByType<CCSprite>(4)->setID("fade-bottom");
    this->getChildByType<CCSprite>(5)->setID("light-1");
    this->getChildByType<CCSprite>(6)->setID("tower-glow-1");
    this->getChildByType<CCSprite>(7)->setID("light-2");
    this->getChildByType<CCSprite>(8)->setID("tower-glow-2");
    this->getChildByType<CCSprite>(9)->setID("light-3");
    this->getChildByType<CCSprite>(10)->setID("tower-glow-3");
    this->getChildByType<CCSprite>(11)->setID("light-4");
    this->getChildByType<CCSprite>(12)->setID("tower-glow-4");
    this->getChildByType<CCSprite>(13)->setID("light-5");
    this->getChildByType<CCSprite>(14)->setID("tower-glow-5");
    this->getChildByType<CCSprite>(15)->setID("light-6");
    this->getChildByType<CCSprite>(16)->setID("tower-glow-6");

    this->getChildByType<CCParticleSystemQuad>(0)->setID("sparkle");

    this->getChildByType<CCMenu>(0)->setID("back-menu");
    this->getChildByType<CCMenu>(1)->setID("enter-menu");

    this->getChildByID("back-menu")->getChildByType<CCMenuItemSpriteExtra>(0)->setID("back-btn");
    this->getChildByID("enter-menu")->getChildByType<CCMenuItemSpriteExtra>(0)->setID("enter-btn");

    this->getChildByType<CCLayerGradient>(0)->setID("top-glow");
}

struct LevelAreaLayerIDs : Modify<LevelAreaLayerIDs, LevelAreaLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("LevelAreaLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set LevelAreaLayer::init hook priority, node IDs may not work properly");
        }
    }

    virtual bool init() {
        if (!LevelAreaLayer::init()) 
            return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};
