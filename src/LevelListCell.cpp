#include <Geode/Bindings.hpp>
#include <Geode/modify/LevelListCell.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(LevelListCell) {
    setIDSafe<CCLayerColor>(this, 0, "background");
    
    if (auto mainLayer = setIDSafe<CCLayer>(this, 1, "main-layer")) {
        if (auto mainMenu = setIDSafe<CCMenu>(mainLayer, 0, "main-menu")) {
            setIDSafe<CCMenuItemSpriteExtra>(mainMenu, 0, "view-button");
            setIDSafe<CCMenuItemSpriteExtra>(mainMenu, 1, "creator-name");
            setIDSafe<CCMenuItemSpriteExtra>(mainMenu, 2, "info-button");
            if (auto downloadsIcon = ::getChildBySpriteFrameName(mainLayer, "GJ_downloadsIcon_001.png")) {
                downloadsIcon->setID("downloads-icon");
            }
            if (auto likesIcon = ::getChildBySpriteFrameName(mainLayer, "GJ_likesIcon_001.png")) {
                likesIcon->setID("likes-icon");
            }
            if (auto completionIcon = ::getChildBySpriteFrameName(mainLayer, "GJ_completesIcon_001.png")) {
                completionIcon->setID("completion-icon");
            }
            if (auto diamondIcon = ::getChildBySpriteFrameName(mainLayer, "diamond_small01_001.png")) {
                diamondIcon->setID("diamond-icon");
                setIDSafe<CCLabelBMFont>(mainLayer, 0, "diamond-label");
                setIDSafe<CCLabelBMFont>(mainLayer, 1, "list-name-label");
                setIDSafe<CCLabelBMFont>(mainLayer, 2, "progress-label");
                setIDSafe<CCLabelBMFont>(mainLayer, 3, "downloads-label");
                setIDSafe<CCLabelBMFont>(mainLayer, 4, "likes-label");
                setIDSafe<CCLabelBMFont>(mainLayer, 5, "completion-label");
            } else {
                setIDSafe<CCLabelBMFont>(mainLayer, 0, "list-name-label");
                setIDSafe<CCLabelBMFont>(mainLayer, 1, "progress-label");
                setIDSafe<CCLabelBMFont>(mainLayer, 2, "downloads-label");
                setIDSafe<CCLabelBMFont>(mainLayer, 3, "likes-label");
            }
            auto mainLayerChildren = CCArrayExt<CCNode*>(mainLayer->getChildren());
            mainLayerChildren[0]->setID("difficulty-sprite");
            mainLayerChildren[3]->setID("progress-bar");
            if (getChildByIDRecursive("downloads-icon") && getChildByIDRecursive("likes-icon")) {
                if (getChildByIDRecursive("diamond-icon")) {
                    mainLayerChildren[3]->setID("featured-icon");
                    mainLayerChildren[6]->setID("progress-bar");
                    if (getChildByIDRecursive("completion-icon")) {
                        mainLayerChildren[13]->setID("progress-bar-diamond");
                    }
                }
            } else {
                mainLayerChildren[5]->setID("info-sprite");
                if (auto theChild = typeinfo_cast<CCLabelBMFont*>(mainLayerChildren[6])) {
                    if (strcmp(theChild->getID().c_str(), "downloads-label") == 0) {
                        if (strcmp(theChild->getString(), "Unpublished") == 0) {
                            theChild->setID("unpublished-label");
                        } else if (strcmp(theChild->getString(), "Uploaded") == 0) {
                            theChild->setID("uploaded-label");
                        } else {
                            theChild->setID("unknown-info-label");
                        }
                    }
                }
            }
        }
    }
}

struct LevelListCellIDs : Modify<LevelListCellIDs, LevelListCell> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("LevelListCell::loadFromList", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set LevelListCell::loadFromList hook priority, node IDs may not work properly");
        }
    }

    void loadFromList(GJLevelList* p0) {
        LevelListCell::loadFromList(p0);

        NodeIDs::get()->provide(this);
    }
};