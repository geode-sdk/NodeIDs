#include <Geode/Bindings.hpp>
#include <Geode/modify/DemonInfoPopup.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

struct DemonInfoPopupIDs : Modify<DemonInfoPopupIDs, DemonInfoPopup> {
    struct Fields {
        int m_weekly = 0;
        int m_gauntlet = 0;
    };

	static void onModify(auto& self) {
		if (!self.setHookPriority("DemonInfoPopup::init", GEODE_ID_PRIORITY)) {
			log::warn("Failed to set DemonInfoPopup::init hook priority, node IDs may not work properly");
		}
	}

	bool init(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int weekly, int gauntlet) {
		if (!DemonInfoPopup::init(a,b,c,d,e,f,g,h,i,j,weekly,gauntlet)) return false;

        m_fields->m_weekly = weekly;
        m_fields->m_gauntlet = gauntlet;

		NodeIDs::get()->provide(this);

		return true;
	}
};

$register_ids(DemonInfoPopup) {
    m_mainLayer->setID("main-layer");
    m_buttonMenu->setID("main-menu");
    setIDSafe(m_buttonMenu, 0, "ok-button");

    size_t idx = 0;

    setIDs(m_mainLayer, idx,
        "background",
        "main-menu",
        "classic-title",
        "platformer-title"
    );
    idx += 4;

    std::array<char const*, 5> diffNames = {
        "easy",
        "medium",
        "hard",
        "insane",
        "extreme"
    };

    for (auto const& diff : diffNames) {
        setIDs(m_mainLayer, idx, 
            fmt::format("{}-sprite", diff).c_str(),
            fmt::format("{}-classic", diff).c_str(),
            fmt::format("{}-platformer", diff).c_str()
        );
        idx += 3;
    }

    auto self = reinterpret_cast<DemonInfoPopupIDs*>(this);
    if(self->m_fields->m_gauntlet) setIDSafe(m_mainLayer, idx++, "gauntlet-text");
    if(self->m_fields->m_weekly) setIDSafe(m_mainLayer, idx++, "weekly-text");

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
    if(auto weekly = m_mainLayer->getChildByID("weekly-text")) switchToMenu(weekly, bottomRight);
    
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