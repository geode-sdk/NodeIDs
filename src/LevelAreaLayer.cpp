#include <Geode/Geode.hpp>
#include <Geode/binding/LevelAreaLayer.hpp>
#include <Geode/modify/LevelAreaLayer.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(LevelAreaLayer) {
    this->setID("main-layer");

    size_t spriteIdx = 0;

    // controller icon id assigned in GameToolbox
    if(PlatformToolbox::isControllerConnected()) spriteIdx++;

    setIDSafe<CCSprite>(this, spriteIdx++, "background");
    setIDSafe<CCSprite>(this, spriteIdx++, "tower-sprite");
    setIDSafe<CCSprite>(this, spriteIdx++, "fade-left");
    setIDSafe<CCSprite>(this, spriteIdx++, "fade-right");
    setIDSafe<CCSprite>(this, spriteIdx++, "fade-bottom");
    setIDSafe<CCSprite>(this, spriteIdx++, "light-1");
    setIDSafe<CCSprite>(this, spriteIdx++, "tower-glow-1");
    setIDSafe<CCSprite>(this, spriteIdx++, "light-2");
    setIDSafe<CCSprite>(this, spriteIdx++, "tower-glow-2");
    setIDSafe<CCSprite>(this, spriteIdx++, "light-3");
    setIDSafe<CCSprite>(this, spriteIdx++, "tower-glow-3");
    setIDSafe<CCSprite>(this, spriteIdx++, "light-4");
    setIDSafe<CCSprite>(this, spriteIdx++, "tower-glow-4");
    setIDSafe<CCSprite>(this, spriteIdx++, "light-5");
    setIDSafe<CCSprite>(this, spriteIdx++, "tower-glow-5");
    setIDSafe<CCSprite>(this, spriteIdx++, "light-6");
    setIDSafe<CCSprite>(this, spriteIdx++, "tower-glow-6");

    setIDSafe<CCParticleSystemQuad>(this, 0, "sparkle");

    setIDSafe<CCMenu>(this, 0, "back-menu");
    setIDSafe<CCMenu>(this, 1, "enter-menu");

    if(auto backMenu = this->getChildByID("back-menu")) {
        setIDSafe<CCMenuItemSpriteExtra>(backMenu, 0, "back-btn");
    }

    if(auto enterMenu = this->getChildByID("enter-menu")) {
        setIDSafe<CCMenuItemSpriteExtra>(enterMenu, 0, "enter-btn");
    }

    setIDSafe<CCLayerGradient>(this, 0, "top-glow");
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
