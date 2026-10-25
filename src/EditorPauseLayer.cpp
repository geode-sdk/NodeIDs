#include <Geode/Geode.hpp>
#include <Geode/utils/NodeIDs.hpp>
#include <Geode/modify/EditorPauseLayer.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(EditorPauseLayer) {
    auto winSize = CCDirector::get()->getWinSize();

    auto resumeMenu = this->getChildByType<CCMenu>(0);
    if (resumeMenu) {
        resumeMenu->setID("resume-menu");

        setIDs(
            resumeMenu, 0,
            "resume-button",
            "save-and-play-button",
            "save-and-exit-button",
            "save-button",
            "exit-button"
        );

        resumeMenu->setContentSize({200.f, 215.f});
        resumeMenu->setLayout(
            SimpleColumnLayout::create()
                ->setMainAxisScaling(AxisScaling::ScaleDownGaps)
                ->setCrossAxisScaling(AxisScaling::Fit)
                ->setGap(14.f)
                ->setCrossAxisDirection(AxisDirection::BottomToTop)
        );
    }

    auto settingsMenu = this->getChildByType<CCMenu>(1);
    if (settingsMenu) {
        settingsMenu->setID("settings-menu");
        
        setIDs(
            settingsMenu, 0,
            "settings-button",
            "export-button",
            "editor-sfx-button",
            "auto-save-button",
            "death-stats-button",
            "get-audio-button",
            "help-button",
            "controls-button"
        );

        settingsMenu->setAnchorPoint({1.f, 1.f});
        settingsMenu->setPosition({winSize.width - 9.f GEODE_IOS(- geode::utils::getSafeAreaRect().getMinX() / 2.f), winSize.height - 7.f});
        settingsMenu->setContentSize({90.f, winSize.height - 60.f});
        settingsMenu->setLayout(
            SimpleColumnLayout::create()
                ->setMainAxisScaling(AxisScaling::ScaleDownGaps)
                ->setCrossAxisScaling(AxisScaling::Fit)
                ->setMainAxisAlignment(MainAxisAlignment::Start)
                ->setGap(6.f)
                ->setCrossAxisDirection(AxisDirection::BottomToTop)
        );
    }

    setIDSafe<CCLabelBMFont>(this, 0, "music-label");
    setIDSafe<CCLabelBMFont>(this, 1, "sfx-label");
    setIDSafe<CCLabelBMFont>(this, 2, "editor-sfx-label");
    setIDSafe<CCLabelBMFont>(this, 3, "object-count-label");
    setIDSafe<CCLabelBMFont>(this, 4, "length-label");

    setIDSafe<Slider>(this, 0, "music-slider");
    setIDSafe<Slider>(this, 1, "sfx-slider");
    setIDSafe<Slider>(this, 2, "editor-sfx-slider");

    setIDSafe<TimeSpeedControl>(this, 0, "time-speed-control");

    auto musicContainer = detachAndCreateNode<CCNode>(
        this, "music-container", 
        nullptr, 
        this->getChildByID("music-label"), 
        this->getChildByID("music-slider")
    );

    auto sfxContainer = detachAndCreateNode<CCNode>(
        this, "sfx-container", 
        nullptr, 
        this->getChildByID("sfx-label"), 
        this->getChildByID("sfx-slider")
    );

    auto editorSfxContainer = detachAndCreateNode<CCNode>(
        this, "editor-sfx-container", 
        nullptr, 
        this->getChildByID("editor-sfx-label"), 
        this->getChildByID("editor-sfx-slider")
    );

    auto infoMenu = detachAndCreateMenu(
        this, "info-menu",
        SimpleColumnLayout::create()
            ->setGap(7.f)
            ->setMainAxisAlignment(MainAxisAlignment::Start)
            ->setCrossAxisAlignment(CrossAxisAlignment::Start),
        this->getChildByID("object-count-label"),
        this->getChildByID("length-label")
    );

    if (infoMenu) {
        for (auto child : CCArrayExt<CCNode*>(infoMenu->getChildren())) {
            child->setLayoutOptions(
                AxisLayoutOptions::create()
                    ->setScaleLimits(0.1f, 0.5f)
                    ->setBreakLine(true)
            );
        }

        infoMenu->setAnchorPoint({0.f, 1.f});
        infoMenu->setContentSize({180.f, 50.f});
        infoMenu->setPosition(10.f GEODE_IOS(+ geode::utils::getSafeAreaRect().getMinX() / 2.f), winSize.height - 5.f);
        infoMenu->updateLayout();
    }

    auto topMenu = CCMenu::create();
    topMenu->setAnchorPoint({0.5f, 1.f});
    topMenu->setContentSize({winSize.width - 340.f, 50.f});
    topMenu->setPosition(winSize.width / 2, winSize.height);
    topMenu->setID("top-menu");
    topMenu->setLayout(SimpleRowLayout::create()
        ->setGap(5.f)
    );
    this->addChild(topMenu);
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
