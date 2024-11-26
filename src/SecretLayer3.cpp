#include <Geode/Bindings.hpp>
#include <Geode/modify/SecretLayer3.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(SecretLayer3) {
    setIDs(
        this,
        0,
        "background",
        "cave", 
        "rocks", 
        "fire-outline", 
        "fire",
        "light-1",
        "torch-holder",
        "light-2",
        "bars-base",
        "bars",
        "eyes",
        "monster",
        "keys-menu",
        "chest-menu",
        "back-menu"
    );
}

struct SecretLayer3IDs : Modify<SecretLayer3IDs, SecretLayer3> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("SecretLayer3::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set SecretLayer3::init hook priority, node IDs may not work properly");
        }
    }

    bool init() {
        if(!SecretLayer3::init()) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};