#include <Geode/Geode.hpp>

#if GEODE_COMP_GD_VERSION >= 22090

#include <Geode/modify/MyStuffPopup.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

#include <array>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(MyStuffPopup) {
    m_mainLayer->setID("main-layer");
    setIDSafe<CCSprite>(m_mainLayer, 0, "background");
    setIDSafe<CCLabelBMFont>(m_mainLayer, 0, "title-label");
    m_buttonMenu->setID("main-menu");

    // MyStuffPopup adds the close button before the social buttons.
    if (auto closeButton = m_buttonMenu->getChildByType<CCMenuItemSpriteExtra>(0)) {
        closeButton->setID("close-button");
    }

    auto winSize = CCDirector::get()->getWinSize();

    auto socialsMenu = CCMenu::create();
    socialsMenu->setID("socials-menu");
    socialsMenu->setLayout(
        RowLayout::create()
            ->setGap(9.f)
            ->setAxisAlignment(AxisAlignment::Center)
            ->setCrossAxisAlignment(AxisAlignment::Center)
            ->setAutoScale(true)
    );
    socialsMenu->setPosition({winSize.width / 2.f, winSize.height / 2.f - 10.f});
    socialsMenu->setContentSize({240.f, 34.f});
    socialsMenu->setZOrder(10);
    m_mainLayer->addChild(socialsMenu);

    // The game sets a tag identifying the social network on each button.
    // Tag 0 is the YouTube button, not the close button.
    static constexpr std::array<const char*, 5> SOCIAL_IDS = {
        "youtube-button",
        "twitter-button",
        "twitch-button",
        "instagram-button",
        "tiktok-button",
    };

    for (int i = 1; ; ++i) {
        auto button = m_buttonMenu->getChildByType<CCMenuItemSpriteExtra>(i);
        if (!button) break;

        auto tag = button->getTag();
        if (tag < 0 || tag >= static_cast<int>(SOCIAL_IDS.size())) continue;

        button->setID(SOCIAL_IDS[tag]);
        switchToMenu(button, socialsMenu);
    }

    socialsMenu->updateLayout();
    handleTouchPriority(this);

    verifyIDSafe(m_mainLayer, "main-layer");
}

struct MyStuffPopupIDs : Modify<MyStuffPopupIDs, MyStuffPopup> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("MyStuffPopup::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set MyStuffPopup::init hook priority, node IDs may not work properly");
        }
    }

    bool init(GJUserScore* score) {
        if (!MyStuffPopup::init(score)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};

#endif
