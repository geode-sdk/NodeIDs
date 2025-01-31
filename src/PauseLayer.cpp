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
        "level-name"
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

    for(auto child : CCArrayExt<CCNode*>(this->getChildren())) {
        if (auto bmFont = typeinfo_cast<CCLabelBMFont*>(child)) {
            if(std::string_view(bmFont->getString()).starts_with("Points") && bmFont->getID().empty()) {
                bmFont->setID("points-label");
                idx += 1;
                break;
            }
        }
    }

    setIDSafe(this, idx, "center-button-menu");
    idx += 1;

    if(auto practiceTxt = getChildBySpriteFrameName(this, "GJ_practiceTxt_001.png")) {
        practiceTxt->setID("practice-arrow-text");
        idx += 1;
    }

    setIDs(
        this,
        idx,
        "music-slider", 
        "sfx-slider", 
        "music-label", 
        "sfx-label"
    );
    idx += 4;

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
    leftMenu->setPosition({36.f, (winSize.height / 2)});
    leftMenu->setContentSize({40, winSize.height - 40.f});
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
    rightMenu->setPosition({winSize.width - 36.f, (winSize.height / 2)});
    rightMenu->setContentSize({40, winSize.height - 40.f});
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
    bottomMenu->setPosition({(winSize.width / 2), 30.f});
    bottomMenu->setContentSize({400, 30});
    bottomMenu->setZOrder(10);
    this->addChild(bottomMenu);

    if (auto menu = this->getChildByID("center-button-menu")) {

        int idx = 0;
        if (auto* node = getChildBySpriteFrameName(menu, "GJ_editBtn_001.png")) {
            node->setID("edit-button");
            ++idx;
        }

        if (auto* node = getChildBySpriteFrameName(menu, "GJ_replayFullBtn_001.png")) {
            node->setID("full-restart-button");
            ++idx;
        }

        if (auto* node = getChildBySpriteFrameName(menu, "GJ_menuBtn_001.png")) {
            node->setID("exit-button");
            ++idx;
        }

        if (auto* node = getChildBySpriteFrameName(menu, "GJ_menuBtn_001.png")) {
            node->setID("exit-button");
            ++idx;
        }

        if (auto* node = getChildBySpriteFrameName(menu, "GJ_normalBtn_001.png")) {
            node->setID("practice-button");
            ++idx;
        }

        if (auto* node = getChildBySpriteFrameName(menu, "GJ_practiceBtn_001.png")) {
            node->setID("practice-button");
            ++idx;
        }

        if (auto* node = getChildBySpriteFrameName(menu, "GJ_playBtn2_001.png")) {
            node->setID("play-button");
            ++idx;
        }

        if (auto* node = getChildBySpriteFrameName(menu, "GJ_replayBtn_001.png")) {
            node->setID("retry-button");
            ++idx;
        }

        if (auto* node = getChildBySpriteFrameName(menu, "GJ_optionsBtn_001.png")) {
            node->setID("options-button");
            node->removeFromParentAndCleanup(false);
            rightMenu->addChild(node);
            rightMenu->updateLayout();
            ++idx;
        }
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
