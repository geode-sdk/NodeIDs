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
#ifndef GEODE_IS_MACOS
        "practice-options-layer",
#endif
        "performance-options-layer",
        "audio-options-layer",
        "other-options-layer",
#ifdef GEODE_IS_MACOS
        "options-options-layer",
#endif
        "music-offset-label",
        "music-offset-background",
        "music-offset-input"
    );

#ifdef GEODE_IS_ANDROID
    std::array<std::string, 10> gameplayMenu1NodeNames{
        "auto-retry", "enable-faster-reset",
        "hide-attempts", "flip-pause-button",
        "disable-portal-guide", "enable-orb-guide",
        "disable-orb-scale", "disable-trigger-orb-scale",
        "disable-explosion-shake", "disable-gravity-effect"
    };
#elif defined(GEODE_IS_WINDOWS) || defined(GEODE_IS_MACOS)
    std::array<std::string, 10> gameplayMenu1NodeNames{
        "auto-retry", "enable-faster-reset",
        "show-in-game-cursor", "lock-in-game-cursor",
        "hide-attempts", "flip-pause-button",
        "disable-portal-guide", "enable-orb-guide",
        "disable-orb-scale", "disable-trigger-orb-scale"
    };
#endif
    if (auto gameplayMenu1 = m_mainLayer->getChildByID("gameplay-options-layer-1")) {
        auto nodes = CCArrayExt<CCLabelBMFont*>(gameplayMenu1->getChildren());

        for (int i = 0; i < nodes.size(); i++) {
            nodes[i]->setID(gameplayMenu1NodeNames.at(i) + "-label");
        }
    }

#ifdef GEODE_IS_ANDROID
    std::array<std::string, 6> gameplayMenu2NodeNames{
        "default-mini-icon", "switch-spider-teleport-color",
        "switch-dash-fire-color", "switch-wave-trail-color",
        "flip-2-player-controls", "always-limit-controls"
    };
#elif defined(GEODE_IS_WINDOWS) || defined(GEODE_IS_MACOS)
    std::array<std::string, 10> gameplayMenu2NodeNames{
        "disable-explosion-shake", "disable-gravity-effect",
        "default-mini-icon", "switch-spider-teleport-color",
        "switch-dash-fire-color", "switch-wave-trail-color",
        "flip-2-player-controls", "always-limit-controls",
        "disable-thumbstick", "enable-quick-keys"
    };
#endif
    if (auto gameplayMenu2 = m_mainLayer->getChildByID("gameplay-options-layer-2")) {
        auto nodes = CCArrayExt<CCLabelBMFont*>(gameplayMenu2->getChildren());

        for (int i = 0; i < nodes.size(); i++) {
            nodes[i]->setID(gameplayMenu2NodeNames.at(i) + "-label");
        }
    }

#ifdef GEODE_IS_ANDROID
    std::array<std::string, 7> practiceMenuNodeNames{
        "hide-attempts", "enable-auto-checkpoints",
        "enable-quick-checkpoints", "enable-death-effect",
        "enable-normal-music-in-editor", "show-hitboxes",
        "disable-player-hitbox"
    };
#elif defined(GEODE_IS_WINDOWS)
    std::array<std::string, 8> practiceMenuNodeNames{
        "hide-practice-buttons", "hide-attempts",
        "enable-auto-checkpoints", "enable-quick-checkpoints",
        "enable-death-effect", "enable-normal-music-in-editor",
        "show-hitboxes", "disable-player-hitbox"
    };
#elif defined(GEODE_IS_MACOS)
    std::array<std::string, 6> practiceMenuNodeNames{
        "hide-practice-buttons", "hide-attempts",
        "enable-auto-checkpoints", "enable-quick-checkpoints",
        "enable-death-effect", "enable-normal-music-in-editor"
    };
#endif
#ifndef GEODE_IS_MACOS
    if (auto practiceMenu = m_mainLayer->getChildByID("practice-options-layer")) {
        auto nodes = CCArrayExt<CCLabelBMFont*>(practiceMenu->getChildren());

        for (int i = 0; i < nodes.size(); i++) {
            nodes[i]->setID(practiceMenuNodeNames.at(i) + "-label");
        }
    }
#endif

#ifdef GEODE_IS_ANDROID
    std::array<std::string, 9> performanceMenuNodeNames{
        "enable-smooth-fix", "increase-draw-capacity",
        "enable-low-detail", "disable-high-object-alert",
        "enable-extra-ldm", "increase-maximum-levels",
        "disable-level-saving", "save-gauntlets",
        "disable-shader-anti-aliasing"
    };
