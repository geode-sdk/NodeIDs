#include <Geode/Bindings.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(PauseLayer) {
    if (auto layer = setIDSafe(this, 0, "main-layer")) {
        int idx = 0;
        setIDs(
            layer,
            idx,
            "background",
            "level-name"
        );
        idx += 2;
        auto pl = PlayLayer::get();
        auto level = pl->m_level;
        auto controller = PlatformToolbox::isControllerConnected();
        auto practice = pl->m_isPracticeMode;

        if (level->isPlatformer()) {
            setIDs(
                layer,
                idx,
                "play-time"
            );
            idx += 1;
        }
        else {
            if (GameManager::get()->getGameVariable(GameVar::LegacyPauseProgress)) {
                setIDs(
                    layer,
                    idx,
                    "normal-progress-bar",
                    "practice-progress-bar",
                    "normal-progress-label",
                    "practice-progress-label",
                    "normal-mode-label",
                    "practice-mode-label"
                );
                idx += 6;
            } else {
                setIDs(
                    layer,
                    idx,
                    "progress-bar",
                    "progress-label",
                    "mode-label"
                );
                if (auto prog = layer->getChildByID("progress-bar")) {
                    setIDs(
                        prog,
                        0,
                        "best-bar",
                        "current-bar"
                    );
                }
                idx += 3;
                if ((practice && level->m_practicePercent) || (!practice && level->m_normalPercent)) {
                    setIDSafe(layer, idx++, "best-label");
                }
            }
        }
        setIDSafe(layer, idx++, "center-button-menu");

        for(auto child : CCArrayExt<CCNode*>(layer->getChildren())) {
            if (auto bmFont = typeinfo_cast<CCLabelBMFont*>(child)) {
                if(std::string_view(bmFont->getString()).starts_with("Points") && bmFont->getID().empty()) {
                    bmFont->setID("points-label");
                    idx += 1;
                    break;
                }
            }
        }

        if(auto practiceTxt = getChildBySpriteFrameName(layer, "GJ_practiceTxt_001.png")) {
            practiceTxt->setID("practice-arrow-text");
            idx += 1;
        }

        setIDs(
            layer,
            idx,
            "music-slider",
            "sfx-slider",
            "music-icon",
            "sfx-icon"
        );
        idx += 4;

        if (level->m_levelType == GJLevelType::Editor) {
            setIDs(
                layer,
                idx,
                "startpos-label",
                "current-label"
            );
            idx += 2;
        } else if (!practice) {
            for (int i = 1; i <= level->m_coins; i++) {
                setIDSafe(layer, idx, fmt::format("coin-{}", i).c_str());
                idx++;
            }
        }

        if (controller) {
            setIDs(
                layer,
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
                ->setGap(5.5f)
                ->setAxisAlignment(AxisAlignment::End)
                ->setAxisReverse(true)
                ->setCrossAxisOverflow(false)
        );
        leftMenu->setID("left-button-menu");
        leftMenu->setPosition({36.f, (winSize.height / 2)});
        leftMenu->setContentSize({40, winSize.height - 40.f});
        leftMenu->setZOrder(10);
        layer->addChild(leftMenu);

        auto rightMenu = CCMenu::create();
        rightMenu->setLayout(
            ColumnLayout::create()
                ->setGap(5.5f)
                ->setAxisAlignment(AxisAlignment::End)
                ->setAxisReverse(true)
                ->setCrossAxisOverflow(false)
        );
        rightMenu->setID("right-button-menu");
        rightMenu->setPosition({winSize.width - 36.f, (winSize.height / 2)});
        rightMenu->setContentSize({40, winSize.height - 40.f});
        rightMenu->setZOrder(10);
        layer->addChild(rightMenu);

        auto bottomMenu = CCMenu::create();
        bottomMenu->setID("bottom-button-menu");
        bottomMenu->setPosition({(winSize.width / 2), 33.f});
        bottomMenu->setContentSize({400, 30});
        bottomMenu->setZOrder(10);
        bottomMenu->setLayout(
            RowLayout::create()
                ->setGap(4.f)
                ->setAxisAlignment(AxisAlignment::Center)
                ->setCrossAxisOverflow(false)
        );
        layer->addChild(bottomMenu);

        if (level->m_levelType != GJLevelType::Editor && !practice) {
            auto coinMenu = detachAndCreateNode<CCNode>(bottomMenu, "coin-container",
                RowLayout::create()
                    ->setAutoScale(false)
                    ->setAxisAlignment(AxisAlignment::Center)
                    ->setCrossAxisOverflow(false)
                    ->setGap(20.f)
                    ->setAutoGrowAxis(0.f),
                layer->getChildByID("coin-1"),
                layer->getChildByID("coin-2"),
                layer->getChildByID("coin-3"));
            coinMenu->setContentHeight(30.f);
            coinMenu->updateLayout();
            bottomMenu->updateLayout();
        }

        if (auto menu = layer->getChildByID("center-button-menu")) {
            int idx = 0;
            if (auto* node = getChildBySpriteFrameName(menu, "GJ_editBtn_001.png")) {
                node->setID("edit-button");
                idx++;
            }

            if (auto* node = getChildBySpriteFrameName(menu, "GJ_replayFullBtn_001.png")) {
                node->setID("full-restart-button");
                idx++;
            }

            if (auto* node = getChildBySpriteFrameName(menu, "GJ_menuBtn_001.png")) {
                node->setID("exit-button");
                idx++;
            }

            if (auto* node = getChildBySpriteFrameName(menu, "GJ_normalBtn_001.png")) {
                node->setID("practice-button");
                idx++;
            }

            if (auto* node = getChildBySpriteFrameName(menu, "GJ_practiceBtn_001.png")) {
                node->setID("practice-button");
                idx++;
            }

            if (auto* node = getChildBySpriteFrameName(menu, "GJ_playBtn2_001.png")) {
                node->setID("play-button");
                idx++;
            }

            if (auto* node = getChildBySpriteFrameName(menu, "GJ_replayBtn_001.png")) {
                node->setID("retry-button");
                idx++;
            }

            if (auto* node = menu->getChildByTag(0)) {
                node->setID("options-button");
                switchToMenu(node, rightMenu);
            }

            if (auto* node = menu->getChildByTag(1)) {
                node->setID("hide-pause-menu-button");
                switchToMenu(node, rightMenu);
            }

            if (auto* node = menu->getChildByTag(2)) {
                node->setID("death-tracker-button");
                switchToMenu(node, leftMenu);
            }

            if (auto* node = menu->getChildByTag(3)) {
                node->setID("death-markers-button");
                switchToMenu(node, leftMenu);
            }

            if (auto* node = menu->getChildByTag(4)) {
                node->setID("comments-button");
                switchToMenu(node, leftMenu);
            }

            if (auto* node = menu->getChildByTag(5)) {
                node->setID("quests-button");
                switchToMenu(node, leftMenu);
            }

            if (auto* node = menu->getChildByTag(6)) {
                node->setID("ignore-damage-button");
                switchToMenu(node, leftMenu);
            }

            if (auto* node = menu->getChildByTag(7)) {
                node->setID("platformer-ui-button");
                switchToMenu(node, leftMenu);
            }

            if (auto* node = menu->getChildByTag(8)) {
                node->setID("speed-modifier-button");
                switchToMenu(node, rightMenu);
            }

            if (auto* node = menu->getChildByTag(9)) {
                node->setID("practice-ui-button");
                switchToMenu(node, rightMenu);
            }

            leftMenu->updateLayout();
            rightMenu->updateLayout();

            if (level->m_levelType == GJLevelType::Editor) {
                setIDs(
                    menu,
                    idx,
                    "left-button",
                    "right-button",
                    "select-button",
                    "create-button"
                );

                auto startposContainer = CCMenu::create();
                startposContainer->ignoreAnchorPointForPosition(false);
                startposContainer->setContentSize({325.f, 30.f});
                startposContainer->setID("startpos-container");
                bottomMenu->addChild(startposContainer);
                bottomMenu->updateLayout();

                switchToMenu(layer->getChildByID("current-label"), startposContainer);
                switchToMenu(layer->getChildByID("startpos-label"), startposContainer);
                switchToMenu(menu->getChildByID("left-button"), startposContainer);
                switchToMenu(menu->getChildByID("right-button"), startposContainer);
                switchToMenu(menu->getChildByID("select-button"), startposContainer);
                switchToMenu(menu->getChildByID("create-button"), startposContainer);
            }

            menu->setContentSize({440, 81.5f});
            menu->setLayout(SimpleRowLayout::create()->setGap(10.f)->setCrossAxisScaling(AxisScaling::Grow));
        }
    }
    if (auto menu = setIDSafe(this, 1, "hide-pause-menu")) {
        setIDSafe(menu, 0, "hide-pause-button");
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
