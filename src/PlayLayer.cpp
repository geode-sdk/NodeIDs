#include <Geode/Bindings.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(PlayLayer) {
    setIDSafe(this, 1, "main-node");
    auto mainNode = this->getChildByID("main-node");
    setIDSafe<CCSprite>(mainNode, 0, "background");
    setIDSafe<CCLayer>(mainNode, 0, "batch-layer");

    setIDSafe(this, 3, "hitbox-node");
    setIDSafe<GJEffectManager>(this, 0, "effect-manager");
    //setIDSafe<UILayer>(this, 0, "ui-layer"); //changing this id is unsafe because mods depend on "UILayer", which is actually fairly safe to do, since this is the only UILayer in the whole layer
    int index = 0;
#if GEODE_COMP_GD_VERSION >= 22060
    if (this->m_level->m_levelType == GJLevelType::Editor) {
        // Testmode is only added for local levels
        setIDSafe<CCLabelBMFont>(this, 0, "testmode-label");
        index++;
    }
#endif

    setIDSafe<CCLabelBMFont>(this, index++, "debug-text");
    setIDSafe<CCSprite>(this, 0, "progress-bar");

    if (this->m_level->isPlatformer()) {
        setIDSafe<CCLabelBMFont>(this, index, "time-label");
    }
    else {
        setIDSafe<CCLabelBMFont>(this, index, "percentage-label");
    }

#if GEODE_COMP_GD_VERSION == 22000
    setIDSafe<CCLabelBMFont>(this, 2, "testmode-label");
#endif
}

struct PlayLayerIDs : Modify<PlayLayerIDs, PlayLayer> {
    struct Fields {
        bool m_dontCreateObjects = false;
    };

    static void onModify(auto& self) {
        if (!self.setHookPriority("PlayLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set PlayLayer::init hook priority, node IDs may not work properly");
        }

        if (!self.setHookPriority("PlayLayer::setupHasCompleted", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set PlayLayer::setupHasCompleted hook priority, node IDs may not work properly");
        }
    }

    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;

        // Used in online levels, which delays node creation
        m_fields->m_dontCreateObjects = dontCreateObjects;

        NodeIDs::get()->provide(this);

        return true;
    }

    void setupHasCompleted() {
        // P.S. For some reason, RobTop adds the nodes in this method,
        // which isn't called from PlayLayer::init if it's an online level
        if (!m_fields->m_dontCreateObjects)
            return PlayLayer::setupHasCompleted();

        // Save preinitialized nodes
        std::unordered_set<cocos2d::CCNode*> nodes;
        for (auto child : CCArrayExt<CCNode*>(this->getChildren())) {
            nodes.insert(child);
        }

        PlayLayer::setupHasCompleted();

        // Filter only new nodes
        std::vector<cocos2d::CCNode*> newNodes;
        for (auto child : CCArrayExt<CCNode*>(this->getChildren())) {
            if (nodes.find(child) == nodes.end()) {
                // skip ShaderLayer, because it can break ordering
                if (typeinfo_cast<ShaderLayer*>(child))
                  continue;
                newNodes.push_back(child);
            }
        }

        // Provide ids for new nodes
        #if GEODE_COMP_GD_VERSION == 22000
            bool isSizeCorrect = newNodes.size() == 3 || newNodes.size() == 4;
        #else
            bool isSizeCorrect = newNodes.size() == 3;
        #endif

        // Shouldn't be false, but just in case
        if (isSizeCorrect) {
            auto debugText = typeinfo_cast<CCLabelBMFont*>(newNodes[0]);
            auto progressBar = typeinfo_cast<CCSprite*>(newNodes[1]);
            auto timeOrPercentageLabel = typeinfo_cast<CCLabelBMFont*>(newNodes[2]);

            if (debugText) debugText->setID("debug-text");
            if (progressBar) progressBar->setID("progress-bar");
            if (timeOrPercentageLabel) {
                if (this->m_level->isPlatformer()) {
                    timeOrPercentageLabel->setID("time-label");
                }
                else {
                    timeOrPercentageLabel->setID("percentage-label");
                }
            }

            #if GEODE_COMP_GD_VERSION == 22000
            if (newNodes.size() == 4) {
                auto testModeLabel = typeinfo_cast<CCLabelBMFont*>(newNodes[3]);
                if (testModeLabel) testModeLabel->setID("testmode-label");
            }
            #endif
        } else {
            geode::log::warn("Failed to provide IDs for PlayLayer nodes");
        }
    }

};