#elif defined(GEODE_IS_WINDOWS)
    std::array<std::string, 8> performanceMenuNodeNames{
        "increase-draw-capacity", "enable-low-detail",
        "disable-high-object-alert", "enable-extra-ldm",
        "increase-maximum-levels", "disable-level-saving",
        "save-gauntlets", "disable-shader-anti-aliasing"
    };
#elif defined(GEODE_IS_MACOS)
    std::array<std::string, 6> performanceMenuNodeNames{
        "hide-practice-buttons", "hide-attempts",
        "enable-auto-checkpoints", "enable-quick-checkpoints",
        "enable-death-effect", "enable-normal-music-in-editor"
    };
#endif
    if (auto performanceMenu = m_mainLayer->getChildByID("performance-options-layer")) {
        auto nodes = CCArrayExt<CCLabelBMFont*>(performanceMenu->getChildren());

        for (int i = 0; i < nodes.size(); i++) {
            nodes[i]->setID(performanceMenuNodeNames.at(i) + "-label");
        }
    }

#ifdef GEODE_IS_ANDROID
    std::array<std::string, 4> audioMenuNodeNames{
        "disable-song-alert", "no-song-limit",
        "reduce-quality", "audio-fix-01"
    };
#elif defined(GEODE_IS_WINDOWS)
    std::array<std::string, 5> audioMenuNodeNames{
        "change-custom-songs-location", "disable-song-alert",
        "no-song-limit", "reduce-quality",
        "audio-fix-01"
    };
#elif defined(GEODE_IS_MACOS)
    // rob really messed up here
    std::array<std::string, 8> audioMenuNodeNames{
        "increase-draw-capacity", "enable-low-detail",
        "disable-high-object-alert", "enable-extra-ldm",
        "increase-maximum-levels", "disable-level-saving",
        "save-gauntlets", "disable-shader-anti-aliasing"
    };
#endif
    if (auto audioMenu = m_mainLayer->getChildByID("audio-options-layer")) {
        auto nodes = CCArrayExt<CCLabelBMFont*>(audioMenu->getChildren());

        for (int i = 0; i < nodes.size(); i++) {
            nodes[i]->setID(audioMenuNodeNames.at(i) + "-label");
        }
    }

#ifdef GEODE_IS_ANDROID
    std::array<std::string, 10> otherMenuNodeNames{
        "more-comments", "load-comments",
        "new-completed-filter", "increase-local-levels-per-page",
        "manual-level-order", "percentage-decimals",
        "show-leaderboard-percentage", "do-not",
        "confirm-exit", "fast-menu"
    };
#elif defined(GEODE_IS_WINDOWS)
    std::array<std::string, 10> otherMenuNodeNames{
        "more-comments", "load-comments",
        "new-completed-filter", "increase-local-levels-per-page",
        "manual-level-order", "percentage-decimals",
        "show-leaderboard-percentage", "do-not",
        "confirm-exit", "fast-menu"
    };
#elif defined(GEODE_IS_MACOS)
    std::array<std::string, 5> otherMenuNodeNames{
        "change-custom-songs-location", "disable-song-alert",
        "no-song-limit", "reduce-quality",
        "audio-fix-01"
    };
#endif
    if (auto otherMenu = m_mainLayer->getChildByID("other-options-layer")) {
        auto nodes = CCArrayExt<CCLabelBMFont*>(otherMenu->getChildren());

        for (int i = 0; i < nodes.size(); i++) {
            nodes[i]->setID(otherMenuNodeNames.at(i) + "-label");
        }
    }

#ifdef GEODE_IS_MACOS
    std::array<std::string, 8> optionsMenuNodeNames{
        "more-comments", "load-comments",
        "new-completed-filter", "increase-local-levels-per-page",
        "manual-level-order", "percentage-decimals",
        "show-leaderboard-percentage", "do-not"
    };

    if (auto optionsMenu = m_mainLayer->getChildByID("options-options-layer")) {
        auto nodes = CCArrayExt<CCLabelBMFont*>(optionsMenu->getChildren());

        for (int i = 0; i < nodes.size(); i++) {
            nodes[i]->setID(optionsMenuNodeNames.at(i) + "-label");
        }
    }
#endif


#ifdef GEODE_IS_ANDROID
    constexpr std::array<std::pair<int, int>, 6> pageIdxToObjectIdxStartEnd{
        std::make_pair(0, 20),  // 10 togglers * 2 (multiplied by 2 to account for the toggler and the info icon)
        std::make_pair(20, 32), // 6 * 2
        std::make_pair(32, 46), // 7 * 2
        std::make_pair(46, 64), // 9 * 2
        std::make_pair(64, 72), // 4 * 2
        std::make_pair(72, 91)  // 10 * 2 - 1 (because we are indexing by 2, in the last iteration, i+1 == 91, which is the last info icon)
    };
