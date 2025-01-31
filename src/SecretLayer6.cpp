#include <Geode/Geode.hpp>
#include <Geode/modify/SecretLayer6.hpp>
#include <Geode/utils/NodeIDs.hpp>

//this layer doesn't exist on Windows
#ifndef GEODE_IS_WINDOWS

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(SecretLayer6) {
    this->setID("main-layer");

    this->getChildByType<CCSprite>(0)->setID("background");
    this->getChildByType<CCLabelBMFont>(0)->setID("title");
    this->getChildByType<SecretGame01Layer>(0)->setID("minigame");
    this->getChildByType<CCMenu>(0)->setID("back-menu");

    this->getChildByID("back-menu")->getChildByType<CCMenuItemSpriteExtra>(0)->setID("back-btn");
}

struct SecretLayer6IDs : Modify<SecretLayer6IDs, SecretLayer6> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("SecretLayer6::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set SecretLayer6::init hook priority, node IDs may not work properly");
        }
    }

    virtual bool init() {
        if (!SecretLayer6::init()) 
            return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};

#endif