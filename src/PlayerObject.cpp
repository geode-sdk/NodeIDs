#include <Geode/Bindings.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(PlayerObject) {
    if(auto layer = setIDSafe(this, 0, "main-layer")) {
        setIDs(
            layer,
            0,
            "gamemode-frame",
            "ship-frame",
            "robot-boost",
            "swing-middle-boost",
            "swing-bottom-boost",
            "swing-top-boost",
            "glow-frame"
        );

        if(auto gamemodeFrame = layer->getChildByID("gamemode-frame")) {
            setIDs(
                gamemodeFrame,
                0,
                "secondary-frame",
                "highlights-frame" // m_iconSpriteWhitener
            );
        }

        if(auto shipFrame = layer->getChildByID("ship-frame")) {
            setIDs(
                shipFrame,
                0,
                "secondary-frame",
                "bird-vehicle-frame", // m_birdVehicle
                "highlights-frame" // m_vehicleSpriteWhitener
            );
        }

        if(auto glowFrame = layer->getChildByID("glow-frame")) {
            setIDs(
                glowFrame,
                0,
                "dash-frame",
                "gamemode-glow",
                "ship-glow"
            );

            if(auto dashFrame = glowFrame->getChildByID("dash-frame")) {
                setIDs(
                    dashFrame,
                    0,
                    "dash-outline"
                );
            }
        }
    }
}

struct PlayerObjectIDs : Modify<PlayerObjectIDs, PlayerObject> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("PlayerObject::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set PlayerObject::init hook priority, node IDs may not work properly");
        }

        if (!self.setHookPriority("PlayerObject::createRobot", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set PlayerObject::createRobot hook priority, node IDs may not work properly");
        }
        
        if (!self.setHookPriority("PlayerObject::createSpider", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set PlayerObject::createSpider hook priority, node IDs may not work properly");
        }
    }

    bool init(int p0, int p1, GJBaseGameLayer* p2, cocos2d::CCLayer* p3, bool p4) {
        if (!PlayerObject::init(p0, p1, p2, p3, p4)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
    
    void createRobot(int p0) {
        PlayerObject::createRobot(p0);

        if(m_robotBatchNode) {
            m_robotBatchNode->setID("robot-frame");
        }
    }

    void createSpider(int p0) {
        PlayerObject::createSpider(p0);

        if(m_spiderBatchNode) {
            m_spiderBatchNode->setID("spider-frame");
        }
    }
};
