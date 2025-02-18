#include <Geode/Geode.hpp>
#include <Geode/binding/GauntletSelectLayer.hpp>
#include <Geode/modify/GauntletSelectLayer.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(GauntletSelectLayer) {
    this->setID("main-layer");

    this->getChildByType<CCSprite>(0)->setID("background");
    this->getChildByType<CCSprite>(1)->setID("title-sprite");

    size_t idx = 0;
    setIDs(
        this,
        idx,
        "background",
        "title",
        "bottom-left-corner",
        "bottom-right-corner",
        "top-left-corner",
        "top-right-corner",
        "scroll-buttons-menu",
        "back-menu"
    );
    idx += 8;

    if (PlatformToolbox::isControllerConnected()) {
        // ID assigned in GameToolbox::addBackButton
        idx += 1;
    }

    setIDs(
        this,
        idx,
        "loading-circle",
        "try-again-text"
    );
    idx += 2;

    if (auto arrowsMenu = this->getChildByID("scroll-buttons-menu")) {
        setIDs(
            arrowsMenu,
            0,
            "left-button",
            "right-button"
        );
    }

    if (auto miscMenu = this->getChildByID("back-menu")) {
        setIDs(
            miscMenu,
            0,
            "back-button",
            "info-button",
            "refresh-button"
        );
        
        auto bottomLeftMenu = detachAndCreateMenu(
            this,
            "bottom-left-menu",
            ColumnLayout::create()
                ->setAxisAlignment(AxisAlignment::Start),
            miscMenu->getChildByID("info-button")
        );
        bottomLeftMenu->setPosition(30.f, 70.f);
        bottomLeftMenu->setID("bottom-left-menu");
        bottomLeftMenu->setContentSize({ 60.f, 103.f });
        bottomLeftMenu->updateLayout();
        
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        auto bottomRightMenu = detachAndCreateMenu(
            this,
            "bottom-right-menu",
            ColumnLayout::create()
                ->setAxisAlignment(AxisAlignment::Start)
                ->setAxisReverse(true),
            miscMenu->getChildByID("refresh-button")
        );
        bottomRightMenu->setPosition(winSize.width - 30.f, 70.f);
        bottomRightMenu->setID("bottom-right-menu");
        bottomRightMenu->setContentSize({ 60.f, 103.f });
        bottomRightMenu->updateLayout();

        auto topRightMenu = CCMenu::create();
        topRightMenu->setLayout(
            ColumnLayout::create()
                ->setAxisAlignment(AxisAlignment::End)
                ->setAxisReverse(true)
        );
        topRightMenu->setPosition(winSize.width - 30.f, winSize.height - 70.f);
        topRightMenu->setID("top-right-menu");
        topRightMenu->setContentSize({ 60.f, 103.f });
        topRightMenu->updateLayout();
        topRightMenu->setZOrder(miscMenu->getZOrder());
        this->addChild(topRightMenu);


        miscMenu->setPosition(25.f, winSize.height - 70.f + 16.75f);
        miscMenu->setID("back-menu");
        miscMenu->setLayout(
            ColumnLayout::create()
                ->setAxisAlignment(AxisAlignment::End)
                ->setAxisReverse(true)
        );
        miscMenu->setContentSize({ 60.f, 103.f });
        miscMenu->updateLayout();


    }
}

struct GauntletSelectLayerIDs : Modify<GauntletSelectLayerIDs, GauntletSelectLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("GauntletSelectLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set GauntletSelectLayer::init hook priority, node IDs may not work properly");
        }
        if (!self.setHookPriority("GauntletSelectLayer::setupGauntlets", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set GauntletSelectLayer::setupGauntlets hook priority, node IDs may not work properly");
        }
    }

    bool init(int p0) {
        if (!GauntletSelectLayer::init(p0)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }

    void setupGauntlets() {
        GauntletSelectLayer::setupGauntlets();

        if (auto gauntletsList = this->getChildByType<BoomScrollLayer>(0)) {
            gauntletsList->setID("gauntlets-list");

            if (auto gauntletPages = gauntletsList->getChildByType<ExtendedLayer>(0)) {
                gauntletPages->setID("gauntlet-pages");

                auto gauntletPagesArray = CCArrayExt<CCLayer*>(gauntletPages->getChildren());
                for (int i = 0; i < gauntletPagesArray.size(); i++) {
                    auto gauntletPage = gauntletPagesArray[i];
                    gauntletPage->setID(fmt::format("gauntlet-page-{}", i + 1));

                    if (auto gauntletMenu = gauntletPage->getChildByType<CCMenu>(0)) {
                        gauntletMenu->setID("gauntlet-menu");

                        auto gauntletButtons = CCArrayExt<CCMenuItemSpriteExtra*>(gauntletMenu->getChildren());
                        for (int i = 0; i < gauntletButtons.size(); i++) {
                            auto gauntletButton = gauntletButtons[i];

                            gauntletButton->setID(fmt::format("gauntlet-button-{}", i + 1));

                            if (auto gauntletNodeParent = gauntletButton->getChildByType<CCNode>(0)) {
                                gauntletNodeParent->setID("gauntlet-node-parent");

                                gauntletNodeParent->getChildByType<GauntletNode>(0)->setID("gauntlet-node");
                            }
                        }
                    }
                }
            }

            gauntletsList->getChildByType<CCSpriteBatchNode>(0)->setID("page-buttons");
        }
    }
};