#elif defined(GEODE_IS_WINDOWS)
    constexpr std::array<std::pair<int, int>, 6> pageIdxToObjectIdxStartEnd{
        std::make_pair(0, 20),  // 10 * 2
        std::make_pair(20, 40), // 10 * 2
        std::make_pair(40, 56), // 8 * 2
        std::make_pair(56, 72), // 8 * 2
        std::make_pair(72, 82), // 5 * 2
        std::make_pair(82, 101) // 10 * 2 - 1
    };
#elif defined(GEODE_IS_MACOS)
    constexpr std::array<std::pair<int, int>, 6> pageIdxToObjectIdxStartEnd{
        std::make_pair(0, 20),  // 10 * 2
        std::make_pair(20, 40), // 10 * 2
        std::make_pair(40, 52), // 6 * 2
        std::make_pair(52, 68), // 8 * 2
        std::make_pair(68, 78), // 5 * 2
        std::make_pair(78, 93)  // 8 * 2 - 1
    };
#endif

    if (auto togglersMenu = m_mainLayer->getChildByID("togglers-menu")) {
        auto nodes = CCArrayExt<CCNode*>(togglersMenu->getChildren());
        std::size_t pageIdx = 0;
        std::size_t arrayIdx = 0;

        for (int i = pageIdxToObjectIdxStartEnd[pageIdx].first; i < pageIdxToObjectIdxStartEnd[pageIdx].second; i += 2) {
            nodes[i]->setID(gameplayMenu1NodeNames[arrayIdx] + "-toggler");
            nodes[i + 1]->setID(gameplayMenu1NodeNames[arrayIdx] + "-info");

            arrayIdx++;
        }

        pageIdx++;
        arrayIdx = 0;
        for (int i = pageIdxToObjectIdxStartEnd[pageIdx].first; i < pageIdxToObjectIdxStartEnd[pageIdx].second; i += 2) {
            nodes[i]->setID(gameplayMenu2NodeNames[arrayIdx] + "-toggler");
            nodes[i + 1]->setID(gameplayMenu2NodeNames[arrayIdx] + "-info");

            arrayIdx++;
        }

#ifndef GEODE_IS_MACOS
        pageIdx++;
        arrayIdx = 0;
        for (int i = pageIdxToObjectIdxStartEnd[pageIdx].first; i < pageIdxToObjectIdxStartEnd[pageIdx].second; i += 2) {
            nodes[i]->setID(practiceMenuNodeNames[arrayIdx] + "-toggler");
            nodes[i + 1]->setID(practiceMenuNodeNames[arrayIdx] + "-info");

            arrayIdx++;
        }
#endif

        pageIdx++;
        arrayIdx = 0;
        for (int i = pageIdxToObjectIdxStartEnd[pageIdx].first; i < pageIdxToObjectIdxStartEnd[pageIdx].second; i += 2) {
            nodes[i]->setID(performanceMenuNodeNames[arrayIdx] + "-toggler");
            nodes[i + 1]->setID(performanceMenuNodeNames[arrayIdx] + "-info");

            arrayIdx++;
        }

        pageIdx++;
        arrayIdx = 0;
        for (int i = pageIdxToObjectIdxStartEnd[pageIdx].first; i < pageIdxToObjectIdxStartEnd[pageIdx].second; i += 2) {
            nodes[i]->setID(audioMenuNodeNames[arrayIdx] + "-toggler");
            nodes[i + 1]->setID(audioMenuNodeNames[arrayIdx] + "-info");

            arrayIdx++;
        }

        pageIdx++;
        arrayIdx = 0;
        for (int i = pageIdxToObjectIdxStartEnd[pageIdx].first; i < pageIdxToObjectIdxStartEnd[pageIdx].second; i += 2) {
            nodes[i]->setID(otherMenuNodeNames[arrayIdx] + "-toggler");
            nodes[i + 1]->setID(otherMenuNodeNames[arrayIdx] + "-info");

            arrayIdx++;
        }

#ifdef GEODE_IS_MACOS
        pageIdx++;
        arrayIdx = 0;
        for (int i = pageIdxToObjectIdxStartEnd[pageIdx].first; i < pageIdxToObjectIdxStartEnd[pageIdx].second; i += 2) {
            nodes[i]->setID(optionsMenuNodeNames[arrayIdx] + "-toggler");
            nodes[i + 1]->setID(optionsMenuNodeNames[arrayIdx] + "-info");
        }
#endif

        setIDs(
            togglersMenu,
            pageIdxToObjectIdxStartEnd[pageIdx].second + 1,
            "saved-songs-button",
            "fmod-debug-button",
            "parental-control-button",
            "close-button",
            "left-arrow-button",
            "right-arrow-button"
#ifndef GEODE_IS_ANDROID // comma on new line
            , "key-bindings-button"
#endif
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
