#include <Geode/Geode.hpp>

#if GEODE_COMP_GD_VERSION >= 22090

#include <Geode/modify/ThreadViewPopup.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(ThreadViewPopup) {
    m_mainLayer->setID("main-layer");

    setIDs(
        m_mainLayer,
        0,
        "background",
        "title-label"
    );

    int idx = 2;
    auto children = m_mainLayer->getChildren();
    for (; idx < static_cast<int>(children->count()); idx++) {
        auto child = static_cast<CCNode*>(children->objectAtIndex(idx));
        if (typeinfo_cast<CCMenu*>(child)) break;

        if (typeinfo_cast<EmoteSprite*>(child)) {
            child->setID("title-emote");
        }
        else if (typeinfo_cast<CCLabelBMFont*>(child)) {
            child->setID("dm-status-label");
        }
        else if (typeinfo_cast<CCSprite*>(child)) {
            child->setID("mod-badge");
        }
    }

    setIDs(
        m_mainLayer,
        idx,
        "main-menu",
        "messages-bg",
        "messages-layer",
        "compose-bg",
        "char-count-label",
        "message-input",
        "lock-notice-label"
    );
    if (auto loadingCircle = m_mainLayer->getChildByType<LoadingCircle>(0)) {
        loadingCircle->setID("loading-circle");
    }

    auto buttonCount = m_buttonMenu->getChildrenCount();
    bool hasDescription = buttonCount >= 10;
    bool hasMembers = buttonCount >= 11;

    int buttonIdx = 0;
    setIDSafe(m_buttonMenu, buttonIdx++, "close-button");
    setIDSafe(m_buttonMenu, buttonIdx++, "options-button");
    if (hasDescription) setIDSafe(m_buttonMenu, buttonIdx++, "description-button");
    setIDSafe(m_buttonMenu, buttonIdx++, "refresh-button");
    setIDSafe(m_buttonMenu, buttonIdx++, "search-button");
    if (hasMembers) setIDSafe(m_buttonMenu, buttonIdx++, "members-button");
    setIDs(
        m_buttonMenu,
        buttonIdx,
        "share-button",
        "emote-button",
        "scroll-to-bottom-button",
        "send-button",
        "lock-info-button"
    );

    verifyIDSafe(m_buttonMenu, "main-menu");

    auto winSize = CCDirector::get()->getWinSize();

    auto topRightMenu = CCMenu::create();
    topRightMenu->setLayout(
        RowLayout::create()
            ->setGap(5.5f)
            ->setAxisAlignment(AxisAlignment::End)
            ->setAxisReverse(true)
            ->ignoreInvisibleChildren(false)
    );
    topRightMenu->setID("top-right-menu");
    topRightMenu->setAnchorPoint({ 1.f, 0.5f });
    topRightMenu->setPosition({ (winSize.width / 2) + 206.f, (winSize.height / 2) + 124.f });
    topRightMenu->setContentSize({ 153.f, 25.f });
    topRightMenu->setZOrder(10);
    m_mainLayer->addChild(topRightMenu);

    switchToMenu(m_buttonMenu->getChildByID("options-button"), topRightMenu);
    switchToMenu(m_buttonMenu->getChildByID("description-button"), topRightMenu);
    switchToMenu(m_buttonMenu->getChildByID("refresh-button"), topRightMenu);
    switchToMenu(m_buttonMenu->getChildByID("search-button"), topRightMenu);
    topRightMenu->updateLayout();

    auto topLeftMenu = CCMenu::create();
    topLeftMenu->setLayout(
        RowLayout::create()
            ->setAxisAlignment(AxisAlignment::Start)
            ->setAxisReverse(false)
    );
    topLeftMenu->setID("top-left-menu");
    topLeftMenu->setAnchorPoint({ 0.f, 0.5f });
    topLeftMenu->setPosition({ (winSize.width / 2) - 182.f, (winSize.height / 2) + 124.f });
    topLeftMenu->setContentSize({ 90.f, 28.f });
    topLeftMenu->setZOrder(10);
    m_mainLayer->addChild(topLeftMenu);

    switchToMenu(m_buttonMenu->getChildByID("members-button"), topLeftMenu);
    topLeftMenu->updateLayout();

    auto bottomLeftMenu = CCMenu::create();
    bottomLeftMenu->setLayout(
        RowLayout::create()
            ->setGap(8.5f)
            ->setAxisAlignment(AxisAlignment::Start)
            ->setAxisReverse(false)
    );
    bottomLeftMenu->setID("bottom-left-menu");
    bottomLeftMenu->setAnchorPoint({ 0.f, 0.5f });
    bottomLeftMenu->setPosition({ (winSize.width / 2) - 207.5f, (winSize.height / 2) - 123.f });
    bottomLeftMenu->setContentSize({ 50.f, 24.f });
    bottomLeftMenu->setZOrder(10);
    m_mainLayer->addChild(bottomLeftMenu);

    switchToMenu(m_buttonMenu->getChildByID("share-button"), bottomLeftMenu);
    switchToMenu(m_buttonMenu->getChildByID("emote-button"), bottomLeftMenu);
    bottomLeftMenu->updateLayout();

    handleTouchPriority(this);
}

struct ThreadViewPopupIDs : Modify<ThreadViewPopupIDs, ThreadViewPopup> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("ThreadViewPopup::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set ThreadViewPopup::init hook priority, node IDs may not work properly");
        }
    }

    bool init(GJMessageThread* thread) {
        if (!ThreadViewPopup::init(thread)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }

    void buildMemberButton() {
        ThreadViewPopup::buildMemberButton();

        if (!m_buttonMenu) return;

        CCMenuItemSpriteExtra* button = nullptr;
        for (auto item : CCArrayExt<CCMenuItemSpriteExtra*>(m_buttonMenu->getChildren())) {
            auto image = item->getNormalImage();
            auto label = image ? image->getChildByType<CCLabelBMFont>(0) : nullptr;
            if (label && std::string_view(label->getString()).find(" member") != std::string_view::npos) {
                button = item;
                break;
            }
        }
        if (!button) return;
        button->setID("members-button");

        if (auto topLeftMenu = m_mainLayer->getChildByID("top-left-menu")) {
            switchToMenu(button, topLeftMenu);
            topLeftMenu->updateLayout();
            handleTouchPriority(this);
        }
    }
};

#endif
