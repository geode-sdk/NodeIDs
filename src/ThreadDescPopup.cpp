#include <Geode/Geode.hpp>

#if GEODE_COMP_GD_VERSION >= 22090

#include <Geode/modify/ThreadDescPopup.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(ThreadDescPopup) {
    m_mainLayer->setID("main-layer");

    setIDs(
        m_mainLayer,
        0,
        "background",
        "main-menu",
        "title-label"
    );
    setIDSafe(m_buttonMenu, 0, "close-button");

    if (m_buttonMenu->getChildrenCount() > 1) {
        setIDs(
            m_mainLayer,
            3,
            "description-bg",
            "description-input",
            "icon-label"
        );

        setIDs(
            m_buttonMenu,
            1,
            "save-button",
            "icon-button",
            "emote-button"
        );
        // this file is pretty lazy ngl
    }
    else {
        setIDSafe(m_mainLayer, 3, "description-area");
    }

    verifyIDSafe(m_buttonMenu, "main-menu");
}

struct ThreadDescPopupIDs : Modify<ThreadDescPopupIDs, ThreadDescPopup> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("ThreadDescPopup::buildUI", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set ThreadDescPopup::buildUI hook priority, node IDs may not work properly");
        }
    }

    bool buildUI(bool editable, std::string const& description, std::string const& icon) {
        if (!ThreadDescPopup::buildUI(editable, description, icon)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};

#endif
