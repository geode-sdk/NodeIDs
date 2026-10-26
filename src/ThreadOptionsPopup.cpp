#include <Geode/Geode.hpp>

#if GEODE_COMP_GD_VERSION >= 22090

#include <Geode/modify/ThreadOptionsPopup.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

std::array<std::pair<const char*, const char*>, 14> OPTION_BUTTONS = {{
    {"Report", "report-button"},
    {"Remove", "remove-button"},
    {"Lock Conversation", "lock-button"},
    {"Unlock Conversation", "lock-button"},
    {"View Profile", "view-profile-button"},
    {"Members", "members-button"},
    {"Rename", "rename-button"},
    {"Mute", "mute-button"},
    {"Unmute", "mute-button"},
    {"Pin", "pin-button"},
    {"Unpin", "pin-button"},
    {"Leave", "leave-button"},
    {"Clear", "clear-button"},
    {"Cancel Request", "cancel-request-button"},
}};

$register_ids(ThreadOptionsPopup) {
    m_mainLayer->setID("main-layer");

    setIDs(
        m_mainLayer,
        0,
        "background",
        "main-menu",
        "title-label"
    );

    for (auto child : CCArrayExt<CCNode*>(m_mainLayer->getChildren())) {
        if (!child->getID().empty()) continue;
        if (typeinfo_cast<CCLabelBMFont*>(child)) {
            child->setID("created-label");
        }
        else if (typeinfo_cast<CCSprite*>(child)) {
            child->setID("mod-badge");
        }
    }

    setIDSafe(m_buttonMenu, 0, "close-button");

    for (auto item : CCArrayExt<CCMenuItemSpriteExtra*>(m_buttonMenu->getChildren())) {
        if (!item->getID().empty()) continue;
        auto sprite = typeinfo_cast<ButtonSprite*>(item->getNormalImage());
        if (!sprite || !sprite->m_label) continue;
        std::string_view text = sprite->m_label->getString();
        for (auto& [label, id] : OPTION_BUTTONS) {
            if (text == label) {
                item->setID(id);
                break;
            }
        }
    }

    verifyIDSafe(m_buttonMenu, "main-menu");

    auto winSize = CCDirector::get()->getWinSize();

    auto centerMenu = CCMenu::create();
    centerMenu->setLayout(
        ColumnLayout::create()
            ->setGap(7.f)
            ->setAxisAlignment(AxisAlignment::Center)
            ->setAxisReverse(true)
    );
    centerMenu->setID("center-menu");
    centerMenu->setPosition({ winSize.width / 2, (winSize.height / 2) - 17.f });
    centerMenu->setContentSize({ 130.f, 167.f });
    centerMenu->setZOrder(10);
    m_mainLayer->addChild(centerMenu);

    std::vector<CCNode*> optionButtons;
    for (auto item : CCArrayExt<CCNode*>(m_buttonMenu->getChildren())) {
        if (item->getID() != "close-button") optionButtons.push_back(item);
    }
    for (auto item : optionButtons) {
        switchToMenu(item, centerMenu);
    }
    centerMenu->updateLayout();

    handleTouchPriority(this);
}

struct ThreadOptionsPopupIDs : Modify<ThreadOptionsPopupIDs, ThreadOptionsPopup> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("ThreadOptionsPopup::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set ThreadOptionsPopup::init hook priority, node IDs may not work properly");
        }
    }

    bool init(GJMessageThread* thread, ThreadViewPopup* viewPopup, bool modView) {
        if (!ThreadOptionsPopup::init(thread, viewPopup, modView)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};

#endif
