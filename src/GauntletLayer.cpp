#include <Geode/Geode.hpp>
#include <Geode/binding/GauntletLayer.hpp>
#include <Geode/modify/GauntletLayer.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(GauntletLayer) {
    this->setID("main-layer");

    this->getChildByType<CCSprite>(0)->setID("background");
    this->getChildByType<CCLabelBMFont>(0)->setID("title");
    this->getChildByType<CCLabelBMFont>(1)->setID("title-shadow");
    this->getChildByType<TextArea>(0)->setID("try-again-text");
    this->getChildByType<LoadingCircle>(0)->setID("loading-circle");

    if (auto menu = this->getChildByType<CCMenu>(0)) {
        menu->setID("exit-menu");
        auto exitBtn = setIDSafe(menu, 0, "exit-button");
        menu->setPositionY(
            menu->getPositionY() - 125.f / 2 +
                getSizeSafe(exitBtn).height / 2
        );
        menu->setContentSize({ 60.f, 125.f });
        menu->setLayout(
            ColumnLayout::create()
                ->setAxisAlignment(AxisAlignment::End)
        );
    }
}

struct GauntletLayerIDs : Modify<GauntletLayerIDs, GauntletLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("GauntletLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set GauntletLayer::init hook priority, node IDs may not work properly");
        }
        if (!self.setHookPriority("GauntletLayer::setupGauntlet", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set GauntletLayer::setupGauntlet hook priority, node IDs may not work properly");
        }
    }

    bool init(GauntletType p0) {
        if (!GauntletLayer::init(p0))
            return false;

        NodeIDs::get()->provide(this);

        return true;
    }

    void setupGauntlet(cocos2d::CCArray* p0) {
        auto before = this->getChildrenCount();
        GauntletLayer::setupGauntlet(p0);
        if(this->getChildrenCount() == before) return;

        if (auto menu = this->getChildByType<CCMenu>(-1)) {
            menu->setID("levels-menu");
            for (int i = 0; i < 5; i++) {
                menu->getChildByType<CCMenuItemSpriteExtra>(i)->setID(fmt::format("level-{}", i + 1));
            }
        }
    }
};
