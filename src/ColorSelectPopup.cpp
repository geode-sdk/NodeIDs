#include <Geode/Geode.hpp>

#include <Geode/modify/ColorSelectPopup.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(ColorSelectPopup) {
    bool pauseMenu = this->m_colorAction != nullptr;
    bool newColorTrigger = this->m_newColorTrigger;
    bool backgroundTrigger = this->m_backgroundTrigger;

    setIDSafe<CCLabelBMFont>(this, 0, "copy-opacity-label");
    setIDSafe<CCLabelBMFont>(this, 1, "channel-id-label");
    setIDSafe<ConfigureHSVWidget>(this, 0, "legacy-hsv-widget");

    setIDSafe<CCScale9Sprite>(m_mainLayer, 0, "background");
    setIDSafe<CCLabelBMFont>(m_mainLayer, 0, "title-label");
    setIDSafe<CCSprite>(m_mainLayer, 0, "new-color-preview-sprite");
    setIDSafe<CCSprite>(m_mainLayer, 1, "old-color-preview-sprite");
    setIDSafe<CCControlColourPicker>(m_mainLayer, 0, "color-picker");

    auto menu = setIDSafe<CCMenu>(m_mainLayer, 0, "menu");
    if (menu) {
        setIDSafe<CCMenuItemSpriteExtra>(menu, 0, "ok-button");
        setIDSafe<CCMenuItemSpriteExtra>(menu, 1, "copy-button");
        setIDSafe<CCMenuItemSpriteExtra>(menu, 2, "paste-button");
        setIDSafe<CCMenuItemSpriteExtra>(menu, 3, "default-button");

        setIDSafe<CCMenuItemToggler>(menu, 0, "player-color-1-toggle");
        setIDSafe<CCMenuItemToggler>(menu, 1, "player-color-2-toggle");

        setIDSafe<InfoAlertButton>(menu, 0, "info-button");
    }

    if (pauseMenu) {
        setIDSafe<CCScale9Sprite>(m_mainLayer, 1, "channel-id-background");
        setIDSafe<CCScale9Sprite>(m_mainLayer, 2, "red-background");
        setIDSafe<CCScale9Sprite>(m_mainLayer, 3, "green-background");
        setIDSafe<CCScale9Sprite>(m_mainLayer, 4, "blue-background");
        setIDSafe<CCScale9Sprite>(m_mainLayer, 5, "hex-background");

        setIDSafe<CCLabelBMFont>(m_mainLayer, 1, "opacity-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 2, "player-color-1-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 3, "player-color-2-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 4, "blending-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 5, "copy-color-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 6, "legacy-hsv-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 7, "red-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 8, "green-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 9, "blue-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 10, "hex-label");

        setIDSafe<CCTextInputNode>(m_mainLayer, 0, "channel-id-input");
        setIDSafe<CCTextInputNode>(m_mainLayer, 1, "red-input");
        setIDSafe<CCTextInputNode>(m_mainLayer, 2, "green-input");
        setIDSafe<CCTextInputNode>(m_mainLayer, 3, "blue-input");
        setIDSafe<CCTextInputNode>(m_mainLayer, 4, "hex-input");

        setIDSafe<Slider>(m_mainLayer, 0, "opacity-slider");

        if (menu) {
            setIDSafe<CCMenuItemSpriteExtra>(menu, 4, "channel-id-prev-button");
            setIDSafe<CCMenuItemSpriteExtra>(menu, 5, "channel-id-next-button");
            setIDSafe<CCMenuItemSpriteExtra>(menu, 6, "special-channel-select-button");

            setIDSafe<CCMenuItemToggler>(menu, 2, "blending-toggle");
            setIDSafe<CCMenuItemToggler>(menu, 3, "copy-color-toggle");
            setIDSafe<CCMenuItemToggler>(menu, 4, "copy-opacity-toggle");
            setIDSafe<CCMenuItemToggler>(menu, 5, "legacy-hsv-toggle");
        }
    } else if (!newColorTrigger && backgroundTrigger) {
        setIDSafe<CCScale9Sprite>(m_mainLayer, 1, "fade-time-background");
        setIDSafe<CCScale9Sprite>(m_mainLayer, 2, "channel-id-background");
        setIDSafe<CCScale9Sprite>(m_mainLayer, 3, "red-background");
        setIDSafe<CCScale9Sprite>(m_mainLayer, 4, "green-background");
        setIDSafe<CCScale9Sprite>(m_mainLayer, 5, "blue-background");
        setIDSafe<CCScale9Sprite>(m_mainLayer, 6, "hex-background");

        setIDSafe<CCLabelBMFont>(m_mainLayer, 1, "fade-time-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 2, "opacity-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 3, "player-color-1-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 4, "player-color-2-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 5, "tint-ground-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 6, "blending-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 7, "copy-color-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 8, "touch-trigger-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 9, "spawn-trigger-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 10, "multi-trigger-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 11, "legacy-hsv-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 12, "red-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 13, "green-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 14, "blue-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 15, "hex-label");

        setIDSafe<CCTextInputNode>(m_mainLayer, 0, "fade-time-input");
        setIDSafe<CCTextInputNode>(m_mainLayer, 1, "channel-id-input");
        setIDSafe<CCTextInputNode>(m_mainLayer, 2, "red-input");
        setIDSafe<CCTextInputNode>(m_mainLayer, 3, "green-input");
        setIDSafe<CCTextInputNode>(m_mainLayer, 4, "blue-input");
        setIDSafe<CCTextInputNode>(m_mainLayer, 5, "hex-input");

        setIDSafe<Slider>(m_mainLayer, 0, "fade-time-slider");
        setIDSafe<Slider>(m_mainLayer, 1, "opacity-slider");

        if (menu) {
            setIDSafe<CCMenuItemSpriteExtra>(menu, 4, "channel-id-prev-button");
            setIDSafe<CCMenuItemSpriteExtra>(menu, 5, "channel-id-next-button");
            setIDSafe<CCMenuItemSpriteExtra>(menu, 6, "special-channel-select-button");

            setIDSafe<CCMenuItemToggler>(menu, 2, "tint-ground-toggle");
            setIDSafe<CCMenuItemToggler>(menu, 3, "blending-toggle");
            setIDSafe<CCMenuItemToggler>(menu, 4, "copy-color-toggle");
            setIDSafe<CCMenuItemToggler>(menu, 5, "touch-trigger-toggle");
            setIDSafe<CCMenuItemToggler>(menu, 6, "spawn-trigger-toggle");
            setIDSafe<CCMenuItemToggler>(menu, 7, "multi-trigger-toggle");
            setIDSafe<CCMenuItemToggler>(menu, 8, "copy-opacity-toggle");
            setIDSafe<CCMenuItemToggler>(menu, 9, "legacy-hsv-toggle");
        }
    } else if (!newColorTrigger) {
        setIDSafe<CCScale9Sprite>(m_mainLayer, 1, "fade-time-background");
        setIDSafe<CCScale9Sprite>(m_mainLayer, 2, "channel-id-background");
        setIDSafe<CCScale9Sprite>(m_mainLayer, 3, "red-background");
        setIDSafe<CCScale9Sprite>(m_mainLayer, 4, "green-background");
        setIDSafe<CCScale9Sprite>(m_mainLayer, 5, "blue-background");
        setIDSafe<CCScale9Sprite>(m_mainLayer, 6, "hex-background");

        setIDSafe<CCLabelBMFont>(m_mainLayer, 1, "fade-time-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 2, "opacity-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 3, "player-color-1-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 4, "player-color-2-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 5, "blending-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 6, "copy-color-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 7, "touch-trigger-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 8, "spawn-trigger-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 9, "multi-trigger-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 10, "legacy-hsv-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 11, "red-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 12, "green-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 13, "blue-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 14, "hex-label");

        setIDSafe<CCTextInputNode>(m_mainLayer, 0, "fade-time-input");
        setIDSafe<CCTextInputNode>(m_mainLayer, 1, "channel-id-input");
        setIDSafe<CCTextInputNode>(m_mainLayer, 2, "red-input");
        setIDSafe<CCTextInputNode>(m_mainLayer, 3, "green-input");
        setIDSafe<CCTextInputNode>(m_mainLayer, 4, "blue-input");
        setIDSafe<CCTextInputNode>(m_mainLayer, 5, "hex-input");

        setIDSafe<Slider>(m_mainLayer, 0, "fade-time-slider");
        setIDSafe<Slider>(m_mainLayer, 1, "opacity-slider");

        if (menu) {
            setIDSafe<CCMenuItemSpriteExtra>(menu, 4, "channel-id-prev-button");
            setIDSafe<CCMenuItemSpriteExtra>(menu, 5, "channel-id-next-button");
            setIDSafe<CCMenuItemSpriteExtra>(menu, 6, "special-channel-select-button");

            setIDSafe<CCMenuItemToggler>(menu, 2, "blending-toggle");
            setIDSafe<CCMenuItemToggler>(menu, 3, "copy-color-toggle");
            setIDSafe<CCMenuItemToggler>(menu, 4, "touch-trigger-toggle");
            setIDSafe<CCMenuItemToggler>(menu, 5, "spawn-trigger-toggle");
            setIDSafe<CCMenuItemToggler>(menu, 6, "multi-trigger-toggle");
            setIDSafe<CCMenuItemToggler>(menu, 7, "copy-opacity-toggle");
            setIDSafe<CCMenuItemToggler>(menu, 8, "legacy-hsv-toggle");
        }
    } else {
        setIDSafe<CCScale9Sprite>(m_mainLayer, 1, "fade-time-background");
        setIDSafe<CCScale9Sprite>(m_mainLayer, 2, "color-id-background");
        setIDSafe<CCScale9Sprite>(m_mainLayer, 3, "channel-id-background");
        setIDSafe<CCScale9Sprite>(m_mainLayer, 4, "red-background");
        setIDSafe<CCScale9Sprite>(m_mainLayer, 5, "green-background");
        setIDSafe<CCScale9Sprite>(m_mainLayer, 6, "blue-background");
        setIDSafe<CCScale9Sprite>(m_mainLayer, 7, "hex-background");

        setIDSafe<CCLabelBMFont>(m_mainLayer, 1, "fade-time-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 2, "opacity-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 3, "player-color-1-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 4, "player-color-2-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 5, "blending-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 6, "copy-color-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 7, "touch-trigger-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 8, "spawn-trigger-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 9, "multi-trigger-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 10, "legacy-hsv-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 11, "color-id-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 12, "red-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 13, "green-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 14, "blue-label");
        setIDSafe<CCLabelBMFont>(m_mainLayer, 15, "hex-label");

        setIDSafe<CCTextInputNode>(m_mainLayer, 0, "fade-time-input");
        setIDSafe<CCTextInputNode>(m_mainLayer, 1, "color-id-input");
        setIDSafe<CCTextInputNode>(m_mainLayer, 2, "channel-id-input");
        setIDSafe<CCTextInputNode>(m_mainLayer, 3, "red-input");
        setIDSafe<CCTextInputNode>(m_mainLayer, 4, "green-input");
        setIDSafe<CCTextInputNode>(m_mainLayer, 5, "blue-input");
        setIDSafe<CCTextInputNode>(m_mainLayer, 6, "hex-input");

        setIDSafe<Slider>(m_mainLayer, 0, "fade-time-slider");
        setIDSafe<Slider>(m_mainLayer, 1, "opacity-slider");

        if (menu) {
            setIDSafe<CCMenuItemSpriteExtra>(menu, 4, "special-color-select-button");
            setIDSafe<CCMenuItemSpriteExtra>(menu, 5, "color-id-prev-button");
            setIDSafe<CCMenuItemSpriteExtra>(menu, 6, "color-id-next-button");
            setIDSafe<CCMenuItemSpriteExtra>(menu, 7, "channel-id-prev-button");
            setIDSafe<CCMenuItemSpriteExtra>(menu, 8, "channel-id-next-button");
            setIDSafe<CCMenuItemSpriteExtra>(menu, 9, "special-channel-select-button");

            setIDSafe<CCMenuItemToggler>(menu, 2, "blending-toggle");
            setIDSafe<CCMenuItemToggler>(menu, 3, "copy-color-toggle");
            setIDSafe<CCMenuItemToggler>(menu, 4, "touch-trigger-toggle");
            setIDSafe<CCMenuItemToggler>(menu, 5, "spawn-trigger-toggle");
            setIDSafe<CCMenuItemToggler>(menu, 6, "multi-trigger-toggle");
            setIDSafe<CCMenuItemToggler>(menu, 7, "copy-opacity-toggle");
            setIDSafe<CCMenuItemToggler>(menu, 8, "legacy-hsv-toggle");
        }
    }
}

struct ColorSelectPopupIDs : Modify<ColorSelectPopupIDs, ColorSelectPopup> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("ColorSelectPopup::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set ColorSelectPopup::init hook priority, node IDs may not work properly");
        }
    }

    bool init(EffectGameObject* object, CCArray* objects, ColorAction* action) {
        if (!ColorSelectPopup::init(object, objects, action)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};