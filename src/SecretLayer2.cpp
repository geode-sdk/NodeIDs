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
        "the-challange-text1",
        "the-challange-text2" 
    );
    auto menu = static_cast<CCMenu*>(this->getChildByID("menu"));
     setIDs(
        menu,
        0,
        "back-button",
        "valtkeeper-button",
        "door-button",
        "the-challange-button"
    );
    auto textbox = this->getChildByID("text-box");
    setIDs(
        textbox,
        0,
        "input",
        "display-text",
        "bar-position"
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