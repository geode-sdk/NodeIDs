#include <Geode/Bindings.hpp>
#include <Geode/modify/ChallengeNode.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>
#include <Geode/utils/NodeIDs.hpp>


using namespace geode::prelude;
using namespace geode::node_ids;

struct ChallengeNodeIDs : Modify<ChallengeNodeIDs, ChallengeNode> {
    struct Fields {
        bool m_isNew;
    };

    static void onModify(auto& self) {
        if (!self.setHookPriority("ChallengeNode::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set ChallengeNode::init hook priority, node IDs may not work properly");
        }
    }

    bool init(GJChallengeItem* challenge, ChallengesPage* page, bool isNew) {
        if(!ChallengeNode::init(challenge, page, isNew)) return false;

        m_fields->m_isNew = isNew;

        NodeIDs::get()->provide(this);

        return true;
    }
};

$register_ids(ChallengeNode) {
    size_t offset = 0;
    auto self = reinterpret_cast<ChallengeNodeIDs*>(this);

    if(!m_challengeItem) {
        setIDs(
            this,
            offset,
            "background",
            "countdown-label"
        );
        
        return;
    }

    setIDs(
        this,
        offset,
        "background",
        "title-label",
        "collect-label",
        "collect-icon"
    );

    offset += 4;

    if(self->m_fields->m_isNew) {
        setIDSafe(this, offset, "new-label");
        offset += 1;
    }

    setIDs(
        this,
        offset,
        "progress-bar",
        "progress-label"
    );

    offset += 2;

    if(m_challengeItem->m_canClaim) {
        if(auto menu = setIDSafe(this, offset, "claim-menu")) {
            setIDs(
                menu,
                0,
                "claim-button"
            );
            offset += 1;
        }
    }

    // technically these get created in the if and else branches
    // but they get created in the same order, they just differ in sizes
    setIDs(
        this,
        offset,
        "reward-sprite",
        "reward-label"
    );

};