#include <Geode/Geode.hpp>
#include <Geode/modify/SetupSmartBlockLayer.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(SetupSmartBlockLayer) {
    if (auto smartBlockBody = setIDSafe<CCLayer>(this, 0, "main-layer")) {

        setIDSafe<CCScale9Sprite>(smartBlockBody, 0, "background");

        int lblOffset = 0;

        // sorry this code SUCKS. Gave up on setIDs because it just chooses at random :|
        setIDSafe<CCLabelBMFont>(smartBlockBody, lblOffset, "reference-only-label");
        lblOffset++;
        setIDSafe<CCLabelBMFont>(smartBlockBody, lblOffset, "allow-rotation-label");
        lblOffset++;
        setIDSafe<CCLabelBMFont>(smartBlockBody, lblOffset, "flip-x-label");
        lblOffset++;
        setIDSafe<CCLabelBMFont>(smartBlockBody, lblOffset, "flip-y-label");
        lblOffset++;
        setIDSafe<CCLabelBMFont>(smartBlockBody, lblOffset, "ignore-corners-label");
        lblOffset++;
        setIDSafe<CCLabelBMFont>(smartBlockBody, lblOffset, "nearby-as-reference-label");
        lblOffset++;
        setIDSafe<CCLabelBMFont>(smartBlockBody, lblOffset, "dont-delete-label");

        if (auto smartBlockMenu = setIDSafe<CCMenu>(smartBlockBody, 0, "button-menu")) {

            // sorry again, I just didnt care to spend an hour messing around with swapping text
            int btnOff = 0;
            setIDSafe<CCMenuItemSpriteExtra>(smartBlockMenu, btnOff, "back-button");
            btnOff++;
            setIDSafe<InfoAlertButton>(smartBlockMenu, btnOff, "info-button");
            setIDSafe<CCMenuItemSpriteExtra>(smartBlockMenu, btnOff, "create-button");
            btnOff++;
            setIDSafe<CCMenuItemSpriteExtra>(smartBlockMenu, btnOff, "template-button");
            btnOff++;
            setIDSafe<CCMenuItemSpriteExtra>(smartBlockMenu, btnOff, "special-button");
            btnOff++;
            setIDSafe<CCMenuItemSpriteExtra>(smartBlockMenu, btnOff, "browser-button");
            btnOff++;
            setIDSafe<CCMenuItemSpriteExtra>(smartBlockMenu, btnOff, "create-all-button");
            btnOff++;
            setIDSafe<CCMenuItemSpriteExtra>(smartBlockMenu, btnOff, "paste-template-button");

            btnOff = 0;

            setIDSafe<CCMenuItemToggler>(smartBlockMenu, btnOff, "reference-only-toggle");
            btnOff++;
            setIDSafe<CCMenuItemToggler>(smartBlockMenu, btnOff, "allow-rotation-toggle");
            btnOff++;
            setIDSafe<CCMenuItemToggler>(smartBlockMenu, btnOff, "flip-x-toggle");
            btnOff++;
            setIDSafe<CCMenuItemToggler>(smartBlockMenu, btnOff, "flip-y-toggle");
            btnOff++;
            setIDSafe<CCMenuItemToggler>(smartBlockMenu, btnOff, "ignore-corners-toggle");
            btnOff++;
            setIDSafe<CCMenuItemToggler>(smartBlockMenu, btnOff, "nearby-as-reference-toggle");
            btnOff++;
            setIDSafe<CCMenuItemToggler>(smartBlockMenu, btnOff, "dont-delete-toggle");
        };
        setIDSafe<CCLabelBMFont>(this, 0, "title-label");
    }
}

struct SetupSmartBlockLayerIDs : Modify<SetupSmartBlockLayerIDs, SetupSmartBlockLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("SetupSmartBlockLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set SetupSmartBlockLayer::init hook priority, node IDs may not work properly");
        }
    }

    bool init(SmartGameObject* object, CCArray* objects) {
        if (!SetupSmartBlockLayer::init(object, objects)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};