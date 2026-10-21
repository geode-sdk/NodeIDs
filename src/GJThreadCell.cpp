#include <Geode/Geode.hpp>

#if GEODE_COMP_GD_VERSION >= 22090

#include <Geode/modify/GJThreadCell.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(GJThreadCell) {
    m_mainLayer->setID("main-layer");

    auto menu = setIDSafe<CCMenu>(m_mainLayer, 0, "main-menu");

    std::vector<CCLabelBMFont*> chatLabels;
    for (auto child : CCArrayExt<CCNode*>(m_mainLayer->getChildren())) {
        if (child == menu) continue;

        if (typeinfo_cast<EmoteSprite*>(child)) {
            child->setID("thread-emote");
        }
        else if (typeinfo_cast<SimplePlayer*>(child)) {
            child->setID("player-icon");
        }
        else if (auto label = typeinfo_cast<CCLabelBMFont*>(child)) {
            if (label->m_sFntFile == "chatFont.fnt") chatLabels.push_back(label);
            else label->setID("name-label");
        }
        else if (typeinfo_cast<CCLayerColor*>(child)) {
            child->setID("select-highlight");
        }
        else if (isSpriteFrameName(child, "GJ_starsIcon_001.png")) {
            child->setID("star-icon");
        }
        else if (isSpriteFrameName(child, "GJ_musicOffBtn_001.png")) {
            child->setID("muted-icon");
        }
        else if (isSpriteFrameName(child, "d_ball_01_001.png")) {
            child->setID("unread-badge");
            setIDs(
                child,
                0,
                "unread-count-label",
                "unread-count-shadow-label"
            );
        }
        else if (typeinfo_cast<CCSprite*>(child)) {
            child->setID("mod-badge");
        }
    }

    if (!chatLabels.empty()) {
        chatLabels.back()->setID("date-label");
        if (chatLabels.size() > 1) chatLabels.front()->setID("status-label");
    }

    if (menu) {
        auto buttonCount = menu->getChildrenCount();
        int buttonIdx = 0;
        if (typeinfo_cast<InfoAlertButton*>(menu->getChildren()->objectAtIndex(0))) {
            setIDSafe(menu, buttonIdx++, "description-button");
            if (buttonCount >= 5) setIDSafe(menu, buttonIdx++, "members-button");
        }
        else if (buttonCount >= 4) {
            setIDSafe(menu, buttonIdx++, "name-button");
        }
        setIDs(
            menu,
            buttonIdx,
            "select-toggler",
            "options-button",
            "view-button"
        );
    }
}

struct GJThreadCellIDs : Modify<GJThreadCellIDs, GJThreadCell> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("GJThreadCell::loadFromThread", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set GJThreadCell::loadFromThread hook priority, node IDs may not work properly");
        }
    }

    void loadFromThread(GJMessageThread* thread) {
        GJThreadCell::loadFromThread(thread);

        NodeIDs::get()->provide(this);
    }
};

#endif
