#include <Geode/Bindings.hpp>
#include <Geode/modify/SecretLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(SecretLayer) {
    setIDs(
        this,
        0,
        "background",
        "vault-name",
        "message",
        "textbox-background",
        "text-box",
        "menu"
    );
    auto menu = static_cast<CCMenu*>(this->getChildByID("menu"));
     setIDs(
        menu,
        0,
        "back-button",
        "vaultkeeper-button"
    );
}

struct SecretLayerIDs : Modify<SecretLayerIDs, SecretLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("SecretLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set SecretLayer::init hook priority, node IDs may not work properly");
        }
    }

    bool init() {
        if(!SecretLayer::init()) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};