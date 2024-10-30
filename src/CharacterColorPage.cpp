#include <Geode/Geode.hpp>
#include <Geode/Bindings.hpp>
#include <Geode/modify/CharacterColorPage.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(CharacterColorPage) {
    size_t offset = 0;

    auto colorsLayer = static_cast<CCLayer*>(this->getChildren()->objectAtIndex(0));
    colorsLayer->setID("colors-layer");

    setIDSafe(colorsLayer, offset++, "background");
    if (auto menu = colorsLayer->getChildByType<CCMenu>(0)) {
        menu->setID("buttons-menu");
        setIDs(
            menu,
            0,
            "close-button",
            "ship-button",
            "col1-button",
            "col2-button",
            "glow-button"
        );

        for (int i = 5; i < menu->getChildrenCount()-1; i++) {
            auto child = as<CCMenuItemSpriteExtra*>(menu->getChildren()->objectAtIndex(i));
            child->setID(std::to_string(child->getTag()));
        }

        setIDSafe(menu, menu->getChildrenCount()-1, "glow-toggler");
    }

    offset++;
    setIDs(
        colorsLayer,
        offset,
        "icon-background",
        "cube-icon",
        "ball-icon",
        "ufo-icon",
        "wave-icon",
        "robot-icon",
        "spider-icon",
        "swing-icon",
        "cursor-col1",
        "cursor-col2",
        "cursor-glow",
        "glow-label"
    );
}

struct CharacterColorPageIDS : Modify<CharacterColorPageIDS, CharacterColorPage> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("CharacterColorPage::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set CharacterColorPage::init hook priority, node IDs may not work properly");
        }
    }

    bool init() {
        if (!CharacterColorPage::init()) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};
