#include <Geode/Geode.hpp>
#include <Geode/binding/LevelPage.hpp>
#include <Geode/modify/LevelPage.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(LevelPage) {
    setIDs(
        this,
        0,
        "level-menu",
        "normal-progress-bar",
        "practice-progress-bar",
        "normal-progress-label",
        "practice-progress-label",
        "normal-mode-label",
        "practice-mode-label"
    );

    if (auto levelMenu = this->getChildByID("level-menu")) {
        if (auto levelButton = levelMenu->getChildByType<CCMenuItemSpriteExtra>(0)) {
            levelButton->setID("level-button");

            // why in gods name does this sprite house everything
            if (auto whiteSprite = levelButton->getChildByType<CCSprite>(0)) {
                whiteSprite->setID("white-sprite");

                if (auto scale9Sprite = whiteSprite->getChildByType<CCScale9Sprite>(0)) {
                    scale9Sprite->setID("scale-9-sprite");

                    setIDs(
                        scale9Sprite,
                        0,
                        "background",
                        "level-name-label",
                        "difficulty-sprite",
                        "stars-icon",
                        "stars-label",
                        "secret-coin-icon-1",
                        "secret-coin-icon-2",
                        "secret-coin-icon-3"
                    );
                }

                if (auto controllerStartSprite = whiteSprite->getChildByType<CCSprite>(0)) {
                    controllerStartSprite->setID("controller-start-sprite");
                }
            }
        }
    }
}

struct LevelPageIDs : Modify<LevelPageIDs, LevelPage> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("LevelPage::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set LevelPage::init hook priority, node IDs may not work properly");
        }

        if (!self.setHookPriority("LevelPage::updateDynamicPage", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set LevelPage::updateDynamicPage hook priority, node IDs may not work properly");
        }

        if (!self.setHookPriority("LevelPage::addSecretDoor", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set LevelPage::addSecretDoor hook priority, node IDs may not work properly");
        }

        if (!self.setHookPriority("LevelPage::addSecretCoin", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set LevelPage::addSecretCoin hook priority, node IDs may not work properly");
        }
    }

    void printTooSmallError(int expected) {
        log::warn("m_dynamicObjects is too small (expected {}, got {}), node IDs will be incorrect!", expected, m_dynamicObjects->count());
    }

    bool init(GJGameLevel* level) {
        if (!LevelPage::init(level)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }

    void addSecretDoor() {
        LevelPage::addSecretDoor();

        //door is not unlocked
        if(!GameManager::sharedState()->getUGV("6")) return;

        if(m_dynamicObjects->count() < 2) {
            return printTooSmallError(2);
        }

        auto secretDoorButton = static_cast<CCNode*>(m_dynamicObjects->objectAtIndex(m_dynamicObjects->count() - 2));
        secretDoorButton->setID("secret-door-button");

        if (auto secretDoorSprite = secretDoorButton->getChildByType<CCSprite>(0)) {
            secretDoorSprite->setID("secret-door-sprite");

            if(secretDoorSprite != m_dynamicObjects->lastObject()) {
                log::warn("secretDoorSprite is not the last object in m_dynamicObjects, node IDs might be incorrect!");
            }
        }

        if(auto parent = secretDoorButton->getParent()) {
            parent->setID("button-menu");

            //bugfix for empty menu leftover bug
            m_dynamicObjects->addObject(parent);
        }
    }

    void addSecretCoin() {
        LevelPage::addSecretCoin();

        if(auto coin = this->m_coinObject) coin->setID("secret-coin");
    }

    void updateDynamicPage(GJGameLevel* level) {
        LevelPage::updateDynamicPage(level);

        size_t offset = 0;

        // this is how updateDynamicPage itself does it
        if (level->m_levelID <= 0) {
            if (level->m_levelID == -2) {
                if(m_dynamicObjects->count() < 1) {
                    return printTooSmallError(1);
                }

                static_cast<CCNode*>(m_dynamicObjects->objectAtIndex(offset++))->setID("button-menu");
                if (auto buttonMenu = getChildByID("button-menu")) {
                    buttonMenu->setID("button-menu");

                    if (auto towerButton = buttonMenu->getChildByType<CCMenuItemSpriteExtra>(0)) {
                        towerButton->setID("tower-button");

                        if (auto towerSprite = towerButton->getChildByType<CCSprite>(0)) {
                            towerSprite->setID("tower-sprite");

                            setIDs(
                                towerSprite,
                                0,
                                "the-tower-sprite",
                                "square-particle-system",
                                "glow-particle-system",
                                "skull-particle-system"
                            );
                        }
                    }
                }
            } else {
                if(m_dynamicObjects->count() < 1) {
                    return printTooSmallError(1);
                }

                static_cast<CCNode*>(m_dynamicObjects->objectAtIndex(offset++))->setID("coming-soon-label");

                //door impld in addSecretDoor
            }
        } else {
            if (GameStatsManager::sharedState()->getStat("8") < level->m_requiredCoins) {
                if(m_dynamicObjects->count() < 3) {
                    return printTooSmallError(3);
                }

                static_cast<CCNode*>(m_dynamicObjects->objectAtIndex(offset++))->setID("lock-sprite");
                static_cast<CCNode*>(m_dynamicObjects->objectAtIndex(offset++))->setID("secret-coin-icon");
                static_cast<CCNode*>(m_dynamicObjects->objectAtIndex(offset++))->setID("secret-coin-label");
            } else {
                if(m_dynamicObjects->count() < 2) {
                    return printTooSmallError(2);
                    return;
                }

                static_cast<CCNode*>(m_dynamicObjects->objectAtIndex(offset++))->setID("orbs-icon");
                static_cast<CCNode*>(m_dynamicObjects->objectAtIndex(offset++))->setID("orbs-label");
            }
        }
    }
};
