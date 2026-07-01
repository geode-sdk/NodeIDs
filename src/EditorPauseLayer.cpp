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

CCMenu* createToggleContainer(EditorPauseLayer* self, CCMenu* menu, CCNode* addTo, ZStringView ID) {
    return detachAndCreateMenu(
        addTo, 
        fmt::format("{}-container", ID).c_str(), 
        SimpleRowLayout::create()
            ->setGap(5.f)
            ->setMainAxisScaling(AxisScaling::Fit)
            ->setCrossAxisScaling(AxisScaling::Fit), 
        menu->getChildByID(fmt::format("{}-toggle", ID)), 
        self->getChildByID(fmt::format("{}-label", ID))
    );
}

$register_ids(EditorPauseLayer) {
    auto winSize = CCDirector::get()->getWinSize();

    if (auto menu = this->getChildByType<CCMenu>(0)) {
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
            SimpleColumnLayout::create()
                ->setGap(12.5f)
                ->setCrossAxisScaling(AxisScaling::Fit)
                ->setMainAxisDirection(AxisDirection::TopToBottom)
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

    if (auto menu = this->getChildByType<CCMenu>(1)) {
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

            "create-loop-button",
            "regroup-button",
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
            SimpleColumnLayout::create()
                ->setGap(5.f)
                ->setMainAxisScaling(AxisScaling::ScaleDownGaps)
                ->setCrossAxisScaling(AxisScaling::Fit)
                ->setMainAxisAlignment(MainAxisAlignment::End)
                ->setMainAxisDirection(AxisDirection::TopToBottom),
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
        smallActionsMenu->setAnchorPoint({0.5f, 0.f});
        smallActionsMenu->setPositionY(10.f);
        smallActionsMenu->updateLayout();

        auto actionsMenu = detachAndCreateMenu(
            this,
            "actions-menu",
            SimpleColumnLayout::create()
                ->setGap(5.f)
                ->setMainAxisScaling(AxisScaling::ScaleDownGaps)
                ->setCrossAxisScaling(AxisScaling::Fit)
                ->setMainAxisAlignment(MainAxisAlignment::End)
                ->setMainAxisDirection(AxisDirection::TopToBottom),
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
        actionsMenu->setContentSize({ 100.f, 230.f });
        actionsMenu->setAnchorPoint({0.5f, 0.f});
        actionsMenu->setPositionY(10.f);
        actionsMenu->updateLayout();

        for (auto node : menu->getChildrenExt()) {
            auto toggler = typeinfo_cast<CCMenuItemToggler*>(node);
            if (!toggler) continue;

            float maxWidth = std::max(toggler->m_offButton->getContentWidth(), toggler->m_onButton->getContentWidth());
            float maxHeight = std::max(toggler->m_offButton->getContentHeight(), toggler->m_onButton->getContentHeight());

            auto maxSize = CCSize{maxWidth, maxHeight};
            auto halfSize = maxSize / 2;

            toggler->setContentSize(maxSize);
            toggler->m_offButton->setContentSize(maxSize);
            toggler->m_onButton->setContentSize(maxSize);

            auto offSpr = toggler->m_offButton->getNormalImage();
            auto onSpr = toggler->m_onButton->getNormalImage();

            toggler->m_offButton->setPosition(halfSize);
            toggler->m_onButton->setPosition(halfSize);

            offSpr->setPosition(halfSize);
            onSpr->setPosition(halfSize);
        }

        // kept as a CCMenu in case anyone relies on that
        auto optionsMenu = CCMenu::create();
        optionsMenu->setID("options-menu");
        optionsMenu->setLayout(SimpleColumnLayout::create()
            ->setGap(5.f)
            ->setMainAxisDirection(AxisDirection::TopToBottom)
            ->setCrossAxisAlignment(CrossAxisAlignment::Start)
            ->setMainAxisScaling(AxisScaling::ScaleDownGaps)
            ->setCrossAxisScaling(AxisScaling::Fit)
        );
        createToggleContainer(this, menu, optionsMenu, "show-hitboxes");
        createToggleContainer(this, menu, optionsMenu, "hide-invisible");
        createToggleContainer(this, menu, optionsMenu, "preview-mode");
        createToggleContainer(this, menu, optionsMenu, "preview-animations");
        createToggleContainer(this, menu, optionsMenu, "preview-particles");
        createToggleContainer(this, menu, optionsMenu, "preview-shaders");
        createToggleContainer(this, menu, optionsMenu, "show-ground");
        createToggleContainer(this, menu, optionsMenu, "show-object-info");
        createToggleContainer(this, menu, optionsMenu, "show-grid");
        createToggleContainer(this, menu, optionsMenu, "select-filter");
        createToggleContainer(this, menu, optionsMenu, "ignore-damage");

        optionsMenu->setContentSize({ 120.f, winSize.height - 62.f });
        optionsMenu->setAnchorPoint({0.f, 0.f});
        optionsMenu->setPosition(15.5f, 14.5f);
        optionsMenu->updateLayout();

        addChild(optionsMenu);

        auto settingsMenu = detachAndCreateMenu(
            this,
            "settings-menu",
            ColumnLayout::create()
                ->setCrossAxisReverse(true)
                ->setGrowCrossAxis(true)
                ->setCrossAxisOverflow(false)
                ->setAxisAlignment(AxisAlignment::Start),
            menu->getChildByID("settings-button")
        );
        settingsMenu->setContentSize({ 54.f, 62.f });
        settingsMenu->updateLayout();
        settingsMenu->setAnchorPoint({0.5f, 1.f});
        settingsMenu->setPosition({actionsMenu->getPositionX(), winSize.height - 5.f});

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

        guidelinesMenu->setID("guidelines-menu");
        guidelinesMenu->setContentSize({ winSize.width / 2, 50.f });
        guidelinesMenu->setLayout(SimpleRowLayout::create()
            ->setGap(5.f)
        );

        auto topMenu = CCMenu::create();
        topMenu->setContentSize({ winSize.width / 2 - 20, 50.f });
        topMenu->setPosition(winSize.width / 2, winSize.height - 30.f);
        topMenu->setID("top-menu");
        topMenu->setLayout(SimpleRowLayout::create()
            ->setGap(5.f)
        );
        this->addChild(topMenu);
    }

    auto infoMenu = detachAndCreateMenu(
        this, "info-menu",
        SimpleColumnLayout::create()
            ->setGap(16.f)
            ->setMainAxisAlignment(MainAxisAlignment::Start)
            ->setMainAxisScaling(AxisScaling::ScaleDownGaps)
            ->setCrossAxisScaling(AxisScaling::Fit)
            ->setCrossAxisAlignment(CrossAxisAlignment::Start)
            ->setMainAxisDirection(AxisDirection::TopToBottom),
        this->getChildByID("object-count-label"),
        this->getChildByID("length-label"),
        this->getChildByID("length-name-label"));
    
    infoMenu->addOnEnterCallback([infoMenu] {
        infoMenu->updateLayout();
    });

    infoMenu->setContentSize({ 180.f, 34.f });
    infoMenu->setScale(0.927f);
    infoMenu->setAnchorPoint({0.f, 1.f});
    infoMenu->setPosition(10.f, winSize.height - 6.f);
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
