#include <Geode/Bindings.hpp>
#include <Geode/Enums.hpp>
#include <Geode/modify/GJScaleControl.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

static CCMenu* createInputContainer(GJScaleControl* self, CCLabelBMFont* label, Slider* slider, CCTextInputNode* input, CCMenuItemSpriteExtra* button, ZStringView ID) {
    auto container = detachAndCreateMenu(self, fmt::format("{}-container", ID).c_str(), 
        nullptr,
        slider,
        label,
        input,
        button
    );

    label->setID(fmt::format("scale-label", ID));
    slider->setID(fmt::format("scale-slider", ID));
    input->setID(fmt::format("scale-input", ID));
    button->setID(fmt::format("refresh-button", ID));

    label->setPosition(label->getPosition() - container->getContentSize());
    slider->setPosition(slider->getPosition() - container->getContentSize());
    input->setPosition(input->getPosition() - container->getContentSize());
    button->setPosition(button->getPosition() - container->getContentSize());

    container->setAnchorPoint({0.5f, 0.f});
    container->setContentSize({170.f, 60.f});

    auto offset = CCPoint{container->getContentWidth() / 2.f, 18.f};

    label->setPosition(label->getPosition() + offset);
    slider->setPosition(slider->getPosition() + offset);
    input->setPosition(input->getPosition() + offset);
    button->setPosition(button->getPosition() + offset);

    return container;
}

$register_ids(GJScaleControl) {
    ignoreAnchorPointForPosition(false);
    setContentSize({0.f, 0.f});

    createInputContainer(this, m_scaleLabel, m_sliderXY, m_scaleInput, m_applyScaleButton, "scale-xy");
    createInputContainer(this, m_scaleXLabel, m_sliderX, m_scaleXInput, m_applyScaleXButton, "scale-x");
    createInputContainer(this, m_scaleYLabel, m_sliderY, m_scaleYInput, m_applyScaleYButton, "scale-y");

    auto lockMenu = setIDSafe<CCMenu>(this, 0, "lock-position-menu");
    if (lockMenu) {
        lockMenu->ignoreAnchorPointForPosition(false);
        lockMenu->setLayout(SimpleRowLayout::create()
            ->setGap(5.f)
            ->setMainAxisScaling(AxisScaling::Fit)
            ->setCrossAxisScaling(AxisScaling::Fit)
        );

        lockMenu->updateLayout();
    }

    m_scaleLockButton->setID("lock-position-toggle");
    m_controlMenu->setID("control-menu");
}

struct GJScaleControlIDs : Modify<GJScaleControlIDs, GJScaleControl> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("GJScaleControl::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set GJScaleControl::init hook priority, node IDs may not work properly");
        }
        if (!self.setHookPriority("GJScaleControl::loadValues", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set GJScaleControl::loadValues hook priority, node IDs may not work properly");
        }
    }

    bool init() {
        if (!GJScaleControl::init()) return false;

        NodeIDs::get()->provide(this);

        return true;
    }

    void loadValues(GameObject* object, cocos2d::CCArray* objects, std::unordered_map<int, GameObjectEditorState>& editorStates) {
        GJScaleControl::loadValues(object, objects, editorStates);

        bool split = m_senderTag == 46;

        auto scaleXY = this->getChildByID("scale-xy-container");
        if (scaleXY) scaleXY->setVisible(!split);

        auto scaleX = this->getChildByID("scale-x-container");
        if (scaleX) scaleX->setVisible(split);

        auto scaleY = this->getChildByID("scale-y-container");
        if (scaleY) scaleY->setVisible(split);
        
        auto top = split ? scaleY : scaleXY;
        if (!top) return;

        auto lockPositionMenu = m_scaleLockButton->getParent();
        if (!lockPositionMenu) return;

        lockPositionMenu->setPosition({top->getPositionX(), top->boundingBox().getMaxY() + lockPositionMenu->getContentHeight() / 2.f + 5.f});
    }
};