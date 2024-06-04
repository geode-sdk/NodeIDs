//TODO: the whole thing for mac
//TODO: the whole thing for android

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
        "visual-options-layer-1",
        "visual-options-layer-2",
        "practice-options-layer",
        "performance-options-layer",
        "audio-options-layer",
        "other-options-layer",
        "music-offset-label",
        "music-offset-background",
        "music-offset-input"
    );

    std::vector<int> options;

    if(auto togglersMenu = m_mainLayer->getChildByID("togglers-menu")) {
        size_t i = 0;
        for(auto child : CCArrayExt<CCNode*>(m_mainLayer->getChildByID("togglers-menu")->getChildren())) {
            if(i % 2 == 0) options.push_back(child->getTag());

            child->setID(fmt::format("option-{}-{}", child->getTag(), (i++)%2==0 ? "toggler" : "info"));
        }

        setIDs(
            togglersMenu,
            #ifdef GEODE_IS_ANDROID
                togglersMenu->getChildrenCount() - 6,
            #else
                togglersMenu->getChildrenCount() - 7,
            #endif
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

    const auto firstLayer = "gameplay-options-layer-1";
    const auto lastLayer = "other-options-layer";

    bool hitFirstChild = false;
    auto optionsIter = options.begin();

    for(auto child : CCArrayExt<CCNode*>(m_mainLayer->getChildren())) {
        if(!hitFirstChild && child->getID() != firstLayer) continue;
        hitFirstChild = true;

        for(auto label : CCArrayExt<CCLabelBMFont*>(child->getChildren())) {
            label->setID(fmt::format("option-{}-label", *(optionsIter++)));
        }
        
        if(child->getID() == lastLayer) break;
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
