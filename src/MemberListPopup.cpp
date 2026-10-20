#include <Geode/Geode.hpp>

#if GEODE_COMP_GD_VERSION >= 22090

#include <Geode/modify/MemberListPopup.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(MemberListPopup) {
    m_mainLayer->setID("main-layer");

    setIDs(
        m_mainLayer,
        0,
        "background",
        "main-menu",
        "title-label",
        "status-label",
        "scroll-bg",
        "scroll-layer",
        "member-count-label"
    );
    if (auto loadingCircle = m_mainLayer->getChildByType<LoadingCircle>(0)) {
        loadingCircle->setID("loading-circle");
    }

    setIDs(
        m_buttonMenu,
        0,
        "close-button",
        "prev-page-button",
        "next-page-button",
        "add-member-button"
    );

    verifyIDSafe(m_buttonMenu, "main-menu");

    auto winSize = CCDirector::get()->getWinSize();
    auto policyBtn = m_buttonMenu->getChildByID("add-policy-button");

    auto bottomMenu = CCMenu::create();
    bottomMenu->setLayout(
        RowLayout::create()
            ->setGap(50.f)
            ->setAxisAlignment(AxisAlignment::Center)
            ->setAxisReverse(false)
            ->ignoreInvisibleChildren(false)
    );
    bottomMenu->setID("bottom-menu");
    bottomMenu->setPosition({ (winSize.width / 2) + (policyBtn ? 13.f : 0.f), (winSize.height / 2) - 106.f });
    bottomMenu->setContentSize({ 230.f, 26.f });
    bottomMenu->setZOrder(10);
    bottomMenu->setTouchPriority(CCTouchDispatcher::get()->getTargetPrio() - 1);
    m_mainLayer->addChild(bottomMenu);

    switchToMenu(m_buttonMenu->getChildByID("add-member-button"), bottomMenu);
    switchToMenu(policyBtn, bottomMenu);
    bottomMenu->updateLayout();
}

struct MemberListPopupIDs : Modify<MemberListPopupIDs, MemberListPopup> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("MemberListPopup::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set MemberListPopup::init hook priority, node IDs may not work properly");
        }
    }

    bool init(GJMessageThread* thread, ThreadViewPopup* viewPopup, bool modView) {
        if (!MemberListPopup::init(thread, viewPopup, modView)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }

    void refreshPolicyBtn() {
        MemberListPopup::refreshPolicyBtn();

        if (!m_buttonMenu) return;

        CCNode* policyButton = nullptr;
        for (auto item : CCArrayExt<CCMenuItemSpriteExtra*>(m_buttonMenu->getChildren())) {
            auto sprite = typeinfo_cast<ButtonSprite*>(item->getNormalImage());
            if (sprite && sprite->m_label && std::string_view(sprite->m_label->getString()).starts_with("Adds:")) {
                policyButton = item;
                break;
            }
        }
        if (!policyButton) return;
        policyButton->setID("add-policy-button");

        if (auto bottomMenu = m_mainLayer->getChildByID("bottom-menu")) {
            switchToMenu(policyButton, bottomMenu);
            bottomMenu->updateLayout();
        }
    }
};

#endif
