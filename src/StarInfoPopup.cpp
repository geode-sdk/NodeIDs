#include <Geode/Bindings.hpp>
#include <Geode/modify/StarInfoPopup.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

struct StarInfoPopupIDs : Modify<StarInfoPopupIDs, StarInfoPopup> {
    struct Fields {
        int m_daily = 0;
        int m_gauntlet = 0;
        int m_map = 0;
        bool m_platformer = false;
    };

    static void onModify(auto& self) {
        if (!self.setHookPriority("StarInfoPopup::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set StarInfoPopup::init hook priority, node IDs may not work properly");
        }
    }

    bool init(int a, int b, int c, int d, int e, int f, int daily, int gauntlet, int map, bool platformer) {
        if (!StarInfoPopup::init(a,b,c,d,e,f,daily,gauntlet,map,platformer)) return false;

        m_fields->m_daily = daily;
        m_fields->m_gauntlet = gauntlet;
        m_fields->m_map = map;
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
        "title"
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
            fmt::format("{}-text", diff).c_str()
        );
        idx += 2;
    }

    if(self->m_fields->m_gauntlet > 0) setIDSafe(m_mainLayer, idx++, "gauntlet-text");
    if(self->m_fields->m_daily > 0) setIDSafe(m_mainLayer, idx++, "daily-text");
    if(self->m_fields->m_map > 0) setIDSafe(m_mainLayer, idx++, "map-text");

    auto winSize = CCDirector::sharedDirector()->getWinSize();

    //bottom right menu
    auto bottomRight = CCMenu::create();
    bottomRight->setPosition((winSize.width / 2 + 190) - 12, (winSize.height / 2 - 105) + 14);
    bottomRight->setID("bottom-right-menu");
    bottomRight->setAnchorPoint({1, 0});
    bottomRight->setZOrder(11);
    bottomRight->setContentSize({ 40.f, 100.f });
    bottomRight->setScale(.4f);
    //touch prio hack to make it clickable,
    //cant call handleTouchPriority(this) in here because that breaks the ProfilePage below it
    //if you wanna change this code, do it in DemonInfoPopup as well
    //the menu is not populated with clickable stuff by default but mods are free to use it for this purpose
    bottomRight->setTouchPriority(-600);
    bottomRight->setLayout(
        ColumnLayout::create()
            ->setAxisAlignment(AxisAlignment::Start)
            ->setCrossAxisLineAlignment(AxisAlignment::End)
            ->setGap(14.f)
    );
    m_mainLayer->addChild(bottomRight);

    if(auto gauntlet = m_mainLayer->getChildByID("gauntlet-text")) switchToMenu(gauntlet, bottomRight);
    if(auto daily = m_mainLayer->getChildByID("daily-text")) switchToMenu(daily, bottomRight);
    if(auto map = m_mainLayer->getChildByID("map-text")) switchToMenu(map, bottomRight);

    bottomRight->updateLayout();

    //identical menu on bottom left for mods to use
    auto bottomLeft = CCMenu::create();
    bottomLeft->setPosition((winSize.width / 2 - 190) + 12, (winSize.height / 2 - 105) + 14);
    bottomLeft->setID("bottom-left-menu");
    bottomLeft->setAnchorPoint({0, 0});
    bottomLeft->setZOrder(11);
    bottomLeft->setContentSize({ 40.f, 100.f });
    bottomLeft->setScale(.4f);
    bottomLeft->setTouchPriority(-600);
    bottomLeft->setLayout(
        ColumnLayout::create()
            ->setAxisAlignment(AxisAlignment::Start)
            ->setCrossAxisLineAlignment(AxisAlignment::Start)
            ->setGap(14.f)
    );
    m_mainLayer->addChild(bottomLeft);

    //handleTouchPriority(this);
}