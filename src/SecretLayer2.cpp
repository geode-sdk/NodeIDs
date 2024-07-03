#include <Geode/Bindings.hpp>
#include <Geode/modify/SecretLayer2.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(SecretLayer2) {
    setIDs(
        this,
        0,
        "background",
        "vault-name", 
        "message", 
        "textbox-background", 
        "text-box",
        "menu",
        "the-challenge-text1",
        "the-challenge-text2",
        "diamonds-icon",
        "diamonds-label"
    );
    auto menu = static_cast<CCMenu*>(this->getChildByID("menu"));
     setIDs(
        menu,
        0,
        "back-button",
        "valtkeeper-button",
        "door-button",
        "the-challenge-button"
    );
}

struct SecretLayer2IDs : Modify<SecretLayer2IDs, SecretLayer2> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("SecretLayer2::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set SecretLayer2::init hook priority, node IDs may not work properly");
        }
    }

    bool init() {
        if(!SecretLayer2::init()) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};