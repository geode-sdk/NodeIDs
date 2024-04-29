#include <Geode/Bindings.hpp>
#include <Geode/modify/LevelListLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(LevelListLayer) {
    setIDSafe<CCSprite>(this, 0, "background");
    
    setIDSafe<CCScale9Sprite>(this, 0, "list-title-input-bg");
    setIDSafe<CCTextInputNode>(this, 0, "list-title-input");
    
    setIDSafe<LoadingCircle>(this, 0, "loading-circle");
    
    setIDSafe<TextArea>(this, 0, "no-internet-label");
    
    if (!getChildByIDRecursive("list-title-input-bg") && !getChildByIDRecursive("list-title-input")) {
        setIDSafe<CCLabelBMFont>(this, 0, "title-label");
        setIDSafe<CCLabelBMFont>(this, 1, "progress-label");
        setIDSafe<CCLabelBMFont>(this, 2, "downloads-label");
        setIDSafe<CCLabelBMFont>(this, 3, "likes-label");
        setIDSafe<CCLabelBMFont>(this, 4, "diamonds-label");
    } else {
        if (!getChildByIDRecursive("list-title-input")) {
            setIDSafe<CCLabelBMFont>(this, 1, "progress-label");
            setIDSafe<CCLabelBMFont>(this, 0, "published-list-label");
        } else {
            setIDSafe<CCLabelBMFont>(this, 0, "progress-label");
        }
    }
    
    if (auto likesIcon = ::getChildBySpriteFrameName(this, "GJ_likesIcon_001.png")) {
        likesIcon->setID("likes-icon");
    }
    if (auto downloadsIcon = ::getChildBySpriteFrameName(this, "GJ_downloadsIcon_001.png")) {
        downloadsIcon->setID("downloads-icon");
    }
    if (auto diamondsIcon = ::getChildBySpriteFrameName(this, "GJ_diamondsIcon_001.png")) {
        diamondsIcon->setID("diamonds-icon");
    }
    if (auto theCorner = ::getChildBySpriteFrameName(this, "GJ_sideArt_001.png")) {
        if (theCorner->getAnchorPoint() == ccp(0.f, 0.f)) {
            theCorner->setID("bottom-left-corner");
        }
    }
    if (auto featuredIcon = ::getChildBySpriteFrameName(this, "GJ_featuredCoin_001.png")) {
        featuredIcon->setID("featured-icon");
    }
    
    if (auto mainMenu = setIDSafe<CCMenu>(this, 0, "main-menu")) {
        setIDSafe<CCMenuItemSpriteExtra>(mainMenu, 0, "back-menu");
        if (auto deleteButton = ::getChildBySpriteFrameName(mainMenu, "GJ_deleteBtn_001.png")) {
            deleteButton->setID("delete-button");
        }
        if (auto refreshButton = ::getChildBySpriteFrameName(mainMenu, "GJ_updateBtn_001.png")) {
            refreshButton->setID("refresh-button");
        }
        if (auto descButton = ::getChildBySpriteFrameName(mainMenu, "GJ_chatBtn_001.png")) {
            descButton->setID("desc-button");
        }
        if (auto infoButton = ::getChildBySpriteFrameName(mainMenu, "GJ_infoBtn_001.png")) {
            infoButton->setID("info-button");
        }
        if (auto editButton = ::getChildBySpriteFrameName(mainMenu, "GJ_editModeBtn_001.png")) {
            editButton->setID("edit-button");
        }
        if (auto copyButton = ::getChildBySpriteFrameName(mainMenu, "GJ_duplicateBtn_001.png")) {
            copyButton->setID("copy-button");
        }
        if (auto shareButton = ::getChildBySpriteFrameName(mainMenu, "GJ_shareBtn_001.png")) {
            shareButton->setID("share-button");
        }
        if (auto infoButton = ::getChildBySpriteFrameName(mainMenu, "GJ_infoIcon_001.png")) {
            infoButton->setID("info-icon");
        }
        if (auto likeButton = ::getChildBySpriteFrameName(mainMenu, "GJ_like2Btn_001.png")) {
            likeButton->setID("like-button");
        }
        if (auto likeButton = ::getChildBySpriteFrameName(mainMenu, "GJ_like2Btn2_001.png")) {
            likeButton->setID("like-button");
        }
        if (auto rateButton = ::getChildBySpriteFrameName(mainMenu, "GJ_plainBtn_001.png")) {
            rateButton->setID("rate-button");
        }
        if (auto favoriteButton = ::getChildBySpriteFrameName(mainMenu, "gj_heartOff_001.png")) {
            favoriteButton->setID("favorite-button");
        }
        if (auto favoriteButton = ::getChildBySpriteFrameName(mainMenu, "gj_heartOn_001.png")) {
            favoriteButton->setID("favorite-button");
        }
        auto mainMenuChildren = CCArrayExt<CCNode*>(mainMenu->getChildren());
        mainMenuChildren[1]->setID("creator-info-menu");
    }
    auto children = CCArrayExt<CCNode*>(getChildren());
    for (int i = 0; i < children.size(); i++) {
        auto theObject = typeinfo_cast<CCNode*>(children[i]);
        if (auto theSprite = typeinfo_cast<CCSprite*>(theObject)) {
            if (strcmp(theSprite->getID().c_str(), "bottom-left-corner") == 0) {
                typeinfo_cast<CCSprite*>(children[i + 1])->setID("bottom-right-corner");
            }
        } else if (auto ccLabelBMFont = typeinfo_cast<CCLabelBMFont*>(theObject)) {
            if (strcmp(ccLabelBMFont->getID().c_str(), "progress-label") == 0 && !getChildByIDRecursive("list-title-input-bg")) {
                typeinfo_cast<CCSprite*>(children[i - 1])->setID("progress-bar");
            }
        }
    }
    
    // needed a second forloop to tie up loose ends; making it part of a single forloop = more prone to crashes
    
    for (int i = 0; i < getChildrenCount(); i++) {
        auto theObject = typeinfo_cast<CCNode*>(children[i]);
        if (strcmp(theObject->getID().c_str(), "") == 0) {
            if (!getChildByIDRecursive("list-title-input-bg")) {
                theObject->setID("difficulty-sprite");
            } else {
                theObject->setID("progress-bar");
            }
        }
    }
}

struct LevelListLayerIDs : Modify<LevelListLayerIDs, LevelListLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("LevelListLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set LevelListLayer::init hook priority, node IDs may not work properly");
        }
    }

    bool init(GJLevelList* p0) {
        if (!LevelListLayer::init(p0)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};
