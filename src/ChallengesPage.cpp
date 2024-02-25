#include <Geode/Bindings.hpp>
#include <Geode/modify/ChallengesPage.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>
#include <Geode/utils/NodeIDs.hpp>


using namespace geode::prelude;
using namespace geode::node_ids;


$register_ids(ChallengesPage) {

    auto winSize = CCDirector::get()->getWinSize();

    m_mainLayer->setID("main-layer");

    setIDSafe<cocos2d::extension::CCScale9Sprite>(m_mainLayer, 0, "background");
    setIDSafe<LoadingCircle>(m_mainLayer, 0, "loading-circle");

    setIDs(
        m_mainLayer,
        1,
        "bottom-left-art",
        "top-left-art",
        "top-right-art",
        "bottom-right-art"
    );

    if(auto topMenu = getChildOfType<cocos2d::CCMenu>(m_mainLayer, 0)) {
        setIDs(
            topMenu,
            0,
            "close-button",
            "info-button"
        );

        topMenu->setID("main-menu");
        // leave m_buttonMenu unlayouted, even if it'll have to be empty
        // otherwise we could break assumptions from other mods

        auto infoMenu = detachAndCreateMenu(
            m_mainLayer,
            "top-right-menu",
            ColumnLayout::create()
                ->setAxisReverse(true)
                ->setAxisAlignment(AxisAlignment::End),
            topMenu->getChildByID("info-button")
        );
        infoMenu->setContentSize({ 60.f, 120.f });
        infoMenu->setPositionY(
            infoMenu->getPositionY() - 120.f / 2 + 
                infoMenu->getChildByID("info-button")->getScaledContentSize().height / 2
        );
        infoMenu->updateLayout();

        auto closeMenu = detachAndCreateMenu(
            m_mainLayer,
            "top-left-menu",
            ColumnLayout::create()
                ->setAxisReverse(true)
                ->setAxisAlignment(AxisAlignment::End),
            topMenu->getChildByID("close-button")
        );
        closeMenu->setContentSize({ 60.f, 120.f });
        closeMenu->setPositionY(
            closeMenu->getPositionY() - 120.f / 2 + 
                closeMenu->getChildByID("close-button")->getScaledContentSize().height / 2
        );
        closeMenu->updateLayout();
    }
    /*getChildOfType<ChallengeNode>(m_mainLayer, 0)->setID("top-quest");
    getChildOfType<ChallengeNode>(m_mainLayer, 1)->setID("middle-quest");
    getChildOfType<ChallengeNode>(m_mainLayer, 2)->setID("bottom-quest");*/
    setIDSafe<cocos2d::CCLabelBMFont>(m_mainLayer, 0, "new-quest-label");

    // For some reason this is more reliable?
    for(intptr_t i = 0; i <= 2; i++) {
        if(!m_dots->objectAtIndex(i)) continue;
        auto dot = static_cast<CCLabelBMFont*>(m_dots->objectAtIndex(i));

        switch(i) {
            case 0: dot->setID("top-quest-indicator"); break;
            case 1: dot->setID("middle-quest-indicator"); break;
            case 2: dot->setID("bottom-quest-indicator"); break;
            default: dot->setID(fmt::format("quest-{}-indicator", i)); break;
        }
    }

};

struct ChallengesPageIDs : Modify<ChallengesPageIDs, ChallengesPage> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("ChallengesPage::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set ChallengesPage::init hook priority, node IDs may not work properly");
        }
        if (!self.setHookPriority("ChallengesPage::createChallengeNode", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set ChallengesPage::createChallengeNode hook priority, node IDs may not work properly");
        }
    }

    ChallengeNode* createChallengeNode(int number, bool skipAnimation, float animLength, bool isNew) {
        auto node = ChallengesPage::createChallengeNode(number, skipAnimation, animLength, isNew);
        if(!node) return nullptr;

        switch(number) {
            case 1: node->setID("top-quest"); break;
            case 2: node->setID("middle-quest"); break;
            case 3: node->setID("bottom-quest"); break;
            default: node->setID(fmt::format("quest-{}", number)); break;
        }

        return node;
    }

    bool init() {
        if(!ChallengesPage::init()) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};
