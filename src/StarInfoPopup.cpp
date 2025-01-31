#include <Geode/Bindings.hpp>
#include <Geode/modify/StarInfoPopup.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

struct StarInfoPopupIDs : Modify<StarInfoPopupIDs, StarInfoPopup> {
    struct Fields {
        int m_daily = 0;
        int m_gauntlet = 0;
        bool m_platformer = false;
    };

    static void onModify(auto& self) {
        if (!self.setHookPriority("StarInfoPopup::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set StarInfoPopup::init hook priority, node IDs may not work properly");
        }
    }

    bool init(int a, int b, int c, int d, int e, int f, int gauntlet, int daily, int unknown, bool platformer) {
        if (!StarInfoPopup::init(a,b,c,d,e,f,gauntlet,daily,unknown,platformer)) return false;

        m_fields->m_daily = daily;
        m_fields->m_gauntlet = gauntlet;
        m_fields->m_platformer = platformer;

        NodeIDs::get()->provide(this);

        return true;
    }
};

$register_ids(StarInfoPopup) {
    m_mainLayer->setID("main-layer");
    m_buttonMenu->setID("main-menu");
    setIDSafe(m_buttonMenu, 0, "ok-button");

    size_t idx = 0;

    auto self = reinterpret_cast<StarInfoPopupIDs*>(this);
    auto mode = self->m_fields->m_platformer ? "platformer" : "classic";

    setIDs(m_mainLayer, idx,
        "background",
        "main-menu",
        fmt::format("{}-title", mode).c_str()
    );
    idx += 3;

    std::array<char const*, 6> diffNames = {
        "auto",
        "easy",
        "normal",
        "hard",
        "harder",
        "insane"
    };

    for (auto const& diff : diffNames) {
        setIDs(m_mainLayer, idx, 
            fmt::format("{}-sprite", diff).c_str(),
            fmt::format("{}-{}", diff, mode).c_str()
        );
        idx += 2;
    }

    if (!self->m_fields->m_platformer) {
        if(self->m_fields->m_gauntlet) setIDSafe(m_mainLayer, idx++, "gauntlet-text");
        if(self->m_fields->m_daily) setIDSafe(m_mainLayer, idx++, "daily-text");
    }

    auto winSize = CCDirector::sharedDirector()->getWinSize();

    //bottom right menu
    auto bottomRight = CCMenu::create();
    bottomRight->setPosition((winSize.width / 2 + 190) - 12, (winSize.height / 2 - 105) + 14);
    bottomRight->setID("bottom-right-menu");
    bottomRight->setAnchorPoint({1, 0});
    bottomRight->setZOrder(1);
    bottomRight->setContentSize({ 40.f, 100.f });
    bottomRight->setScale(.4f);
    bottomRight->setLayout(
        ColumnLayout::create()
            ->setAxisAlignment(AxisAlignment::Start)
            ->setCrossAxisLineAlignment(AxisAlignment::End)
            ->setGap(14.f)
    );
    m_mainLayer->addChild(bottomRight);

    if(auto gauntlet = m_mainLayer->getChildByID("gauntlet-text")) switchToMenu(gauntlet, bottomRight);
    if(auto daily = m_mainLayer->getChildByID("daily-text")) switchToMenu(daily, bottomRight);

    bottomRight->updateLayout();

    //identical menu on bottom left for mods to use
    auto bottomLeft = CCMenu::create();
    bottomLeft->setPosition((winSize.width / 2 - 190) + 12, (winSize.height / 2 - 105) + 14);
    bottomLeft->setID("bottom-left-menu");
    bottomLeft->setAnchorPoint({0, 0});
    bottomLeft->setZOrder(1);
    bottomLeft->setContentSize({ 40.f, 100.f });
    bottomLeft->setScale(.4f);
    bottomLeft->setLayout(
        ColumnLayout::create()
            ->setAxisAlignment(AxisAlignment::Start)
            ->setCrossAxisLineAlignment(AxisAlignment::Start)
            ->setGap(14.f)
    );
    m_mainLayer->addChild(bottomLeft);

    handleTouchPriority(this);
}