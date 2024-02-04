#include <Geode/Bindings.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(PauseLayer) {
    int idx = 0;
    setIDs(
        this,
        idx,
        "background",
        "level-name",

        "normal-progress-bar",
        "practice-progress-bar",
        "normal-progress-label",
        "practice-progress-label",
        "normal-mode-label",
        "practice-mode-label",

        "center-button-menu",

        "music-slider", 
        "sfx-slider", 
        "music-label", 
        "sfx-label"
    );
    idx += 2;

    auto level = PlayLayer::get()->m_level;
    auto controller = PlatformToolbox::isControllerConnected();

    if (level->isPlatformer()) {
        setIDs(
            this,
            idx,
            "play-time"
        );
        idx += 1;
    }
    else {
        setIDs(
            this,
            idx,
            "normal-progress-bar",
            "practice-progress-bar",
            "normal-progress-label",
            "practice-progress-label",
            "normal-mode-label",
            "practice-mode-label"
        );
        idx += 6;
    }

    if (this->getChildrenCount() == idx + 5 + 1 + controller * 3) {
        setIDs(
            this,
            idx,
            "practice-arrow-text"
        );
        idx += 1;
    }

    setIDs(
        this,
        idx,
        "center-button-menu",

        "music-slider", 
        "sfx-slider", 
        "music-label", 
        "sfx-label"
    );
    idx += 5;

    if (controller) {
        setIDs(
            this,
            idx,
            "controller-play-hint",
            "controller-back-hint",
            "controller-practice-hint"
        );
    }

    auto winSize = CCDirector::sharedDirector()->getWinSize();

    auto leftMenu = CCMenu::create();
    leftMenu->setLayout(
        ColumnLayout::create()
            ->setGap(4.f)
            ->setAxisAlignment(AxisAlignment::End)
            ->setAxisReverse(true)
            ->setCrossAxisOverflow(false)
    );
    leftMenu->setID("left-button-menu");
    leftMenu->setPosition({(winSize.width / 2) - 240.f, (winSize.height / 2)});
    leftMenu->setContentSize({40, 280});
    leftMenu->setZOrder(10);
    this->addChild(leftMenu);

    auto rightMenu = CCMenu::create();
    rightMenu->setLayout(
        ColumnLayout::create()
            ->setGap(4.f)
            ->setAxisAlignment(AxisAlignment::End)
            ->setAxisReverse(true)
            ->setCrossAxisOverflow(false)
    );
    rightMenu->setID("right-button-menu");
    rightMenu->setPosition({(winSize.width / 2) + 240.f, (winSize.height / 2)});
    rightMenu->setContentSize({40, 280});
    rightMenu->setZOrder(10);
    this->addChild(rightMenu);

    auto bottomMenu = CCMenu::create();
    bottomMenu->setLayout(
        RowLayout::create()
            ->setGap(4.f)
            ->setAxisAlignment(AxisAlignment::Center)
            ->setCrossAxisOverflow(false)
    );
    bottomMenu->setID("bottom-button-menu");
    bottomMenu->setPosition({(winSize.width / 2), (winSize.height / 2) - 130.f});
    bottomMenu->setContentSize({400, 30});
    bottomMenu->setZOrder(10);
    this->addChild(bottomMenu);

    if (auto menu = this->getChildByID("center-button-menu")) {

        int idx = 0;
        if (level->m_levelType == GJLevelType::Editor) {
            setIDSafe(menu, idx, "edit-button");
            ++idx;
        }

        if (level->isPlatformer()) {
            setIDSafe(menu, idx, "full-restart-button");
            ++idx;
        }

        setIDs(menu, idx, "practice-button", "play-button", "exit-button", "retry-button", "options-button");

        auto options = menu->getChildByID("options-button");
        options->removeFromParentAndCleanup(false);
        rightMenu->addChild(options);
        rightMenu->updateLayout();
    }
}

struct PauseLayerIDs : Modify<PauseLayerIDs, PauseLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("PauseLayer::customSetup", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set PauseLayer::customSetup hook priority, node IDs may not work properly");
        }
    }

    void customSetup() {
        PauseLayer::customSetup();

        NodeIDs::get()->provide(this);
    }
};
