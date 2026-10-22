#include <Geode/Bindings.hpp>
#include <Geode/Enums.hpp>
#include <Geode/modify/GJRotationControl.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(GJRotationControl) {
    setContentSize({0.f, 0.f});
    ignoreAnchorPointForPosition(false);

    setIDSafe<CCSprite>(this, 0, "rotation-thumb");

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

    m_angleInput->setID("rotation-input");
    m_applyAngleButton->setID("refresh-rotation-button");
    m_lockRotationButton->setID("lock-position-toggle");

    setIDSafe<CCScale9Sprite>(m_angleInput, 0, "background");
    
    auto refreshMenu = getChildByType<CCMenu>(1);

    auto container = detachAndCreateMenu(this, "rotation-input-container", 
        nullptr,
        m_angleInput, 
        m_applyAngleButton
    );

    auto size = CCSize{m_angleInput->getScaledContentWidth() + 10.f + m_applyAngleButton->getScaledContentWidth(), std::max(m_angleInput->getScaledContentHeight(), m_angleInput->getScaledContentHeight())};

    m_angleInput->setPosition({m_angleInput->getScaledContentWidth() / 2.f, size.height / 2.f});
    container->setPositionX(container->getPositionX() + m_angleInput->getPositionX() / 2.f);

    m_applyAngleButton->setPosition({size.width - m_applyAngleButton->getScaledContentWidth() / 2.f, size.height / 2.f});
    container->setContentSize({size.width, size.height});

    refreshMenu->removeFromParent();
};

struct GJRotationControlIDs : Modify<GJRotationControlIDs, GJRotationControl> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("GJRotationControl::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set GJRotationControl::init hook priority, node IDs may not work properly");
        }
    }

    bool init() {
        if (!GJRotationControl::init()) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};