// #include "AddIDs.hpp"

#include "Spacer.hpp"
#include <Geode/Bindings.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(EditorUI) {
    setIDSafe(this, 1, "background-sprite");
    setIDSafe(this, 3, "spacer-line-left");
    setIDSafe(this, 4, "spacer-line-right");

    auto winSize = CCDirector::get()->getWinSize();

    m_objectInfoLabel->setID("object-info-label");
    m_layerLockSprite->setID("layer-locked-sprite");
    m_zoomLabel->setID("zoom-label");

    m_positionSlider->setID("position-slider");
    m_positionSlider->setContentSize({m_positionSlider->m_groove->getScaledContentWidth() + m_positionSlider->m_touchLogic->m_thumb->getScaledContentWidth(), m_positionSlider->m_touchLogic->m_thumb->getScaledContentHeight()});
    m_positionSlider->ignoreAnchorPointForPosition(false);
    m_positionSlider->m_groove->setPosition(m_positionSlider->getContentSize() / 2.f);
    m_positionSlider->m_touchLogic->setContentSize({0.f, 0.f});
    m_positionSlider->m_touchLogic->setPosition(m_positionSlider->getContentSize() / 2.f);

    m_buildModeBtn->setID("build-button");
    m_editModeBtn->setID("edit-button");
    m_deleteModeBtn->setID("delete-button");
    m_viewModeBtn->setID("view-button");

    auto toolbarCategoriesMenu = detachAndCreateMenu(
        this,
        "toolbar-categories-menu",
        RowLayout::create()
            ->setGap(3.5f)
            ->setCrossAxisOverflow(false)
            ->setGrowCrossAxis(true)
            ->setAxisAlignment(AxisAlignment::Center)
            ->setCrossAxisAlignment(AxisAlignment::Center),
        m_buildModeBtn,
        m_editModeBtn,
        m_deleteModeBtn,
        m_viewModeBtn
    );

    toolbarCategoriesMenu->setAnchorPoint({0.f, 0.f});
    toolbarCategoriesMenu->setPosition(2.f GEODE_IOS(+ geode::utils::getSafeAreaRect().getMinX() / 2.f), 0.1f);
    toolbarCategoriesMenu->setContentSize({90.f, 90.f});
    toolbarCategoriesMenu->updateLayout();

    m_swipeBtn->setID("swipe-button");
    m_rotateBtn->setID("rotate-button");
    m_freeMoveBtn->setID("free-move-button");
    m_snapBtn->setID("snap-button");

    auto toolbarTogglesMenu = detachAndCreateMenu(
        this,
        "toolbar-toggles-menu",
        RowLayout::create()
            ->setGap(3.5f)
            ->setCrossAxisOverflow(false)
            ->setGrowCrossAxis(true)
            ->setAxisAlignment(AxisAlignment::Center)
            ->setCrossAxisAlignment(AxisAlignment::Center),
        m_swipeBtn,
        m_rotateBtn,
        m_freeMoveBtn,
        m_snapBtn
    );

    toolbarTogglesMenu->setAnchorPoint({1.f, 0.f});
    toolbarTogglesMenu->setPosition(
        winSize.width - 2.f GEODE_IOS(- geode::utils::getSafeAreaRect().getMinX() / 2.f),
        0.1f
    );
    toolbarTogglesMenu->setContentSize({90.f, 90.f});
    toolbarTogglesMenu->updateLayout();

    m_undoBtn->setID("undo-button");
    m_redoBtn->setID("redo-button");
    m_trashBtn->setID("delete-button");
    m_hideUIBtn->setID("hide-ui-button");

    float leftGap = 8.5f;

    auto undoMenu = detachAndCreateMenu(
        this,
        "undo-menu",
        SimpleRowLayout::create()
            ->setMainAxisScaling(AxisScaling::Fit)
            ->setCrossAxisScaling(AxisScaling::Fit)
            ->setMainAxisAlignment(MainAxisAlignment::Start)
            ->setGap(leftGap),
        m_undoBtn,
        m_redoBtn,
        m_trashBtn,
        m_hideUIBtn
    );

    undoMenu->setAnchorPoint({0.f, 1.f});
    undoMenu->setContentSize({winSize.width / 2.f - 120.f, 60.f});
    undoMenu->setPosition({6.f GEODE_IOS(+ geode::utils::getSafeAreaRect().getMinX() / 2.f), winSize.height});
    undoMenu->updateLayout();

    m_showUIMenu->setContentSize(undoMenu->getContentSize());
    m_showUIMenu->setPosition(undoMenu->getPosition());
    m_showUIMenu->setID("show-ui-menu");
    m_showUIMenu->setAnchorPoint({0.f, 1.f});
    m_showUIMenu->ignoreAnchorPointForPosition(false);

    setIDSafe(m_showUIMenu, 0, "show-ui-button");
    auto showUIBtn = m_showUIMenu->getChildByID("show-ui-button");

    if (showUIBtn) {
        showUIBtn->setPosition(m_hideUIBtn->getPosition());
    }

    m_playbackBtn->setID("music-playback-button");

    auto playBackMenu = detachAndCreateMenu(
        this,
        "playback-menu",
        SimpleRowLayout::create()
            ->setCrossAxisScaling(AxisScaling::Fit)
            ->setMainAxisAlignment(MainAxisAlignment::Start)
            ->setGap(leftGap),
        m_playbackBtn
    );
    playBackMenu->setContentSize({100.f, 50.f});
    playBackMenu->setAnchorPoint({0.f, 1.f});
    playBackMenu->setPosition({6.f GEODE_IOS(+ geode::utils::getSafeAreaRect().getMinX() / 2.f), undoMenu->boundingBox().getMinY() - 6.f});
    playBackMenu->updateLayout();

    m_playtestBtn->setID("playtest-button");
    m_playtestStopBtn->setID("stop-playtest-button");

    auto playTestMenu = detachAndCreateMenu(
        this,
        "playtest-menu",
        SimpleRowLayout::create()
            ->setGap(leftGap)
            ->setCrossAxisScaling(AxisScaling::Fit)
            ->setMainAxisAlignment(MainAxisAlignment::Start)
            ->ignoreInvisibleChildren(false),
        m_playtestBtn,
        m_playtestStopBtn
    );
    
    playTestMenu->setContentSize({100.f, 50.f});
    playTestMenu->setAnchorPoint({0.f, 1.f});
    playTestMenu->setPosition({playBackMenu->getPositionX(), playBackMenu->boundingBox().getMinY() - 5.5f});
    playTestMenu->updateLayout();

    m_enableLinkBtn->setID("enable-link-button");
    m_linkBtn->setID("link-button");
    m_unlinkBtn->setID("unlink-button");

    auto linkMenu = detachAndCreateMenu(
        this,
        "link-menu",
        SimpleColumnLayout::create()
            ->setGap(-1.f)
            ->setMainAxisAlignment(MainAxisAlignment::End)
            ->setCrossAxisScaling(AxisScaling::Fit)
            ->setMainAxisScaling(AxisScaling::Fit),
        m_enableLinkBtn,
        m_linkBtn,
        m_unlinkBtn
    );
    linkMenu->setContentSize({125.f, 77.f});
    linkMenu->setAnchorPoint({0.f, 0.5f});
    linkMenu->updateLayout();

    auto zoomMenu = this->getChildByType<CCMenu>(0);
    if (zoomMenu) {
        setIDs(
            zoomMenu,
            0,
            "zoom-out-button",
            "zoom-in-button"
        );

        zoomMenu->setLayout(SimpleColumnLayout::create()
            ->setGap(3.5f)
            ->setCrossAxisScaling(AxisScaling::Fit)
            ->setMainAxisAlignment(MainAxisAlignment::End)
        );

        zoomMenu->setID("zoom-menu");
        zoomMenu->setContentSize({50.f, 66.f});
        zoomMenu->setAnchorPoint({0.f, 1.f});
        zoomMenu->ignoreAnchorPointForPosition(false);
        zoomMenu->updateLayout();
        zoomMenu->setPosition({playBackMenu->getPositionX() + 19.f - zoomMenu->getContentWidth() / 2.f, playTestMenu->boundingBox().getMinY() - 9.5f});

        linkMenu->setPosition({zoomMenu->boundingBox().getMaxX() + 6.f, zoomMenu->boundingBox().getMidY()});
    }

    m_deleteMenu->setID("delete-category-menu");
    m_deleteMenu->setZOrder(3);
    m_deleteMenu->setContentSize({winSize.width, 90.f});
    m_deleteMenu->ignoreAnchorPointForPosition(false);
    m_deleteMenu->setAnchorPoint({0.5f, 0.f});
    m_deleteMenu->setPosition({winSize.width / 2.f, 0.f});
    m_deleteMenu->setLayout(SimpleRowLayout::create()
        ->setGap(15.f)
        ->setPadding({20.f, 4.f, 0.f, 9.f})
        ->setMainAxisScaling(AxisScaling::Fit)
        ->setCrossAxisScaling(AxisScaling::ScaleDown)
        ->setCrossAxisAlignment(CrossAxisAlignment::Start)
    );

    m_deleteButton->setID("delete-button");
    m_deleteAllButton->setID("delete-all-of-button");

    m_deleteMenu->addChild(Spacer::create({5.f, 80.f}, 3));

    auto deleteButtonMenu = detachAndCreateMenu(
        m_deleteMenu,
        "delete-button-menu",
        ColumnLayout::create()
            ->setGap(4.f)
            ->setCrossAxisOverflow(false)
            ->setGrowCrossAxis(true)
            ->setAxisReverse(true)
            ->setCrossAxisReverse(true)
            ->setAxisAlignment(AxisAlignment::End)
            ->setCrossAxisAlignment(AxisAlignment::Start)
            ->setDefaultScaleLimits(0.f, 0.94f),
        m_deleteMenu->getChildByID("delete-button"),
        m_deleteMenu->getChildByID("delete-all-of-button")
    );
    deleteButtonMenu->setZOrder(2);

    m_deleteFilterNone->setID("delete-filter-none");
    m_deleteFilterStatic->setID("delete-filter-static");
    m_deleteFilterDetails->setID("delete-filter-detail");
    m_deleteFilterCustom->setID("delete-filter-custom");

    auto deleteFilterMenu = detachAndCreateMenu(
        m_deleteMenu,
        "delete-filter-menu",
        ColumnLayout::create()
            ->setGap(4.f)
            ->setCrossAxisOverflow(false)
            ->setGrowCrossAxis(true)
            ->setAxisReverse(true)
            ->setCrossAxisReverse(true)
            ->setAxisAlignment(AxisAlignment::End)
            ->setCrossAxisAlignment(AxisAlignment::End)
            ->setDefaultScaleLimits(0.f, 0.94f),
        m_deleteFilterNone,
        m_deleteFilterStatic,
        m_deleteFilterDetails,
        m_deleteFilterCustom
    );
    deleteFilterMenu->setZOrder(4);

    setIDs(
        m_deleteMenu,
        0,
        "delete-startpos-button",

        "delete-help-icon",

        "delete-filter-group-id",
        "delete-filter-color",
        "delete-reset-search",
        "delete-find-group-id"
    );
    
    Ref deleteStartPosBtn = m_deleteMenu->getChildByID("delete-startpos-button");
    if (deleteStartPosBtn) {
        deleteStartPosBtn->removeFromParent();
        deleteButtonMenu->addChild(deleteStartPosBtn);
    }

    deleteButtonMenu->setPosition(-70.f, m_deleteMenu->getContentHeight() / 2.f);
    deleteButtonMenu->setContentSize({80.f, 80.f});
    deleteButtonMenu->updateLayout();

    Ref deleteFindGroupIDBtn = m_deleteMenu->getChildByID("delete-find-group-id");
    if (deleteFindGroupIDBtn) {
        deleteFindGroupIDBtn->removeFromParent();
        deleteFilterMenu->insertBefore(deleteFindGroupIDBtn, m_deleteFilterNone);
    }

    Ref deleteResetSearchBtn = m_deleteMenu->getChildByID("delete-reset-search");
    if (deleteResetSearchBtn) {
        deleteResetSearchBtn->removeFromParent();
        deleteFilterMenu->insertBefore(deleteResetSearchBtn, m_deleteFilterNone);
    }

    Ref deleteFilterColorBtn = m_deleteMenu->getChildByID("delete-filter-color");
    if (deleteFilterColorBtn) {
        deleteFilterColorBtn->removeFromParent();
        deleteFilterColorBtn->setLayoutOptions(
            AxisLayoutOptions::create()
                ->setRelativeScale(1.f / 0.9f)
        );
        deleteFilterMenu->insertBefore(deleteFilterColorBtn, m_deleteFilterNone);
    }

    Ref deleteFilterGroupIDBtn = m_deleteMenu->getChildByID("delete-filter-group-id");
    if (deleteFilterGroupIDBtn) {
        deleteFilterGroupIDBtn->removeFromParent();
        deleteFilterGroupIDBtn->setLayoutOptions(
            AxisLayoutOptions::create()
                ->setRelativeScale(1.f / 0.9f)
        );
        deleteFilterMenu->insertBefore(deleteFilterGroupIDBtn, m_deleteFilterNone);
    }

    auto helpBtn = m_deleteMenu->getChildByID("delete-help-icon");
    if (helpBtn) {
        helpBtn->setZOrder(5);
    }

    deleteFilterMenu->setPosition(60.f, m_deleteMenu->getContentHeight() / 2.f);
    deleteFilterMenu->setContentSize({166.f, 80.f});
    deleteFilterMenu->updateLayout();

    m_deleteMenu->updateLayout();

    m_layerPlusBtn->setID("next-free-layer-button");
    m_goToBaseBtn->setID("all-layers-button");
    m_layerNextBtn->setID("next-layer-button");
    m_layerPrevBtn->setID("prev-layer-button");

    m_currentLayerLabel->setID("layer-index-label");
    m_currentLayerLabel->setLayoutOptions(
        AxisLayoutOptions::create()
            ->setAutoScale(false)
            ->setLength(28.f)
    );

    auto layerMenu = detachAndCreateMenu(
        this,
        "layer-menu",
        RowLayout::create()
            ->setGap(7.f)
            ->setAxisAlignment(AxisAlignment::End),
            m_layerPlusBtn,
        m_goToBaseBtn,
        m_layerPrevBtn,
        m_currentLayerLabel,
        m_layerNextBtn
    );

    layerMenu->setPositionX(winSize.width - 110.f / 2.f - 6.f GEODE_IOS(- geode::utils::getSafeAreaRect().getMinX() / 2.f));
    layerMenu->setContentSize({110.f, 30.f});
    layerMenu->updateLayout();

    m_copyPasteBtn->setID("copy-paste-button");
    m_editObjectBtn->setID("edit-object-button");
    m_pasteColorBtn->setID("paste-color-button");
    m_deselectBtn->setID("deselect-button");

    m_pasteBtn->setID("paste-button");
    m_editGroupBtn->setID("edit-group-button");
    m_pasteStateBtn->setID("paste-state-button");
    m_goToLayerBtn->setID("go-to-layer-button");

    m_copyBtn->setID("copy-button");
    m_editSpecialBtn->setID("edit-special-button");
    m_copyValuesBtn->setID("copy-values-button");
    m_editHSVBtn->setID("hsv-button");

    auto editButtonsMenu = detachAndCreateMenu(
        this,
        "editor-buttons-menu",
        ColumnLayout::create()
            ->setAxisAlignment(AxisAlignment::End)
            ->setCrossAxisAlignment(AxisAlignment::End)
            ->setGap(0.85f)
            ->setGrowCrossAxis(true)
            ->setCrossAxisOverflow(false)
            ->setAxisReverse(true),
        m_copyPasteBtn,
        m_editObjectBtn,
        m_pasteColorBtn,
        m_deselectBtn,

        m_pasteBtn,
        m_editGroupBtn,
        m_pasteStateBtn,
        m_goToLayerBtn,

        m_copyBtn,
        m_editSpecialBtn,
        m_copyValuesBtn,
        m_editHSVBtn
    );

    for (auto btn : CCArrayExt<CCNode*>(editButtonsMenu->getChildren())) {
        btn->setContentWidth(37.f);
    }

    editButtonsMenu->setAnchorPoint({1.f, 1.f});
    editButtonsMenu->setContentSize({210.f, 140.f});
    editButtonsMenu->updateLayout();

    auto settingsMenu = m_playtestPauseBtn->getParent();
    if (settingsMenu) {
        settingsMenu->setID("lock-layer-menu");

        setIDs(
            settingsMenu,
            0,
            "pause-button",
            "settings-button",
            "edit-tools-button",
            "grid-controls-button",
            "lock-layer-button"
        );

        auto lockLayerMenu = detachAndCreateMenu(
            this,
            "lock-layer-menu",
            nullptr,
            settingsMenu->getChildByID("lock-layer-button")
        );
        lockLayerMenu->setContentSize(layerMenu->getContentSize());
        lockLayerMenu->setPosition(layerMenu->getPosition());
        
        auto lockLayerButton = lockLayerMenu->getChildByID("lock-layer-button");
        if (lockLayerButton) {
            lockLayerButton->setPosition(m_currentLayerLabel->getPosition());
        }

        settingsMenu->setID("settings-menu");
        settingsMenu->setLayout(SimpleRowLayout::create()
            ->setGap(8.f)
            ->setMainAxisScaling(AxisScaling::Fit)
            ->setCrossAxisScaling(AxisScaling::Fit)
            ->setMainAxisDirection(AxisDirection::RightToLeft)
            ->setMainAxisAlignment(MainAxisAlignment::End)
        );

        settingsMenu->setAnchorPoint({1.f, 1.f});
        settingsMenu->ignoreAnchorPointForPosition(false);
        settingsMenu->setContentSize({winSize.width / 2.f - 120.f, 60.f});
        settingsMenu->setPosition({winSize.width - 1.f GEODE_IOS(- geode::utils::getSafeAreaRect().getMinX() / 2.f), winSize.height - 0.5f});
        settingsMenu->updateLayout();
    }

    editButtonsMenu->setPosition(
        winSize.width - 4.f GEODE_IOS(- geode::utils::getSafeAreaRect().getMinX() / 2.f),
        settingsMenu->boundingBox().getMinY() - 3.f
    );

    std::array<std::string, 14> buttonBarNames = {
        "block",
        "outline",
        "slope",
        "hazard",
        "3d",
        "portal",
        "monster",
        "pixel",
        "collectible",
        "icon",
        "deco",
        "sawblade",
        "trigger",
        "custom"
    };

    for (auto tab : m_tabsArray->asExt<CCNode>()) {
        auto bar = m_createButtonBars->asExt<CCNode>()[tab->getTag()];
        ZStringView name = buttonBarNames[tab->getTag()];

        tab->setID(fmt::format("{}-tab", name));
        bar->setID(fmt::format("{}-tab-bar", name));

        bar->setContentSize({winSize.width, 90.f});
    }

    m_tabsMenu->setID("build-tabs-menu");
    m_tabsMenu->setPosition(winSize.width / 2.f, 91.f);
    m_tabsMenu->setAnchorPoint({0.5f, 0.f});
    m_tabsMenu->setContentSize({winSize.width, 50.f});
    m_tabsMenu->setLayout(
        SimpleRowLayout::create()
            ->setCrossAxisScaling(AxisScaling::Fit)
            ->setGap(2.f)
    );

    if (m_viewMenu) {
        m_viewMenu->setID("view-tab-bar");
        m_viewMenu->setContentSize({winSize.width, 90.f});

        auto bar = static_cast<EditButtonBar*>(m_viewMenu);

        std::unordered_map<int, std::string> viewButtonIDs = {
            {9, "preview-mode-toggle"},
            {11, "hitbox-toggle"},
            {10, "hide-invisible-toggle"},
            {20, "ldm-toggle"},
            {8, "animations-toggle"},
            {7, "particles-toggle"},
            {6, "shaders-toggle"},
            {5, "ground-toggle"},
            {4, "object-info-toggle"},
            {3, "grid-toggle"},
            {2, "select-filter-toggle"},
            {1, "ignore-damage-toggle"},
            {12, "effect-lines-toggle"},
            {13, "duration-lines-toggle"},
            {14, "song-lines-toggle"},
            {15, "bpm-lines-toggle"},
            {-16, "keyframe-lines-toggle"},
            {17, "local-markers-toggle"},
            {18, "global-markers-toggle"},
            {19, "marker-labels-toggle"},
            {21, "trace-in-toggle"},
            {22, "trace-out-toggle"}
        };

        for (auto node : bar->m_buttonArray->asExt<CCNode>()) {
            node->setID(viewButtonIDs[node->getTag()]);
        }
    }
}

