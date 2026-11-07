#include <Geode/Geode.hpp>
#include <Geode/modify/SetupSmartTemplateLayer.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(SetupSmartTemplateLayer) {
    if (auto smartTemplateBody = setIDSafe<CCLayer>(this, 0, "main-layer")) {
        int offset = 0;
        setIDSafe<CCScale9Sprite>(
            smartTemplateBody,
            offset,
            "background"
        );

        offset++;
        
        setIDSafe<CCScale9Sprite>(
            smartTemplateBody,
            offset,
            "name-input-background"
        );

        // offset += 2;

        setIDSafe<CCTextInputNode>(smartTemplateBody, 0, "name-input");
        // offset += 1;
        if (auto smartBlockMenu = setIDSafe<CCMenu>(smartTemplateBody, 0, "button-menu")) {
            setIDs(
                smartBlockMenu,
                0,
                "back-button",
                "info-button",
                "browse-button",
                "delete-button"
            );
        };
        // offset += 1;
        setIDSafe<CCLabelBMFont>(smartTemplateBody, 0, "template-status");
    }
}

struct SetupSmartTemplateLayerIDs : Modify<SetupSmartTemplateLayerIDs, SetupSmartTemplateLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("SetupSmartTemplateLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set SetupSmartTemplateLayer::init hook priority, node IDs may not work properly");
        }
    }

    bool init(GJSmartTemplate* smartTemplate) {
        if (!SetupSmartTemplateLayer::init(smartTemplate)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};