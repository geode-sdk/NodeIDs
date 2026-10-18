#include <Geode/Bindings.hpp>
#include <Geode/modify/RewardsPage.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(RewardsPage) {
    setIDs(
        m_mainLayer,
        0,
        "background",
        "title-label",
        "bottom-left-art",
        "top-left-art",
        "top-right-art",
        "bottom-right-art",
        "main-menu",
        "left-label",
        "right-label"
    );

    if (auto menu = this->m_buttonMenu) {
        bool isFreeVisible = false;
        auto GSM = GameStatsManager::sharedState();

        std::array<std::string, 6> chests = {"0007", "0008", "0009", "0010", "0011", "0024"};
        for(auto& chest : chests) {
            if(!GSM->isSpecialChestUnlocked(chest)) {
                isFreeVisible = true;
                break;
            }
        }

        isFreeVisible ? setIDs(menu, 0, "close-button", "free-button", "right-chest", "left-chest") : setIDs(menu, 0, "close-button", "right-chest", "left-chest");
    }

    /**
     * Sanity checks
    */
    verifyIDSafe(m_leftLabel, "left-label");
    verifyIDSafe(m_rightLabel, "right-label");
    verifyIDSafe(m_leftChest, "left-chest");
    verifyIDSafe(m_rightChest, "right-chest");
}

struct RewardsPageIDs : Modify<RewardsPageIDs, RewardsPage> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("RewardsPage::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set RewardsPage::init hook priority, node IDs may not work properly");
        }
    }

    bool init() {
        if (!RewardsPage::init()) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};
