// #include "AddIDs.hpp"

#include <Geode/Bindings.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(EditorUI) {
    setIDSafe(this, 0, "position-slider");
    setIDSafe(this, this->getChildrenCount() - 3, "layer-index-label");
    setIDSafe(this, this->getChildrenCount() - 2, "layer-locked-sprite");
    setIDSafe(this, this->getChildrenCount() - 1, "object-info-label");

    auto winSize = CCDirector::get()->getWinSize();

    if (auto menu = getChildOfType<CCMenu>(this, 0)) {
        menu->setID("toolbar-categories-menu");

        setIDs(
            menu,
            0,
            "build-button",
            "edit-button",
            "delete-button",

            "swipe-button",
            "free-move-button",
            "snap-button",
            "rotate-button",

            "undo-button",
            "redo-button",
            "delete-trash-button",

            "music-playback-button",

            "playtest-button",
            "stop-playtest-button",

            "zoom-in-button",
            "zoom-out-button",

            "link-button",
            "unlink-button"
        );

        auto toolbarTogglesMenu = detachAndCreateMenu(
            this,
            "toolbar-toggles-menu",
            RowLayout::create()
                ->setGap(3.5f)
                ->setCrossAxisOverflow(false)
                ->setGrowCrossAxis(true)
                ->setAxisAlignment(AxisAlignment::Center)
                ->setCrossAxisAlignment(AxisAlignment::Center),
            menu->getChildByID("swipe-button"),
            menu->getChildByID("rotate-button"),
            menu->getChildByID("free-move-button"),
            menu->getChildByID("snap-button")
        );
        toolbarTogglesMenu->setPosition(
            winSize.width - 47.f,
            45.f
        );
        toolbarTogglesMenu->setContentSize({ 90.f, 90.f });
        toolbarTogglesMenu->updateLayout();

        auto undoMenuWidth = winSize.width / 2 - 90.f;
        auto undoMenu = detachAndCreateMenu(
            this,
            "undo-menu",
            RowLayout::create()
                ->setAxisAlignment(AxisAlignment::Start)
                ->setGap(10.f),
            menu->getChildByID("undo-button"),
            menu->getChildByID("redo-button"),
            menu->getChildByID("delete-trash-button")
        );
        undoMenu->setContentSize({ undoMenuWidth, 50.f });
        undoMenu->setPositionX(
            undoMenu->getPositionX() + undoMenuWidth / 2 - 
                getSizeSafe(undoMenu->getChildByID("undo-button")).width / 2
        );
        undoMenu->updateLayout();

        auto playBackMenu = detachAndCreateMenu(
            this,
            "playback-menu",
            RowLayout::create()
                ->setAxisAlignment(AxisAlignment::Start),
            menu->getChildByID("music-playback-button")
        );
        playBackMenu->setContentSize({ 100.f, 50.f });
        playBackMenu->setPositionX(
            playBackMenu->getPositionX() + 100.f / 2 - 
                getSizeSafe(playBackMenu->getChildByID("music-playback-button")).width / 2
        );
        playBackMenu->updateLayout();

        auto playTestMenu = detachAndCreateMenu(
            this,
            "playtest-menu",
            RowLayout::create()
                ->setAxisAlignment(AxisAlignment::Start),
            menu->getChildByID("playtest-button"),
            menu->getChildByID("stop-playtest-button")
        );
        playTestMenu->setContentSize({ 100.f, 50.f });
        playTestMenu->setPositionX(
            playTestMenu->getPositionX() + 100.f / 2 - 
                getSizeSafe(playTestMenu->getChildByID("playtest-button")).width / 2
        );
        playTestMenu->updateLayout();

        auto zoomMenuHeight = winSize.height - 245.f;
        auto zoomMenu = detachAndCreateMenu(
            this,
            "zoom-menu",
            ColumnLayout::create()
                ->setGap(3.f)
                ->setAxisAlignment(AxisAlignment::End),
            menu->getChildByID("zoom-out-button"),
            menu->getChildByID("zoom-in-button")
        );
        zoomMenu->setContentSize({ 50.f, zoomMenuHeight });
        zoomMenu->setPositionY(playTestMenu->getPositionY() - 30 - (zoomMenu->getContentHeight() / 2));
        zoomMenu->updateLayout();

        auto linkMenu = detachAndCreateMenu(
            this,
            "link-menu",
            ColumnLayout::create()
                ->setGap(3.f)
                ->setAxisAlignment(AxisAlignment::End)
                ->setGrowCrossAxis(true),
            menu->getChildByID("unlink-button"),
            menu->getChildByID("link-button")
        );
        linkMenu->setContentSize({ 125.f, zoomMenuHeight });
        linkMenu->setPositionY(playTestMenu->getPositionY() - 30 - (linkMenu->getContentHeight() / 2));
        linkMenu->updateLayout();

        menu->setPosition(42.f, 45.f);
        menu->setContentSize({ 100.f, 90.f });
        menu->setLayout(
            ColumnLayout::create()
                ->setGap(4.f)
                ->setAxisReverse(true)
        );
    }

    if (auto menu = getChildOfType<CCMenu>(this, 1)) {
        menu->setID("delete-category-menu");

        setIDs(
            menu,
            0,
            "delete-button",
            "delete-startpos-button",
            "delete-all-of-button",

            "delete-filter-none",
            "delete-filter-static",
            "delete-filter-detail",
            "delete-filter-custom",

            "delete-help-icon",

            "delete-filter-group-id",
            "delete-filter-color",
            "delete-reset-search",
            "delete-find-group-id"
        );

        auto deleteButtonMenu = detachAndCreateMenu(
            menu,
            "delete-button-menu",
            ColumnLayout::create()
                ->setCrossAxisOverflow(false)
                ->setGrowCrossAxis(true)
                ->setAxisReverse(true)
                ->setCrossAxisReverse(true)
                ->setAxisAlignment(AxisAlignment::End)
                ->setCrossAxisAlignment(AxisAlignment::Start),
            menu->getChildByID("delete-button"),
            menu->getChildByID("delete-all-of-button"),
            menu->getChildByID("delete-startpos-button")
        );
        deleteButtonMenu->setPosition(-70.f, 0.f);
        deleteButtonMenu->setContentSize({ winSize.width / 2 - 120.f, 80.f });
        deleteButtonMenu->updateLayout();
    	
        auto deleteFilterMenu = detachAndCreateMenu(
            menu,
            "delete-filter-menu",
            ColumnLayout::create()
                ->setCrossAxisOverflow(false)
                ->setGrowCrossAxis(true)
                ->setAxisReverse(true)
                ->setCrossAxisReverse(true)
                ->setAxisAlignment(AxisAlignment::Even)
                ->setCrossAxisAlignment(AxisAlignment::Start),
            menu->getChildByID("delete-find-group-id"),
            menu->getChildByID("delete-reset-search"),
            menu->getChildByID("delete-filter-group-id"),
            menu->getChildByID("delete-filter-color"),
            menu->getChildByID("delete-filter-none"),
            menu->getChildByID("delete-filter-static"),
            menu->getChildByID("delete-filter-detail"),
            menu->getChildByID("delete-filter-custom")
        );
        deleteFilterMenu->setPosition(60.f, 0.f);
        deleteFilterMenu->setContentSize({ 170.f, 80.f });
        deleteFilterMenu->updateLayout();
    }

    auto buttonBarIDs = {
        "block-tab-bar",
        "outline-tab-bar",
        "slope-tab-bar",
        "hazard-tab-bar",
        "3d-tab-bar",
        "portal-tab-bar",
        "monster-tab-bar",
        "pixel-tab-bar",
        "collectible-tab-bar",
        "icon-tab-bar",
        "deco-tab-bar",
        "sawblade-tab-bar",
        "trigger-tab-bar",
        "custom-tab-bar",
        "edit-tab-bar",
    };

    size_t buttonBarIndex = 0;
    for (auto id : buttonBarIDs) {
        if (auto bar = getChildOfType<EditButtonBar>(this, buttonBarIndex++)) {
            bar->setID(id);
        }
        else break;
    }

    if (auto editBar = static_cast<EditButtonBar*>(this->getChildByID("edit-tab-bar"))) {
        auto editButtonIDs = {
            "move-up-small-button",
            "move-down-small-button",
            "move-left-small-button",
            "move-right-small-button",
            "move-up-button",
            "move-down-button",
            "move-left-button",
            "move-right-button",
            "move-up-big-button",
            "move-down-big-button",
            "move-left-big-button",
            "move-right-big-button",
            "move-up-tiny-button",
            "move-down-tiny-button",
            "move-left-tiny-button",
            "move-right-tiny-button",
            "move-up-half-button",
            "move-down-half-button",
            "move-left-half-button",
            "move-right-half-button",
            "flip-x-button",
            "flip-y-button",
            "rotate-cw-button",
            "rotate-ccw-button",
            "rotate-cw-45-button",
            "rotate-ccw-45-button",
            "rotate-free-button",
            "rotate-snap-button",
            "scale-button",
            "scale-xy-button",
            "warp-button",
        };
        size_t i = 0;
        for (auto id : editButtonIDs) {
            if (i < editBar->m_buttonArray->count()) {
                static_cast<CCNode*>(editBar->m_buttonArray->objectAtIndex(i++))->setID(id);
            }
        }
    }

    if (auto menu = getChildOfType<CCMenu>(this, 2)) {
        menu->setID("build-tabs-menu");

        // todo: maybe form these from buttonBarIDs to avoid duplication?
        setIDs(
            menu,
            0,
            "block-tab",
            "outline-tab",
            "slope-tab",
            "hazard-tab",
            "3d-tab",
            "portal-tab",
            "monster-tab",
            "pixel-tab",
            "collectible-tab",
            "icon-tab",
            "deco-tab",
            "sawblade-tab",
            "trigger-tab",
            "custom-tab"
        );

        menu->setPosition(winSize.width / 2 - 5.f, 100.f);
        menu->setContentSize({ winSize.width, 50.f });
        menu->setLayout(
            RowLayout::create()
                ->setGap(2.f)
                ->setCrossAxisLineAlignment(AxisAlignment::Start)
        );
    }

    if (auto menu = getChildOfType<CCMenu>(this, 3)) {
        setIDs(
            menu,
            0,
            "pause-button",
            "settings-button",
            "copy-paste-button",
            "copy-button",
            "paste-button",
            "hsv-button",
            "edit-special-button",
            "edit-object-button",
            "deselect-button",
            "edit-group-button",
            "copy-values-button",
            "paste-state-button",
            "paste-color-button",
            "go-to-layer-button",
            "next-layer-button",
            "prev-layer-button",
            "all-layers-button",
            "lock-layer-button"
        );

        auto topRightMenuWidth = winSize.width / 2 - 140.f;
        auto topRightMenu = detachAndCreateMenu(
            this,
            "settings-menu",
            RowLayout::create()
                ->setAxisReverse(true)
                ->setAxisAlignment(AxisAlignment::End),
            menu->getChildByID("pause-button"),
            menu->getChildByID("settings-button")
        );
        topRightMenu->setContentSize({ topRightMenuWidth, 60.f });
        topRightMenu->setPositionX(
            topRightMenu->getPositionX() - topRightMenuWidth / 2 + 
                getSizeSafe(topRightMenu->getChildByID("pause-button")).width / 2
        );
        topRightMenu->updateLayout();

        auto rightMenu = detachAndCreateMenu(
            this,
            "editor-buttons-menu",
            ColumnLayout::create()
                ->setAxisAlignment(AxisAlignment::End)
                ->setCrossAxisAlignment(AxisAlignment::End)
                ->setGap(-4.5f)
                ->setGrowCrossAxis(true)
                ->setCrossAxisOverflow(false)
                ->setAxisReverse(true),
            menu->getChildByID("copy-paste-button"),
            menu->getChildByID("edit-object-button"),
            menu->getChildByID("paste-color-button"),
            menu->getChildByID("deselect-button"),
            menu->getChildByID("paste-button"),
            menu->getChildByID("edit-group-button"),
            menu->getChildByID("paste-state-button"),
            menu->getChildByID("go-to-layer-button"),
            menu->getChildByID("copy-button"),
            menu->getChildByID("edit-special-button"),
            menu->getChildByID("copy-values-button"),
            menu->getChildByID("hsv-button")
        );
        for (auto btn : CCArrayExt<CCNode*>(rightMenu->getChildren())) {
            btn->setContentSize({ 40.f, 40.f });
        }
        rightMenu->setContentSize({ 210.f, 160.f });
        rightMenu->setPosition(
            winSize.width - 210.f / 2,
            winSize.height - 117.5f
        );
        rightMenu->updateLayout();

        this->getChildByID("layer-index-label")->setLayoutOptions(
            AxisLayoutOptions::create()
                ->setAutoScale(false)
                ->setLength(25.f)
        );

        auto layerMenu = detachAndCreateMenu(
            this,
            "layer-menu",
            RowLayout::create()
                ->setAxisAlignment(AxisAlignment::End),
            menu->getChildByID("all-layers-button"),
            menu->getChildByID("prev-layer-button"),
            this->getChildByID("layer-index-label"),
            menu->getChildByID("next-layer-button")
        );
        layerMenu->setPositionX(winSize.width - 110.f / 2 - 6.f);
        layerMenu->setContentSize({ 110.f, 30.f });
        layerMenu->updateLayout();
    }
}

struct EditorUIIDs : Modify<EditorUIIDs, EditorUI> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("EditorUI::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set EditorUI::init hook priority, node IDs may not work properly");
        }
    }

    bool init(LevelEditorLayer* lel) {
        if (!EditorUI::init(lel)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};
