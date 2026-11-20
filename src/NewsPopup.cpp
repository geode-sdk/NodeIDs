#include <Geode/Geode.hpp>
#include <Geode/modify/NewsPopup.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(NewsPopup) {
    if (auto mainLayer = setIDSafe<CCLayer>(this, 0, "main-layer")) {
        setIDSafe<CCScale9Sprite>(mainLayer, 0, "background");
        setIDSafe<CCLabelBMFont>(mainLayer, 0, "title-label");
        setIDSafe<CCLabelBMFont>(mainLayer, 1, "page-label");
        setIDs(
            mainLayer,
            1,
            "bottom-left-corner",
            "top-left-corner",
            "top-right-corner",
            "bottom-right-corner"
        );

        if (auto controlMenu = setIDSafe<CCMenu>(mainLayer, 0, "control-menu")) {
            setIDs(
                controlMenu,
                0,
                "close-button",
                "prev-page-button",
                "next-page-button"
            );
        }
    }
}

struct NewsPopupIDs : Modify<NewsPopupIDs, NewsPopup> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("NewsPopup::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set NewsPopup::init hook priority, node IDs may not work properly");
        }
    }

    bool init() {
        if (!NewsPopup::init()) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};