#include <Geode/Geode.hpp>
#include <Geode/modify/DailyRecallUnlockPopup.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(DailyRecallUnlockPopup) {
    m_mainLayer->setID("main-layer");
    m_buttonMenu->setID("main-menu");

    setIDs(m_mainLayer, 0,
        "background",
        "crown-sprite",
        "unlock-label",
        "key-count-label",
        "key-sprite",
        "prompt-area",
        "prompt-shadow-area",
        "daily-level-number-label"
    );

    setIDs(m_buttonMenu, 0,
        "cancel-button",
        "unlock-button",
        "info-button"
    );
}

struct DailyRecallUnlockPopupIDs : Modify<DailyRecallUnlockPopupIDs, DailyRecallUnlockPopup> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("DailyRecallUnlockPopup::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set DailyRecallUnlockPopup::init hook priority, node IDs may not work properly");
        }
    }

    bool init(FLAlertLayerProtocol* protocol, GJGameLevel* level) {
        if (!DailyRecallUnlockPopup::init(protocol, level)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};