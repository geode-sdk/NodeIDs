#include <Geode/Geode.hpp>
#include <Geode/modify/LevelCell.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

struct LevelCellIDs : Modify<LevelCellIDs, LevelCell> {
    struct Fields {
        bool m_isLocal = false;
    };

    static void onModify(auto& self) {
        if (!self.setHookPriority("LevelCell::loadFromLevel", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set LevelCell::loadFromLevel hook priority, node IDs may not work properly");
        }
        if (!self.setHookPriority("LevelCell::loadCustomLevelCell", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set LevelCell::loadCustomLevelCell hook priority, node IDs may not work properly");
        }
        if (!self.setHookPriority("LevelCell::loadLocalLevelCell", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set LevelCell::loadLocalLevelCell hook priority, node IDs may not work properly");
        }
    }

    void loadFromLevel(GJGameLevel* level) {
        LevelCell::loadFromLevel(level);

        if(m_level->m_localOrSaved && !m_compactView) {
            m_toggler->setID("select-toggler");
        }
    }

    void loadCustomLevelCell() {
        LevelCell::loadCustomLevelCell();

        m_fields->m_isLocal = false;
        NodeIDs::get()->provide(this);
    }

    void loadLocalLevelCell() {
        LevelCell::loadLocalLevelCell();

        m_fields->m_isLocal = true;
        NodeIDs::get()->provide(this);
    }
};

// With how RobTop uses the cell it would be safe to only use loadFromLevel,
// however with mods using it, it is safer to have the IDs defined at the earlier stage already

$register_ids(LevelCell) {
    if(!m_level) return;

    m_mainLayer->setID("main-layer");
    m_mainMenu->setID("main-menu");

    if(reinterpret_cast<LevelCellIDs*>(this)->m_fields->m_isLocal) {
        //LevelCell::loadLocalLevelCell

        size_t labelOffset = 0;
        size_t buttonOffset = 0;
        size_t spriteOffset = 0;

        m_mainLayer->getChildByType<CCLabelBMFont>(labelOffset)->setID("level-name");
        labelOffset++;

        if(m_level->m_levelRev > 0) {
            m_mainLayer->getChildByType<CCLabelBMFont>(labelOffset)->setID("level-revision");
            labelOffset++;
        }

        m_mainMenu->getChildByType<CCMenuItemSpriteExtra>(buttonOffset)->setID("view-button");
        buttonOffset++;

        m_mainLayer->getChildByType<CCSprite>(spriteOffset)->setID("length-icon");
        spriteOffset++;

        m_mainLayer->getChildByType<CCLabelBMFont>(labelOffset)->setID("length-label");
        labelOffset++;

        m_mainLayer->getChildByType<CCSprite>(spriteOffset)->setID("song-icon");
        spriteOffset++;

        m_mainLayer->getChildByType<CCLabelBMFont>(labelOffset)->setID("song-label");
        labelOffset++;

        m_mainLayer->getChildByType<CCSprite>(spriteOffset)->setID("info-icon");
        spriteOffset++;

        m_mainLayer->getChildByType<CCLabelBMFont>(labelOffset)->setID("info-label");
        labelOffset++;

    } else {
        //LevelCell::loadCustomLevelCell
        size_t labelOffset = 0;
        size_t buttonOffset = 0;
        size_t spriteOffset = 0;

        if(m_compactView) {
            m_mainLayer->getChildByType<CCLabelBMFont>(labelOffset)->setID("level-place");
            labelOffset++;
        }

        m_mainLayer->getChildByType<CCLabelBMFont>(labelOffset)->setID("level-name");
        labelOffset++;

        m_mainMenu->getChildByType<CCMenuItemSpriteExtra>(buttonOffset)->setID("view-button");
        buttonOffset++;

        if(m_listType == BoomListType::Level4) {
            m_mainMenu->getChildByType<CCMenuItemSpriteExtra>(buttonOffset)->setID("flip-button");
            buttonOffset++;
            
            m_mainMenu->getChildByType<CCMenuItemSpriteExtra>(buttonOffset)->setID("down-button");
            buttonOffset++;
            
            m_mainMenu->getChildByType<CCMenuItemSpriteExtra>(buttonOffset)->setID("up-button");
            buttonOffset++;
            
            m_mainMenu->getChildByType<CCMenuItemSpriteExtra>(buttonOffset)->setID("delete-button");
            buttonOffset++;
        }

        m_mainMenu->getChildByType<CCMenuItemSpriteExtra>(buttonOffset)->setID("creator-name");
        buttonOffset++;

        m_mainLayer->getChildByType<CCLabelBMFont>(labelOffset)->setID("song-name");
        labelOffset++;

        auto MDLM = MusicDownloadManager::sharedState();
        auto songObj = MDLM->getSongInfoObject(m_level->m_songID);
        if(songObj && songObj->m_nongType == 1) {
            m_mainLayer->getChildByType<CCSprite>(spriteOffset)->setID("ncs-icon");
            spriteOffset++;
        }

        size_t containerSpriteOffset = 0;
        size_t containerLabelOffset = 0;
        //we can use label offset because nothing else has been made yet, the +1 is the CCMenu that contains all buttons
        auto container = m_mainLayer->getChildByType<CCNode>(labelOffset + spriteOffset + 1);
        if(container) {
            container->setID("difficulty-container");
            container->getChildByType<CCSprite>(containerSpriteOffset)->setID("difficulty-sprite");
            containerSpriteOffset++;

            if(m_level->m_stars > 0) {
                container->getChildByType<CCSprite>(containerSpriteOffset)->setID("stars-icon");
                containerSpriteOffset++;

                container->getChildByType<CCLabelBMFont>(containerLabelOffset)->setID("stars-label");
                containerLabelOffset++;
            }

            if(m_level->m_dailyID > 0) {
                container->getChildByType<CCSprite>(containerSpriteOffset)->setID("diamond-icon");
                containerSpriteOffset++;

                container->getChildByType<CCLabelBMFont>(containerLabelOffset)->setID("diamond-label");
                containerLabelOffset++;
            }
        }

        auto coins = m_level->m_coins > 3 ? 3 : m_level->m_coins;
        if(coins > 0 && (m_compactView || container)) {
            for(size_t i = 0; i < coins; i++) {
                if(auto sprite = (m_compactView ? m_mainLayer : container)->getChildByType<CCSprite>(m_compactView ? spriteOffset : containerSpriteOffset)) {
                    sprite->setID(fmt::format("coin-icon-{}", i + 1));
                    m_compactView ? spriteOffset++ : containerSpriteOffset++;
                }
            }
        }

        m_mainLayer->getChildByType<CCSprite>(spriteOffset)->setID("length-icon");
        spriteOffset++;

        m_mainLayer->getChildByType<CCSprite>(spriteOffset)->setID("downloads-icon");
        spriteOffset++;

        m_mainLayer->getChildByType<CCSprite>(spriteOffset)->setID("likes-icon");
        spriteOffset++;

        m_mainLayer->getChildByType<CCLabelBMFont>(labelOffset)->setID("length-label");
        labelOffset++;

        m_mainLayer->getChildByType<CCLabelBMFont>(labelOffset)->setID("downloads-label");
        labelOffset++;

        m_mainLayer->getChildByType<CCLabelBMFont>(labelOffset)->setID("likes-label");
        labelOffset++;

        if(m_level->m_stars > 1) {

            m_mainLayer->getChildByType<CCSprite>(spriteOffset)->setID("orbs-icon");
            spriteOffset++;

            m_mainLayer->getChildByType<CCLabelBMFont>(labelOffset)->setID("orbs-label");
            labelOffset++;

        }

        bool hasCompletedLevel = m_level->m_dailyID > 0 ? m_level->m_orbCompletion > 99 : GameStatsManager::sharedState()->hasCompletedLevel(m_level);
        auto savedLevel = m_level->m_dailyID > 0 ? GameLevelManager::sharedState()->getSavedDailyLevel(m_level->m_dailyID) : GameLevelManager::sharedState()->getSavedLevel(m_level->m_levelID);
        if (hasCompletedLevel) {
            m_mainLayer->getChildByType<CCSprite>(spriteOffset)->setID("completed-icon");
            spriteOffset++;
        } else if (savedLevel && savedLevel->m_normalPercent.value() != 0) {
            if (auto node = m_mainLayer->getChildByType<CCLabelBMFont>(labelOffset)) {
                node->setID("percentage-label");
                labelOffset++;
            }
        }

        if(m_level->m_originalLevel > 0) {
            m_mainLayer->getChildByType<CCSprite>(spriteOffset)->setID("copy-indicator");
            spriteOffset++;
        }
        if(m_level->m_objectCount > 40000) {
            m_mainLayer->getChildByType<CCSprite>(spriteOffset)->setID("high-object-indicator");
            spriteOffset++;
        }

    }
    
}
