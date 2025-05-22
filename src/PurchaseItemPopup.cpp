#include <Geode/Bindings.hpp>
#include <Geode/modify/PurchaseItemPopup.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(PurchaseItemPopup) {
    if(auto layer = setIDSafe(this, 0, "main-layer")) {
        setIDs(
            layer,
            0,
            "background",
            "title",
            "icon",
            "info-area",
            "button-menu"
        );

        if(auto buttonMenu = layer->getChildByID("button-menu")) {
            setIDs(
                buttonMenu,
                0,
                "cancel-button",
                "buy-button"
            );
        }
    }
}

struct PurchaseItemPopupIDs : Modify<PurchaseItemPopupIDs, PurchaseItemPopup> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("PurchaseItemPopup::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set PurchaseItemPopup::init hook priority, node IDs may not work properly");
        }
    }

    bool init(GJStoreItem* p0) {
        if (!PurchaseItemPopup::init(p0)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};
