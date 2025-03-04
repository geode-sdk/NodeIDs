#include <Geode/Geode.hpp>
#include <Geode/modify/TutorialLayer.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(TutorialLayer) {
    if (auto tutorialLayer = setIDSafe<CCLayer>(this, 0, "main-layer")) {
        setIDSafe<CCScale9Sprite>(tutorialLayer, 0, "background");
        if (auto tutorialDetails = setIDSafe<CCLayer>(tutorialLayer, 0, "tutorial-Layer")) {
            setIDSafe<CCSprite>(tutorialDetails, 0, "tutorial-image-01");
            setIDSafe<TextArea>(tutorialDetails, 0, "tutorial-text-01");
        }

        if (auto tutorialMenu = setIDSafe<CCMenu>(tutorialLayer, 0, "tutorial-menu")) {
            setIDs(
                tutorialMenu,
                0,
                "close-button",
                "next-button",
                "exit-button"
            );
        };
        setIDSafe<CCLabelBMFont>(tutorialLayer, 0, "tutorial-title-label");
    }
}

struct TutorialLayerIDs : Modify<TutorialLayerIDs, TutorialLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("TutorialLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set TutorialLayer::init hook priority, node IDs may not work properly");
        }
    }

    bool init() {
        if (!TutorialLayer::init()) return false;

        NodeIDs::get()->provide(this);
        return true;
    }

    void onNext(CCObject* sender) {
        TutorialLayer::onNext(sender);
        log::debug("{}", this->m_page);
        // auto details = m_tutorialLayer->getChildByID("tutorial-guide");

        if (auto spr = m_tutorialLayer->getChildByType<CCSprite>(0)) {
            spr->setID(fmt::format("tutorial-image-0{}", this->m_page).c_str());
        }

        if (auto txtArea= m_tutorialLayer->getChildByType<TextArea>(0)) {
            txtArea->setID(fmt::format("tutorial-text-0{}", this->m_page).c_str());
        }
    }
};