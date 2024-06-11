#include <Geode/Bindings.hpp>
#include <Geode/modify/EndLevelLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

// this code sux but oh well
// maybe it should be in geode utils
// definitely should be in geode utils
// ok it is in geode utils now
// use it when we release beta 20

inline bool isSpriteFrameName(CCNode* node, const char* name) {
    auto cache = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name);
    if (!cache) return false;

    auto* texture = cache->getTexture();
    auto rect = cache->getRect();

    if (auto* spr = typeinfo_cast<CCSprite*>(node)) {
        if (spr->getTexture() == texture && spr->getTextureRect() == rect) {
            return true;
        }
    } else if (auto* btn = typeinfo_cast<CCMenuItemSprite*>(node)) {
        auto* img = btn->getNormalImage();
        if (auto* spr = typeinfo_cast<CCSprite*>(img)) {
            if (spr->getTexture() == texture && spr->getTextureRect() == rect) {
                return true;
            }
        }
    }
    return false;
}

inline CCNode* getChildBySpriteFrameName(CCNode* parent, const char* name) {
    for (auto child : CCArrayExt<CCNode*>(parent->getChildren())) {
        if (::isSpriteFrameName(static_cast<CCNode*>(child), name)) {
            return child;
        }
    }
    return nullptr;
}


$register_ids(EndLevelLayer) {
    m_mainLayer->setID("main-layer");
    if(auto hideMenu = setIDSafe(this, 1, "hide-layer-menu")) {
        setIDSafe(hideMenu, 0, "hide-button");
    }

    int idx = 0;
    setIDs(
        m_mainLayer,
        idx,
        "background",
        "hide-dropdown-menu",
        "chain-left",
        "chain-right"
    );
    idx += 4;

    if (auto levelTxt = ::getChildBySpriteFrameName(m_mainLayer, "GJ_levelComplete_001.png")) {
        levelTxt->setID("level-complete-text");
        idx += 1;
    }
    else if (auto practiceTxt = ::getChildBySpriteFrameName(m_mainLayer, "GJ_practiceComplete_001.png")) {
        practiceTxt->setID("practice-complete-text");
        idx += 1;
    }

    for (auto child : CCArrayExt<CCNode*>(m_mainLayer->getChildren())) {
        if (auto bmFont = typeinfo_cast<CCLabelBMFont*>(child)) {
            std::string_view view = bmFont->getString();

            if (view.starts_with("Attempts")) {
                bmFont->setID("attempts-label");
                idx += 1;
            }
            else if (view.starts_with("Jumps")) {
                bmFont->setID("jumps-label");
                idx += 1;
            }
            else if (view.starts_with("Time")) {
                bmFont->setID("time-label");
                idx += 1;
            }
            else if (view.starts_with("Points")) {
                bmFont->setID("points-label");
                idx += 1;
            }
        }
    }

    if (auto endText = typeinfo_cast<CCLabelBMFont*>(m_mainLayer->getChildren()->objectAtIndex(idx))) {
        endText->setID("end-text");
        idx += 1;
    }

    if (auto textArea = typeinfo_cast<TextArea*>(m_mainLayer->getChildren()->objectAtIndex(idx))) {
        textArea->setID("complete-message");
        idx += 1;
    }

    setIDs(
        m_mainLayer,
        idx,
        "button-menu"
    );
    idx += 1;

    auto menu = static_cast<CCMenu*>(m_mainLayer->getChildByID("button-menu"));

    setIDs(
        menu,
        0,
        "retry-button",
        "exit-button"
    );

    if (auto editButton = ::getChildBySpriteFrameName(menu, "GJ_editBtn_001.png")) {
        editButton->setID("edit-button");
    }
    if (auto leaderboardButton = ::getChildBySpriteFrameName(menu, "GJ_levelLeaderboardBtn_001.png")) {
        leaderboardButton->setID("leaderboard-button");
    }
    if (auto leaderboardButton = ::getChildBySpriteFrameName(menu, "GJ_restartCheckBtn_001.png")) {
        leaderboardButton->setID("practice-retry-button");
    }

    int currentCoin = 1;
    std::vector<CCPoint> coinPos;
    for (auto child : CCArrayExt<CCNode*>(m_mainLayer->getChildren())) {
        for (auto framename : {
            "secretCoin_b_01_001.png",
            "secretCoin_2_b_01_001.png"
        }) {
            if (::isSpriteFrameName(child, framename)) {
                child->setID(fmt::format("coin-{}-background", currentCoin));
                coinPos.push_back(child->getPosition());
                currentCoin += 1;
                idx += 1;
            }
        }
    }

    for (auto child : CCArrayExt<CCNode*>(m_mainLayer->getChildren())) {
        for (int i = 1; i < currentCoin; i++) {
            if (child->getID().empty() && child->getPosition() == coinPos[i - 1]) {
                child->setID(fmt::format("coin-{}-sprite", i));
            }
        }
    }

    for (auto child : CCArrayExt<CCNode*>(m_coinsToAnimate)) {
        for (int i = 1; i < currentCoin; i++) {
            if (child->getID().empty() && child->getPosition() == coinPos[i - 1]) {
                child->setID(fmt::format("coin-{}-sprite", i));
            }
        }
    }

    if (PlatformToolbox::isControllerConnected()) {
        setIDs(
            m_mainLayer,
            idx,
            "controller-retry-hint",
            "controller-exit-hint"
        );
        idx += 2;
    }
}

struct EndLevelLayerIDs : Modify<EndLevelLayerIDs, EndLevelLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("EndLevelLayer::customSetup", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set EndLevelLayer::customSetup hook priority, node IDs may not work properly");
        }
        if (!self.setHookPriority("EndLevelLayer::showLayer", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set EndLevelLayer::showLayer hook priority, node IDs may not work properly");
        }
    }

    void customSetup() {
        EndLevelLayer::customSetup();

        NodeIDs::get()->provide(this);
    }

    void showLayer(bool p0) {
        EndLevelLayer::showLayer(p0);

        for (auto child : CCArrayExt<CCNode*>(m_mainLayer->getChildren())) {
            if (auto star = ::getChildBySpriteFrameName(child, "GJ_bigStar_001.png")) {
                child->setID("star-container");
                star->setID("star-sprite");
                getChildOfType<CCLabelBMFont>(child, 0)->setID("star-label");
            }
            else if (auto moon = ::getChildBySpriteFrameName(child, "GJ_bigMoon_001.png")) {
                child->setID("moon-container");
                moon->setID("moon-sprite");
                getChildOfType<CCLabelBMFont>(child, 0)->setID("moon-label");
            }
            else if (auto orb = ::getChildBySpriteFrameName(child, "currencyOrbIcon_001.png")) {
                child->setID("orb-container");
                orb->setID("orb-sprite");
                getChildOfType<CCLabelBMFont>(child, 0)->setID("orb-label");
            }
            else if (auto diamond = ::getChildBySpriteFrameName(child, "GJ_bigDiamond_001.png")) {
                child->setID("diamond-container");
                diamond->setID("diamond-sprite");
                getChildOfType<CCLabelBMFont>(child, 0)->setID("diamond-label");
            }
        }
    }
};
