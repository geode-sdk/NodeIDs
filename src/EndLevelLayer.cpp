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
inline CCNode* getChildBySpriteFrameName(CCNode* parent, const char* name) {
    auto cache = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name);
    if (!cache) return nullptr;

    auto* texture = cache->getTexture();
    auto rect = cache->getRect();

    for (int i = 0; i < parent->getChildrenCount(); ++i) {
        auto* child = parent->getChildren()->objectAtIndex(i);
        if (auto* spr = typeinfo_cast<CCSprite*>(child)) {
            if (spr->getTexture() == texture && spr->getTextureRect() == rect) {
                return spr;
            }
        } else if (auto* btn = typeinfo_cast<CCMenuItemSprite*>(child)) {
            auto* img = btn->getNormalImage();
            if (auto* spr = typeinfo_cast<CCSprite*>(img)) {
                if (spr->getTexture() == texture && spr->getTextureRect() == rect) {
                    return btn;
                }
            }
        }
    }
    return nullptr;
}

namespace {
    void handleContainers(EndLevelLayer* self) {
        for (auto child : CCArrayExt<CCNode*>(self->m_mainLayer->getChildren())) {
            if (auto star = ::getChildBySpriteFrameName(child, "GJ_bigStar_001.png")) {
                child->setID("star-container");
                star->setID("star-sprite");
                getChildOfType<CCLabelBMFont>(child, 0)->setID("star-label");
            }
            else if (auto star = ::getChildBySpriteFrameName(child, "GJ_bigMoon_001.png")) {
                child->setID("moon-container");
                star->setID("moon-sprite");
                getChildOfType<CCLabelBMFont>(child, 0)->setID("moon-label");
            }
            else if (auto star = ::getChildBySpriteFrameName(child, "currencyOrbIcon_001.png")) {
                child->setID("orb-container");
                star->setID("orb-sprite");
                getChildOfType<CCLabelBMFont>(child, 0)->setID("orb-label");
            }
            else if (auto star = ::getChildBySpriteFrameName(child, "GJ_bigDiamond_001.png")) {
                child->setID("diamond-container");
                star->setID("diamond-sprite");
                getChildOfType<CCLabelBMFont>(child, 0)->setID("diamond-label");
            }
        }
    }
}

$register_ids(EndLevelLayer) {
    if (!m_mainLayer->getID().empty()) {
        handleContainers(this);
        return;
    }

    m_mainLayer->setID("main-layer");

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

    m_buttonMenu->setID("button-menu");
    idx += 1;

    setIDs(
        m_buttonMenu,
        0,
        "replay-button",
        "menu-button"
    );

    if (auto editButton = ::getChildBySpriteFrameName(m_buttonMenu, "GJ_editBtn_001.png")) {
        editButton->setID("edit-button");
    }
    if (auto leaderboardButton = ::getChildBySpriteFrameName(m_buttonMenu, "GJ_levelLeaderboardBtn_001.png")) {
        leaderboardButton->setID("leaderboard-button");
    }

    int currentCoin = 1;
    for (auto child : CCArrayExt<CCNode*>(m_mainLayer->getChildren())) {
        for (auto framename : {
            "secretCoin_b_01_001.png",
            "secretCoin_2_b_01_001.png",
            "secretCoinUI_001.png",
            "secretCoinUI2_001.png"
        }) {
            if (auto sprite = ::getChildBySpriteFrameName(m_buttonMenu, framename)) {
                sprite->setID(fmt::format("coin-{}-sprite", currentCoin));
                currentCoin += 1;
                idx += 1;
            }
        }
    }

    if (PlatformToolbox::isControllerConnected()) {
        setIDs(
            m_mainLayer,
            idx,
            "controller-replay-hint",
            "controller-menu-hint"
        );
        idx += 2;
    }
}

struct EndLevelLayerIDs : Modify<EndLevelLayerIDs, EndLevelLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("EndLevelLayer::customSetup", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set EndLevelLayer::customSetup hook priority, node IDs may not work properly");
        }
    }

    void customSetup() {
        EndLevelLayer::customSetup();

        NodeIDs::get()->provide(this);
    }

    void showLayer(bool p0) {
        EndLevelLayer::showLayer(p0);

        NodeIDs::get()->provide(this);
    }
};
