#include <Geode/Bindings.hpp>
#include <Geode/modify/FollowRewardPage.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(FollowRewardPage) {
    setIDs(
        m_mainLayer,
        0,
        "background",
        "bottom-left-art",
        "top-left-art",
        "top-right-art",
        "bottom-right-art",
        "title-label",
        "sub-title-label",
        "main-menu"
    );

    if (auto mainMenu = m_mainLayer->getChildByID("main-menu")) {
        setIDs(
            mainMenu,
            0,
            "close-button",
            "youtube-chest",
            "twitter-chest",
            "facebook-chest",
            "twitch-chest",
            "discord-chest",
            "reddit-chest",
            "spotlight-chest"
        );
    }
    
    auto gm = GameManager::get();
    auto children = this->m_mainLayer->getChildren();
    int index = 8;

    static_cast<CCNode *>(children->objectAtIndex(index))->setID("youtube-label");
    if (!gm->getUGV("22")) {
        index++;
        static_cast<CCNode *>(children->objectAtIndex(index))->setID("youtube-icon");
    }
    index++;

    static_cast<CCNode *>(children->objectAtIndex(index))->setID("twitter-label");
    if (!gm->getUGV("24")) {
        index++;
        static_cast<CCNode *>(children->objectAtIndex(index))->setID("twitter-icon");
    }
    index++;

    static_cast<CCNode *>(children->objectAtIndex(index))->setID("facebook-label");
    if (!gm->getUGV("23")) {
        index++;
        static_cast<CCNode *>(children->objectAtIndex(index))->setID("facebook-icon");
    }
    index++;

    static_cast<CCNode *>(children->objectAtIndex(index))->setID("twitch-label");
    if (!gm->getUGV("26")) {
        index++;
        static_cast<CCNode *>(children->objectAtIndex(index))->setID("twitch-icon");
    }
    index++;

    static_cast<CCNode *>(children->objectAtIndex(index))->setID("discord-label");
    if (!gm->getUGV("27")) {
        index++;
        static_cast<CCNode *>(children->objectAtIndex(index))->setID("discord-icon");
    }
    index++;

    static_cast<CCNode *>(children->objectAtIndex(index))->setID("reddit-label");
    if (!gm->getUGV("32")) {
        index++;
        static_cast<CCNode *>(children->objectAtIndex(index))->setID("reddit-icon");
    }
    index++;

    static_cast<CCNode *>(children->objectAtIndex(index))->setID("spotlight-label");
    if (!gm->getUGV("39")) {
        index++;
        static_cast<CCNode *>(children->objectAtIndex(index))->setID("spotlight-icon");
    }
}

struct FollowRewardPageIDs : Modify<FollowRewardPageIDs, FollowRewardPage> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("FollowRewardPage::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set FollowRewardPage::init hook priority, node IDs may not work properly");
        }
    }

    bool init() {
        if (!FollowRewardPage::init()) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};