struct EditorUIIDs : Modify<EditorUIIDs, EditorUI> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("EditorUI::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set EditorUI::init hook priority, node IDs may not work properly");
        }
        if (!self.setHookPriority("EditorUI::updateGroupIDLabel", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set EditorUI::updateGroupIDLabel hook priority, node IDs may not work properly");
        }
        if (!self.setHookPriority("EditorUI::createMoveMenu", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set EditorUI::createMoveMenu hook priority, node IDs may not work properly");
        }
    }

    bool init(LevelEditorLayer* lel) {
        if (!EditorUI::init(lel)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }

    void updateGroupIDLabel() {
        EditorUI::updateGroupIDLabel();
     
        auto menu = getChildByID("layer-menu");
        if (menu) {
            menu->updateLayout();
        }
    }

    // ensures that vanilla IDs stay sane if legacy is switched and a mod adds items somewhere between vanilla buttons
    void setupMoveIDs() {
        std::unordered_map<int, std::string> editButtonIDs = {
            {3, "move-up-small-button"},
            {4, "move-down-small-button"},
            {1, "move-left-small-button"},
            {2, "move-right-small-button"},
            {7, "move-up-button"},
            {8, "move-down-button"},
            {5, "move-left-button"},
            {6, "move-right-button"},
            {11, "move-up-big-button"},
            {12, "move-down-big-button"},
            {9, "move-left-big-button"},
            {10, "move-right-big-button"},
            {15, "move-up-tiny-button"},
            {16, "move-down-tiny-button"},
            {13, "move-left-tiny-button"},
            {14, "move-right-tiny-button"},
            {19, "move-up-half-button"},
            {20, "move-down-half-button"},
            {17, "move-left-half-button"},
            {18, "move-right-half-button"},
            {37, "flip-x-button"},
            {38, "flip-y-button"},
            {39, "rotate-cw-button"},
            {40, "rotate-ccw-button"},
            {41, "rotate-cw-45-button"},
            {42, "rotate-ccw-45-button"},
            {43, "rotate-free-button"},
            {44, "rotate-snap-button"},
            {45, "scale-button"},
            {46, "scale-xy-button"},
            {47, "warp-button"},
        };

        auto winSize = CCDirector::get()->getWinSize();

        if (m_dpadMoveNode) {
            m_dpadMoveNode->setID("dpad-move-node");
            m_dpadMoveNode->setContentSize({winSize.width, 90.f});

            setIDSafe(m_dpadMoveNode, 0, "spacer-line-center-left");
            setIDSafe(m_dpadMoveNode, 1, "spacer-line-center-right");
            setIDSafe(m_dpadMoveNode, 2, "dpad-menu");

            m_dpadLabel->setID("move-increment-label");

            std::unordered_map<int, std::string> dpadArrows = {
                {5, "move-left-button"},
                {6, "move-right-button"},
                {7, "move-up-button"},
                {8, "move-down-button"}
            };

            for (auto node : m_dpadArrowButtons->asExt<CCNode>()) {
                node->setID(dpadArrows[node->getTag()]);
            }

            auto spacerCenterLeft = m_dpadMoveNode->getChildByID("spacer-line-center-left");
            auto spacerCenterRight = m_dpadMoveNode->getChildByID("spacer-line-center-right");

            auto availableStepSpace = spacerCenterRight->boundingBox().getMinX() - spacerCenterLeft->boundingBox().getMaxX();

            std::unordered_map<int, std::string> dpadSteps = {
                {0, "step-5-button"},
                {1, "step-1-button"},
                {2, "step-custom-button"},
                {3, "step-half-button"},
                {4, "step-quarter-button"},
                {5, "step-eighth-button"},
                {6, "step-2-small-button"},
                {7, "step-half-small-button"},
                {8, "step-tenth-small-button"}
            };

            for (auto node : m_dpadStepButtons->asExt<CCNode>()) {
                node->setID(dpadSteps[node->getTag()]);
            }

            auto menu = m_dpadMoveNode->getChildByType<CCMenu>(1);
            if (menu) {
                menu->setID("edit-buttons");

                auto dpadStepsMenu = detachAndCreateMenu(
                    m_dpadMoveNode,
                    "dpad-steps-menu",
                    nullptr,
                    menu->getChildByID("step-5-button"),
                    menu->getChildByID("step-1-button"),
                    menu->getChildByID("step-custom-button"),
                    menu->getChildByID("step-half-button"),
                    menu->getChildByID("step-quarter-button"),
                    menu->getChildByID("step-eighth-button"),
                    menu->getChildByID("step-2-small-button"),
                    menu->getChildByID("step-half-small-button"),
                    menu->getChildByID("step-tenth-small-button")
                );

                // RowLayouts are dumb and scale gaps weird if I handle it with auto scale normally, so I extract the old widths, update, then extract again and set the new widths
                auto getMaxWidth = [] (CCNode* node) -> float {
                    float minX = FLT_MAX;
                    float maxX = -FLT_MAX;
                    
                    for (auto child : node->getChildrenExt()) {
                        if (child->boundingBox().getMaxX() > maxX) {
                            maxX = child->boundingBox().getMaxX();
                        }
                        if (child->boundingBox().getMinX() < minX) {
                            minX = child->boundingBox().getMinX();
                        }
                    }

                    return maxX - minX;
                };

                dpadStepsMenu->setContentSize({getMaxWidth(dpadStepsMenu), 90.f});
                dpadStepsMenu->setLayout(RowLayout::create()
                    ->setGap(4.f)
                    ->setAutoScale(false)
                    ->setCrossAxisOverflow(false)
                    ->setGrowCrossAxis(true)
                    ->setAxisAlignment(AxisAlignment::Start)
                    ->setCrossAxisAlignment(AxisAlignment::Center)
                );
                dpadStepsMenu->updateLayout();

                dpadStepsMenu->setContentSize({getMaxWidth(dpadStepsMenu), 90.f});
                dpadStepsMenu->setPosition({spacerCenterLeft->boundingBox().getMaxX() + availableStepSpace / 2.f, 46.f});

                for (auto node : menu->getChildrenExt()) {
                    node->setID(editButtonIDs[node->getTag()]);
                }

                auto availableEditSpace = winSize.width - 96.75f GEODE_IOS(- geode::utils::getSafeAreaRect().getMinX() / 2.f) - spacerCenterRight->boundingBox().getMaxX() * m_dpadMoveNode->getScale();

                menu->setContentSize({getMaxWidth(menu), 90.f});
                menu->setLayout(RowLayout::create()
                    ->setGap(4.f)
                    ->setAutoScale(false)
                    ->setCrossAxisOverflow(false)
                    ->setGrowCrossAxis(true)
                    ->setAxisAlignment(AxisAlignment::Start)
                    ->setCrossAxisAlignment(AxisAlignment::Center)
                );
                menu->updateLayout();

                menu->setContentSize({getMaxWidth(menu), 90.f});
                menu->setPosition({spacerCenterRight->boundingBox().getMaxX() + availableEditSpace / 2.f, 46.f});
            }
        }
        else if (m_editButtonBar) {
            m_editButtonBar->setID("edit-tab-bar");
            m_editButtonBar->setContentSize({winSize.width, 90.f});
            
            for (auto node : m_editButtonBar->m_buttonArray->asExt<CCNode>()) {
                node->setID(editButtonIDs[node->getTag()]);
            }
        }
    }

    void createMoveMenu() {
        EditorUI::createMoveMenu();
        setupMoveIDs();
    }
};
