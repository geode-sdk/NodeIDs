#include <Geode/Geode.hpp>
#include <Geode/binding/MoreOptionsLayer.hpp>
#include <Geode/modify/MoreOptionsLayer.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(MoreOptionsLayer) {
    m_mainLayer->setID("main-layer");

    setIDs(
        m_mainLayer,
        0,
        "background",
        "options-label",
        "togglers-menu",
        "gameplay-options-layer-1",
        "gameplay-options-layer-2",
        "practice-options-layer",
        "performance-options-layer",
        "audio-options-layer",
        "other-options-layer",
        "music-offset-label",
        "music-offset-background",
        "music-offset-input"
    );

    std::array<std::string, 10> gameplayMenu1NodeNames{
        "auto-retry", "enabled-faster-reset",
        "show-in-game-cursor", "lock-in-game-cursor",
        "hide-attempts", "flip-pause-button",
        "disable-portal-guide", "enable-orb-guide",
        "disable-orb-scale", "disable-trigger-orb-scale"
    };
    if (auto gameplayMenu1 = m_mainLayer->getChildByID("gameplay-options-layer-1")) {
        auto nodes = CCArrayExt<CCLabelBMFont*>(gameplayMenu1->getChildren());

        for (int i = 0; i < nodes.size(); i++) {
            nodes[i]->setID(gameplayMenu1NodeNames.at(i) + "-label");
        }
    }

    std::array<std::string, 10> gameplayMenu2NodeNames{
        "disable-explosion-shake", "disable-gravity-effect",
        "default-mini-icon", "switch-spider-teleport-color",
        "switch-dash-fire-color", "switch-wave-trail-color",
        "flip-2-player-controls", "always-limit-controls",
        "disable-thumbstick", "enable-quick-keys"
    };
    if (auto gameplayMenu2 = m_mainLayer->getChildByID("gameplay-options-layer-2")) {
        auto nodes = CCArrayExt<CCLabelBMFont*>(gameplayMenu2->getChildren());

        for (int i = 0; i < nodes.size(); i++) {
            nodes[i]->setID(gameplayMenu2NodeNames.at(i) + "-label");
        }
    }

    std::array<std::string, 8> practiceMenuNodeNames{
        "hide-practice-buttons", "hide-attempts",
        "enable-auto-checkpoints", "enable-quick-checkpoints",
        "enable-death-effect", "enable-normal-music-in-editor",
        "show-hitboxes", "disable-player-hitbox"
    };
    if (auto practiceMenu = m_mainLayer->getChildByID("practice-options-layer")) {
        auto nodes = CCArrayExt<CCLabelBMFont*>(practiceMenu->getChildren());

        for (int i = 0; i < nodes.size(); i++) {
            nodes[i]->setID(practiceMenuNodeNames.at(i) + "-label");
        }
    }

    std::array<std::string, 8> performanceMenuNodeNames{
        "increase-draw-capacity", "enable-low-detail",
        "disable-high-object-alert", "enable-extra-ldm",
        "increase-maximum-levels", "disable-level-saving",
        "save-gauntlets", "disable-shader-anti-aliasing"
    };
    if (auto performanceMenu = m_mainLayer->getChildByID("performance-options-layer")) {
        auto nodes = CCArrayExt<CCLabelBMFont*>(performanceMenu->getChildren());

        for (int i = 0; i < nodes.size(); i++) {
            nodes[i]->setID(performanceMenuNodeNames.at(i) + "-label");
        }
    }

    std::array<std::string, 5> audioMenuNodeNames{
        "change-custom-songs-location", "disable-song-alert",
        "no-song-limit", "reduce-quality",
        "audio-fix-01"
    };
    if (auto audioMenu = m_mainLayer->getChildByID("audio-options-layer")) {
        auto nodes = CCArrayExt<CCLabelBMFont*>(audioMenu->getChildren());

        for (int i = 0; i < nodes.size(); i++) {
            nodes[i]->setID(audioMenuNodeNames.at(i) + "-label");
        }
    }

    std::array<std::string, 10> otherMenuNodeNames{
        "more-comments", "load-comments",
        "new-completed-filter", "increase-local-levels-per-page",
        "manual-level-order", "percentage-decimals",
        "show-leaderboard-percentage", "do-not",
        "confirm-exit", "fast-menu"
    };
    if (auto otherMenu = m_mainLayer->getChildByID("other-options-layer")) {
        auto nodes = CCArrayExt<CCLabelBMFont*>(otherMenu->getChildren());

        for (int i = 0; i < nodes.size(); i++) {
            nodes[i]->setID(otherMenuNodeNames.at(i) + "-label");
        }
    }


    if (auto togglersMenu = m_mainLayer->getChildByID("togglers-menu")) {
        auto nodes = CCArrayExt<CCNode*>(togglersMenu->getChildren());
        std::size_t arrayIdx = 0;

        for (int i = 0; i < 20; i += 2) {
            nodes[i]->setID(gameplayMenu1NodeNames[arrayIdx] + "-toggler");
            nodes[i + 1]->setID(gameplayMenu1NodeNames[arrayIdx] + "-info");

            arrayIdx++;
        }

        arrayIdx = 0;
        for (int i = 20; i < 40; i += 2) {
            nodes[i]->setID(gameplayMenu2NodeNames[arrayIdx] + "-toggler");
            nodes[i + 1]->setID(gameplayMenu2NodeNames[arrayIdx] + "-info");

            arrayIdx++;
        }

        arrayIdx = 0;
        for (int i = 40; i < 56; i += 2) {
            nodes[i]->setID(practiceMenuNodeNames[arrayIdx] + "-toggler");
            nodes[i + 1]->setID(practiceMenuNodeNames[arrayIdx] + "-info");

            arrayIdx++;
        }

        arrayIdx = 0;
        for (int i = 56; i < 72; i += 2) {
            nodes[i]->setID(performanceMenuNodeNames[arrayIdx] + "-toggler");
            nodes[i + 1]->setID(performanceMenuNodeNames[arrayIdx] + "-info");

            arrayIdx++;
        }

        arrayIdx = 0;
        for (int i = 72; i < 82; i += 2) {
            nodes[i]->setID(audioMenuNodeNames[arrayIdx] + "-toggler");
            nodes[i + 1]->setID(audioMenuNodeNames[arrayIdx] + "-info");

            arrayIdx++;
        }

        arrayIdx = 0;
        for (int i = 82; i < 101; i += 2) {
            nodes[i]->setID(otherMenuNodeNames[arrayIdx] + "-toggler");
            nodes[i + 1]->setID(otherMenuNodeNames[arrayIdx] + "-info");

            arrayIdx++;
        }

        setIDs(
            togglersMenu,
            102,
            "saved-songs-button",
            "fmod-debug-button",
            "parental-controls-button",
            "close-button",
            "left-arrow-button",
            "right-arrow-button",
            "key-bindings-button"
        );
    }
}

struct MoreOptionsLayerIDs : Modify<MoreOptionsLayerIDs, MoreOptionsLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("MoreOptionsLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set MoreOptionsLayer::init hook priority, node IDs may not work properly");
        }
    }

    bool init() {
        if (!MoreOptionsLayer::init()) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};
