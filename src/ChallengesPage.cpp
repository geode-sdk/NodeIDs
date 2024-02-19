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
    getChildOfType<cocos2d::CCMenu>(challengesLayer, 0)->setID("top-menu");
    getChildOfType<ChallengeNode>(challengesLayer, 0)->setID("top-challenge");
    getChildOfType<ChallengeNode>(challengesLayer, 1)->setID("middle-challenge");
    getChildOfType<ChallengeNode>(challengesLayer, 2)->setID("bottom-challenge");
    getChildOfType<cocos2d::CCLabelBMFont>(challengesLayer, 0)->setID("top-challenge-indicator");
    getChildOfType<cocos2d::CCLabelBMFont>(challengesLayer, 1)->setID("middle-challenge-indicator");
    getChildOfType<cocos2d::CCLabelBMFont>(challengesLayer, 2)->setID("bottom-challenge-indicator");
    getChildOfType<cocos2d::CCLabelBMFont>(challengesLayer, 3)->setID("new-challenges-label");

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
