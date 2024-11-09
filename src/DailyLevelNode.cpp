// #include "AddIDs.hpp"
//TODO: FIX 2.207

#include <Geode/Geode.hpp>
#include <Geode/modify/DailyLevelNode.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

struct DailyLevelNodeIDs : Modify<DailyLevelNodeIDs, DailyLevelNode> {
    struct Fields {
        bool m_isNew;
    };

    static void onModify(auto& self) {
        if (!self.setHookPriority("DailyLevelNode::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set DailyLevelNode::init hook priority, node IDs may not work properly");
        }
    }

    bool init(GJGameLevel* level, DailyLevelPage* page, bool isNew) {
        if(!DailyLevelNode::init(level, page, isNew)) return false;

        m_fields->m_isNew = isNew;

        NodeIDs::get()->provide(this);

        return true;
    }
};

$register_ids(DailyLevelNode) {
    auto self = reinterpret_cast<DailyLevelNodeIDs*>(this);

    this->getChildByType<CCScale9Sprite>(0)->setID("background");

    if(m_level) {
        this->getChildByType<CCSprite>(0)->setID("crown-sprite");

        size_t labelOffset = 0;
        if(self->m_fields->m_isNew) {
            this->getChildByType<CCLabelBMFont>(0)->setID("new-label");
            labelOffset += 1;
        }

        size_t menuOffset = 0;
        if(m_level->m_orbCompletion > 99) {
            if (auto mainMenu = this->getChildByType<CCMenu>(0)) {
                mainMenu->setID("claim-menu");

                mainMenu->getChildByType<CCMenuItemSpriteExtra>(0)->setID("claim-button");

                menuOffset += 1;
            }
        }

        if (auto mainMenu = this->getChildByType<CCMenu>(0 + menuOffset)) {
            mainMenu->setID("skip-menu");

            mainMenu->getChildByType<CCMenuItemSpriteExtra>(0)->setID("skip-button");
        }

        this->getChildByType<CCLabelBMFont>(0 + labelOffset)->setID("bonus-label");
        if(m_page->m_type == GJTimedLevelType::Weekly) {
            //this->getChildByType<GJChestSprite>(0)->setID("chest-sprite");
        } else {
            this->getChildByType<CCLabelBMFont>(1 + labelOffset)->setID("bonus-number-label");
        }

        this->getChildByType<CCSprite>(1)->setID("bonus-sprite"); //this coincidentally matches the chest sprite as well
    } else {
        this->getChildByType<CCLabelBMFont>(0)->setID("time-label");
    }
}
