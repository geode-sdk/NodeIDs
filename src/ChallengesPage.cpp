#include <Geode/Bindings.hpp>
#include <Geode/modify/ChallengesPage.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>
#include <Geode/utils/NodeIDs.hpp>


using namespace geode::prelude;
using namespace geode::node_ids;


$register_ids(ChallengesPage) {

    auto challengesLayer = static_cast<cocos2d::CCLayer*>(this->getChildren()->objectAtIndex(0));
    auto winSize = CCDirector::get()->getWinSize();


    getChildOfType<cocos2d::extension::CCScale9Sprite>(challengesLayer, 0)->setID("background");
    auto topMenu = getChildOfType<cocos2d::CCMenu>(challengesLayer, 0);
    topMenu->setID("top-menu");
    topMenu->setLayout(
    RowLayout::create()
        ->setGap(370.f)
        ->setGrowCrossAxis(true)
    );
    topMenu->updateLayout();
    topMenu->setPositionX(285);
    getChildOfType<ChallengeNode>(challengesLayer, 0)->setID("top-quest");
    getChildOfType<ChallengeNode>(challengesLayer, 1)->setID("middle-quest");
    getChildOfType<ChallengeNode>(challengesLayer, 2)->setID("bottom-quest");
    getChildOfType<cocos2d::CCLabelBMFont>(challengesLayer, 0)->setID("new-quest-label");
    getChildOfType<cocos2d::CCLabelBMFont>(challengesLayer, 1)->setID("top-quest-indicator");
    getChildOfType<cocos2d::CCLabelBMFont>(challengesLayer, 2)->setID("middle-quest-indicator");
    getChildOfType<cocos2d::CCLabelBMFont>(challengesLayer, 3)->setID("bottom-quest-indicator");

};

struct ChallengesPageIDs : Modify<ChallengesPageIDs, ChallengesPage> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("ChallengesPage::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set ChallengesPage::init hook priority, node IDs may not work properly");
        }
    }

    bool init() {
        if(!ChallengesPage::init()) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};
