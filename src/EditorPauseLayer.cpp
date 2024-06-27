#include <Geode/Geode.hpp>
#include <Geode/utils/NodeIDs.hpp>
#include <Geode/modify/EditorPauseLayer.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

// special class for this because making it a CCMenuItemToggler would be very UB 
// (not gonna reinterpret_cast that into the members)
class GuidelinesButtonDummy {

public:
    void onClick(CCObject* sender) {
        GameManager::get()->m_showSongMarkers ^= 1;
        CCMenuItemSpriteExtra* btn = typeinfo_cast<CCMenuItemSpriteExtra*>(sender);

        btn->setNormalImage(CCSprite::createWithSpriteFrameName(
            GameManager::get()->m_showSongMarkers ? 
                "GJ_audioOnBtn_001.png" :
                "GJ_audioOffBtn_001.png"
        ));
    }
};

$register_ids(EditorPauseLayer) {
    auto winSize = CCDirector::get()->getWinSize();

    if (auto menu = getChildOfType<CCMenu>(this, 0)) {
        menu->setID("resume-menu");

        setIDs(
            menu, 0,
            "resume-button",
            "save-and-play-button",
            "save-and-exit-button",
            "save-button",
            "exit-button"
        );

        menu->setContentSize({ 100.f, 220.f });
        menu->setLayout(
            ColumnLayout::create()
                ->setGap(12.5f)
                ->setAxisReverse(true)
        );
    }

    setIDs(
        this, 2,
        "ignore-damage-label",
        "select-filter-label",
        "show-grid-label",
        "show-object-info-label",
        "show-ground-label",
        "preview-shaders-label",
        "preview-particles-label",
        "preview-animations-label",
        "preview-mode-label",
        "hide-invisible-label",
        "show-hitboxes-label",

        "object-count-label",
        "length-label",
        "length-name-label"
    );

    if (auto menu = getChildOfType<CCMenu>(this, 1)) {
        menu->setID("bottom-menu");

        int idx = 0;

        setIDs(
            menu, idx, 
            "guidelines-enable-button",
            "help-button",
            "guidelines-disable-button",

            "uncheck-portals-button",
            "reset-unused-button",
            "unlock-layers-button",
            "create-extras-button",
            "paste-color-button",
            "copy-color-button",
            "build-helper-button",

            "regroup-button",
            "create-loop-button",
            "align-x-button",
            "align-y-button",
            "select-all-button",
            "select-all-left-button",
            "select-all-right-button",
            "new-groupx-button",
            "new-groupy-button",

            "ignore-damage-toggle",
            "select-filter-toggle",
            "show-grid-toggle",
            "show-object-info-toggle",
            "show-ground-toggle",
            "preview-shaders-toggle",
            "preview-particles-toggle",
            "preview-animations-toggle",
            "preview-mode-toggle",
            "hide-invisible-toggle",
            "show-hitboxes-toggle",

        #ifdef GEODE_IS_DESKTOP
            "keys-button",
        #endif
            "settings-button"
        );

        auto smallActionsMenu = detachAndCreateMenu(
            this,
            "small-actions-menu",
            ColumnLayout::create()
                ->setAxisAlignment(AxisAlignment::Start)
                ->setAxisReverse(true),
            menu->getChildByID("regroup-button"),
            menu->getChildByID("create-loop-button"),
            menu->getChildByID("align-x-button"),
            menu->getChildByID("align-y-button"),
            menu->getChildByID("select-all-button"),
            menu->getChildByID("select-all-left-button"),
            menu->getChildByID("select-all-right-button"),
            menu->getChildByID("new-groupx-button"),
            menu->getChildByID("new-groupy-button")
        );
        smallActionsMenu->setContentSize({ 100.f, 290.f });
        smallActionsMenu->setPositionY(155.f);
        smallActionsMenu->updateLayout();

        auto actionsMenu = detachAndCreateMenu(
            this,
            "actions-menu",
            ColumnLayout::create()
                ->setAxisAlignment(AxisAlignment::Start)
                ->setAxisReverse(true),
        #ifdef GEODE_IS_DESKTOP
            menu->getChildByID("keys-button"),
        #endif
            menu->getChildByID("build-helper-button"),
            menu->getChildByID("copy-color-button"),
            menu->getChildByID("paste-color-button"),
            menu->getChildByID("create-extras-button"),
            menu->getChildByID("unlock-layers-button"),
            menu->getChildByID("reset-unused-button"),
            menu->getChildByID("uncheck-portals-button")
        );
        actionsMenu->setContentSize({ 100.f, 290.f });
        actionsMenu->setPositionY(155.f);
        actionsMenu->updateLayout();

        for(CCNode* node : CCArrayExt<CCNode*>(menu->getChildren())) {
            if(CCMenuItemToggler* toggler = typeinfo_cast<CCMenuItemToggler*>(node)) {

                auto off = toggler->m_offButton;
                auto on = toggler->m_onButton;

                float maxWidth = (std::max)(off->getContentSize().width, on->getContentSize().width);
                float maxHeight = (std::max)(off->getContentSize().height, on->getContentSize().height);

                toggler->setContentSize({maxWidth, maxHeight});
                off->setContentSize({maxWidth, maxHeight});
                on->setContentSize({maxWidth, maxHeight});

                off->setPosition({maxWidth/2, maxHeight/2});
                on->setPosition({maxWidth/2, maxHeight/2});

                CCSprite* offSpr = getChildOfType<CCSprite>(off, 0);
                CCSprite* onSpr = getChildOfType<CCSprite>(off, 0);

                off->setPosition({maxWidth/2, maxHeight/2});
                on->setPosition({maxWidth/2, maxHeight/2});

                offSpr->setPosition({maxWidth/2, maxHeight/2});
                onSpr->setPosition({maxWidth/2, maxHeight/2});
            }
        }

        auto optionsMenu = detachAndCreateMenu(
            this,
            "options-menu",
            RowLayout::create()
                ->setGap(5.f)
                ->setAxisAlignment(AxisAlignment::Start)
                ->setGrowCrossAxis(true)
                ->setCrossAxisAlignment(AxisAlignment::Start)
                ->setCrossAxisOverflow(false),
            menu->getChildByID("show-hitboxes-toggle"),
            this->getChildByID("show-hitboxes-label"),
            menu->getChildByID("hide-invisible-toggle"),
            this->getChildByID("hide-invisible-label"),
            menu->getChildByID("preview-mode-toggle"),
            this->getChildByID("preview-mode-label"),
            menu->getChildByID("preview-animations-toggle"),
            this->getChildByID("preview-animations-label"),
            menu->getChildByID("preview-particles-toggle"),
            this->getChildByID("preview-particles-label"),
            menu->getChildByID("preview-shaders-toggle"),
            this->getChildByID("preview-shaders-label"),
            menu->getChildByID("show-ground-toggle"),
            this->getChildByID("show-ground-label"),
            menu->getChildByID("show-object-info-toggle"),
            this->getChildByID("show-object-info-label"),
            menu->getChildByID("show-grid-toggle"),
            this->getChildByID("show-grid-label"),
            menu->getChildByID("select-filter-toggle"),
            this->getChildByID("select-filter-label"),
            menu->getChildByID("ignore-damage-toggle"),
            this->getChildByID("ignore-damage-label")
        );
        for (auto node : CCArrayExt<CCNode*>(optionsMenu->getChildren())) {
            if (auto label = typeinfo_cast<CCLabelBMFont*>(node)) {
                label->setLayoutOptions(
                    AxisLayoutOptions::create()
                        ->setSameLine(true)
                        ->setBreakLine(true)
                        ->setPrevGap(5.f)
                        ->setScaleLimits(.1f, .35f)
                        ->setScalePriority(1)
                );
            }
        }
        optionsMenu->setContentSize({ 120.f, winSize.height - 60.f });
        optionsMenu->setPosition(75.f, winSize.height / 2 - 25.f + 10.f);
        optionsMenu->updateLayout();

        auto settingsMenu = detachAndCreateMenu(
            this,
            "settings-menu",
            RowLayout::create()
                ->setAxisReverse(true),
            menu->getChildByID("settings-button")
        );
        settingsMenu->setContentSize({ 95.f, 50.f });
        settingsMenu->updateLayout();

        auto guidelinesMenu = menu;

        // replace the two guidelines buttons with a single toggle
        guidelinesMenu->getChildByID("guidelines-enable-button")->removeFromParent();
        guidelinesMenu->getChildByID("guidelines-disable-button")->removeFromParent();
        
        auto* spr = CCSprite::createWithSpriteFrameName("GJ_audioOffBtn_001.png");
        auto glToggle = CCMenuItemSpriteExtra::create(spr, this, menu_selector(GuidelinesButtonDummy::onClick));
        glToggle->setNormalImage(CCSprite::createWithSpriteFrameName(
            GameManager::get()->m_showSongMarkers ? 
                "GJ_audioOnBtn_001.png" :
                "GJ_audioOffBtn_001.png"
        ));
        glToggle->setID("guidelines-enable-toggle");
        guidelinesMenu->insertBefore(glToggle, nullptr);
        m_guidelinesOffButton = m_guidelinesOnButton = nullptr;
        // this->updateSongButton();

        guidelinesMenu->setID("guidelines-menu");
        guidelinesMenu->setContentSize({ winSize.width / 2, 50.f });
        guidelinesMenu->setLayout(RowLayout::create());

        auto topMenu = CCMenu::create();
        topMenu->setContentSize({ winSize.width / 2, 50.f });
        topMenu->setPosition(winSize.width / 2, winSize.height - 30.f);
        topMenu->setID("top-menu");
        topMenu->setLayout(RowLayout::create());
        this->addChild(topMenu);
    }

    if (auto menu = detachAndCreateMenu(
        this, "info-menu",
        ColumnLayout::create()
            ->setGap(10.f)
            ->setAxisAlignment(AxisAlignment::End)
            ->setAxisReverse(true)
            ->setCrossAxisOverflow(false)
            ->setCrossAxisAlignment(AxisAlignment::Start)
            ->setCrossAxisLineAlignment(AxisAlignment::Start),
        this->getChildByID("object-count-label"),
        this->getChildByID("length-label"),
        this->getChildByID("length-name-label")
    )) {
        for (auto child : CCArrayExt<CCNode*>(menu->getChildren())) {
            child->setLayoutOptions(
                AxisLayoutOptions::create()
                    ->setScaleLimits(.1f, .5f)
                    ->setBreakLine(true)
            );
        }
        menu->setContentSize({ 180.f, 100.f });
        menu->setPosition(100.f, winSize.height - 55.f);
        menu->updateLayout();
    }
}

struct EditorPauseLayerIDs : Modify<EditorPauseLayerIDs, EditorPauseLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("EditorPauseLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set EditorPauseLayer::init hook priority, node IDs may not work properly");
        }
    }

    bool init(LevelEditorLayer* lel) {
        if (!EditorPauseLayer::init(lel)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};
