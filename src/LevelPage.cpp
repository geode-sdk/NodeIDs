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
        if (auto levelButton = getChildOfType<CCMenuItemSpriteExtra>(levelMenu, 0)) {
            levelButton->setID("level-button");

            // why in gods name does this sprite house everything
            if (auto whiteSprite = getChildOfType<CCSprite>(levelButton, 0)) {
                whiteSprite->setID("white-sprite");

                if (auto scale9Sprite = getChildOfType<CCScale9Sprite>(whiteSprite, 0)) {
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

                if (auto controllerStartSprite = getChildOfType<CCSprite>(whiteSprite, 0)) {
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
    }

    bool init(GJGameLevel* level) {
        if (!LevelPage::init(level)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }

    void updateDynamicPage(GJGameLevel* level) {
        LevelPage::updateDynamicPage(level);

        // can't believe im bugfixing this game
        if (auto emptyMenu = getChildOfType<CCMenu>(this, 1); emptyMenu && emptyMenu->getChildrenCount() == 0) {
            emptyMenu->removeFromParent();
        }

        if (GameStatsManager::sharedState()->getStat("8") < level->m_requiredCoins) {
            setIDs(
                this->getChildByID("level-menu")
                    ->getChildByID("level-button")
                    ->getChildByID("white-sprite")
                    ->getChildByID("scale-9-sprite"),
                8,
                "lock-sprite",
                "secret-coin-icon",
                "secret-coin-label"
            );
        } else {
            setIDs(
                this->getChildByID("level-menu")
                    ->getChildByID("level-button")
                    ->getChildByID("white-sprite")
                    ->getChildByID("scale-9-sprite"),
                8,
                "orbs-icon",
                "orbs-label"
            );
        }

        // this is how updateDynamicPage itself does it
        if (level->m_levelID <= 0) {
            if (level->m_levelID == -2) {
                if (auto buttonMenu = getChildOfType<CCMenu>(this, 1)) {
                    buttonMenu->setID("button-menu");

                    if (auto towerButton = getChildOfType<CCMenuItemSpriteExtra>(buttonMenu, 0)) {
                        towerButton->setID("tower-button");

                        if (auto towerSprite = getChildOfType<CCSprite>(towerButton, 0)) {
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
                getChildOfType<CCLabelBMFont>(this, 4)->setID("coming-soon-label");

                if (auto buttonMenu = getChildOfType<CCMenu>(this, 1)) {
                    buttonMenu->setID("button-menu");

                    if (auto secretDoorButton = getChildOfType<CCMenuItemSpriteExtra>(buttonMenu, 0)) {
                        secretDoorButton->setID("secret-door-button");

                        getChildOfType<CCSprite>(secretDoorButton, 0)->setID("secret-door-sprite");
                    }
                }
            }
        }
    }
};
