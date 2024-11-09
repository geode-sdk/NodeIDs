#include <Geode/Bindings.hpp>
#include <Geode/modify/SecretLayer4.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(SecretLayer4) {
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

struct SecretLayer4IDs : Modify<SecretLayer4IDs, SecretLayer4> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("SecretLayer4::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set SecretLayer4::init hook priority, node IDs may not work properly");
        }
    }

    bool init() {
        if(!SecretLayer4::init()) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};