#include <Geode/Geode.hpp>
#include <Geode/binding/GauntletNode.hpp>
#include <Geode/modify/GauntletNode.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

struct GauntletNodeIDs : Modify<GauntletNodeIDs, GauntletNode> {
    struct Fields {
        GJMapPack* m_gauntlet;
    };

    static void onModify(auto& self) {
        if (!self.setHookPriority("GauntletNode::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set GauntletNode::init hook priority, node IDs may not work properly");
        }
    }

    bool init(GJMapPack* gauntlet) {
        if (!GauntletNode::init(gauntlet)) return false;

        m_fields->m_gauntlet = gauntlet;

        NodeIDs::get()->provide(this);

        return true;
    }
};

$register_ids(GauntletNode) {
    const auto GSM = GameStatsManager::sharedState();
    auto self = reinterpret_cast<GauntletNodeIDs*>(this);

    if (self->m_fields->m_gauntlet->hasCompletedMapPack()) {
        setIDs(
            this,
            0,
            "gauntlet-info-node",
            "reward-node",
            "background",
            "gauntlet-name-label",
            "gauntlet-label",
            "gauntlet-name-shadow-label",
            "gauntlet-shadow-label",
            "checkmark-sprite",
            "checkmark-shadow-sprite"
        );
    } else {
        setIDs(
            this,
            0,
            "gauntlet-info-node",
            "reward-node",
            "background",
            "gauntlet-name-label",
            "gauntlet-label",
            "gauntlet-name-shadow-label",
            "gauntlet-shadow-label"
        );
    }

    if (
        self->m_fields->m_gauntlet->hasCompletedMapPack() &&
        GSM->isSpecialChestUnlocked(GSM->getGauntletRewardKey(self->m_fields->m_gauntlet->m_packID))
    ) {
        setIDs(
            m_gauntletInfoNode,
            0,
            "gauntlet-sprite",
            "gauntlet-shadow-sprite",
            "gauntlet-progress-label",
            "gauntlet-progress-shadow-label"
        );
    } else {
        setIDs(
            m_gauntletInfoNode,
            0,
            "gauntlet-sprite",
            "gauntlet-shadow-sprite",
            "gauntlet-progress-label",
            "gauntlet-progress-shadow-label",
            "reward-label",
            "reward-shadow-label",
            "chest-sprite",
            "chest-shadow-sprite"
        );

        setIDs(
            m_rewardNode,
            0,
            "reward-label",
            "reward-shadow-label",
            "chest-sprite",
            "chest-shadow-sprite"
        );
    }

    verifyIDSafe(m_gauntletInfoNode, "gauntlet-info-node");
    verifyIDSafe(m_rewardNode, "reward-node");
}
