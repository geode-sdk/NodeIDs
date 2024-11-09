#include <Geode/Bindings.hpp>
#include <Geode/modify/ItemInfoPopup.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(ItemInfoPopup) {
    m_mainLayer->setID("main-layer");
    m_buttonMenu->setID("button-menu");

    setIDSafe<CCScale9Sprite>(m_mainLayer, 0, "background");
    setIDSafe<CCScale9Sprite>(m_mainLayer, 1, "description-bg");

    setIDSafe<CCLabelBMFont>(m_mainLayer, 0, "name-label");
    auto AM = AchievementManager::sharedState();
    auto achievement = AM->achievementForUnlock(m_itemID, m_unlockType);
    if (!achievement.empty()) {
        if (AM->limitForAchievement(achievement) > 1) setIDSafe<CCSprite>(m_mainLayer, 0, "spinoff-logo");
    }

    auto labelOffset = 1;
    auto GM = GameManager::sharedState();
    auto GSM = GameStatsManager::sharedState();
    auto unlockState = GSM->getItemUnlockState(m_itemID, m_unlockType);
    if ((unlockState == 2 || unlockState == 3) &&
        GSM->getSpecialUnlockDescription(m_itemID, m_unlockType, GM->isIconUnlocked(m_itemID, GM->unlockTypeToIconType((int)m_unlockType))).empty()) {
        setIDSafe<CCLabelBMFont>(m_mainLayer, labelOffset++, "random-label");
    }

    setIDSafe<GJItemIcon>(m_mainLayer, 0, "item-icon");
    setIDSafe<CCMenuItemSpriteExtra>(m_buttonMenu, 0, "ok-button");
    if (GSM->m_accountIDForIcon.contains({ m_itemID, m_unlockType }) && GSM->m_usernameForAccountID.contains(GSM->m_accountIDForIcon[{ m_itemID, m_unlockType }])) {
        setIDSafe<CCMenuItemSpriteExtra>(m_buttonMenu, 1, "author-button");
    }

    setIDSafe<CCMenuItemSpriteExtra>(m_buttonMenu, 1, "author-button");
    setIDSafe<TextArea>(m_mainLayer, 0, "description-area");
    setIDSafe<CCLabelBMFont>(m_mainLayer, labelOffset, "achievement-label");
}

struct ItemInfoPopupIDs : Modify<ItemInfoPopupIDs, ItemInfoPopup> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("ItemInfoPopup::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set ItemInfoPopup::init hook priority, node IDs may not work properly");
        }
    }

    bool init(int id, UnlockType type) {
        if (!ItemInfoPopup::init(id, type)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};
