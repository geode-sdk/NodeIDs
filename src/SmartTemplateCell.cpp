#include <Geode/Geode.hpp>
#include <Geode/modify/SmartTemplateCell.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(SmartTemplateCell) {
    setIDSafe<CCLayerColor>(this, 0, "background");

    if (auto smartTemplateBody = setIDSafe<CCLayer>(this, 1, "main-layer")) {

        setIDSafe<CCLabelBMFont>(smartTemplateBody, 0, "template-name");

        // I realized what I did too late...
        if (auto SmartCellMenu = setIDSafe<CCMenu>(smartTemplateBody, 0, "main-menu")) {
            setIDs(
                SmartCellMenu,
                0,
                "use-button",
                "edit-button"
            );
        };
    }
}

struct SmartTemplateCellIDs : Modify<SmartTemplateCellIDs, SmartTemplateCell> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("SmartTemplateCell::loadFromObject", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set SmartTemplateCell::loadFromObject hook priority, node IDs may not work properly");
        }
    }

    void loadFromObject(GJSmartTemplate* smartTemplate) {
        SmartTemplateCell::loadFromObject(smartTemplate);

        NodeIDs::get()->provide(this);
    }
};