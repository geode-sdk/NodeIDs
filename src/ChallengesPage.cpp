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

    getChildOfType<cocos2d::extension::CCScale9Sprite>(m_mainLayer, 0)->setID("background");
    getChildOfType<LoadingCircle>(m_mainLayer, 0)->setID("loading-circle");

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

        topMenu->setID("top-left-menu");
        topMenu->setLayout(
            ColumnLayout::create()
                ->setAxisReverse(true)
                ->setAxisAlignment(AxisAlignment::End)
        );
        topMenu->setContentSize({ 60.f, 120.f });
        topMenu->setPositionY(
            topMenu->getPositionY() - 120.f / 2 + 
                topMenu->getChildByID("close-button")->getScaledContentSize().height / 2
        );
        topMenu->updateLayout();
        //topMenu->setPositionX(285);
    }
    getChildOfType<ChallengeNode>(m_mainLayer, 0)->setID("top-quest");
    getChildOfType<ChallengeNode>(m_mainLayer, 1)->setID("middle-quest");
    getChildOfType<ChallengeNode>(m_mainLayer, 2)->setID("bottom-quest");
    getChildOfType<cocos2d::CCLabelBMFont>(m_mainLayer, 0)->setID("new-quest-label");
    getChildOfType<cocos2d::CCLabelBMFont>(m_mainLayer, 1)->setID("top-quest-indicator");
    getChildOfType<cocos2d::CCLabelBMFont>(m_mainLayer, 2)->setID("middle-quest-indicator");
    getChildOfType<cocos2d::CCLabelBMFont>(m_mainLayer, 3)->setID("bottom-quest-indicator");

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
