#include <Geode/Geode.hpp>

#if GEODE_COMP_GD_VERSION >= 22090

#include <Geode/modify/ThreadSearchPopup.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(ThreadSearchPopup) {
    m_mainLayer->setID("main-layer");

    setIDs(
        m_mainLayer,
        0,
        "background",
        "main-menu",
        "title-label",
        "search-bg",
        "search-input",
        "year-bg",
        "year-input",
        "year-label",
        "month-bg",
        "month-input",
        "month-label",
        "day-bg",
        "day-input",
        "day-label"
    );

    setIDs(
        m_buttonMenu,
        0,
        "close-button",
        "search-button",
        "go-button"
    );

    verifyIDSafe(m_buttonMenu, "main-menu");

    auto winSize = CCDirector::get()->getWinSize();

    auto topMenu = CCMenu::create();
    topMenu->setLayout(
        RowLayout::create()
            ->setGap(21.f)
            ->setAxisAlignment(AxisAlignment::Center)
            ->setAxisReverse(false)
    );
    topMenu->setID("top-menu");
    topMenu->setPosition({ (winSize.width / 2) + 7.5f, (winSize.height / 2) + 16.f });
    topMenu->setContentSize({ 272.f, 28.f });
    topMenu->setZOrder(10);
    m_mainLayer->addChild(topMenu);

    auto bottomMenu = CCMenu::create();
    bottomMenu->setLayout(
        RowLayout::create()
            ->setGap(6.f)
            ->setAxisAlignment(AxisAlignment::Center)
            ->setAxisReverse(false)
    );
    bottomMenu->setID("bottom-menu");
    bottomMenu->setPosition({ (winSize.width / 2) + 7.5f, (winSize.height / 2) - 30.f });
    bottomMenu->setContentSize({ 272.f, 28.f });
    bottomMenu->setZOrder(10);
    m_mainLayer->addChild(bottomMenu);

    for (auto prefix : { "search", "year", "month", "day" }) {
        auto bg = m_mainLayer->getChildByID(fmt::format("{}-bg", prefix));
        if (!bg) continue;

        auto field = CCNode::create();
        field->setID(fmt::format("{}-field", prefix));
        field->setAnchorPoint({ 0.5f, 0.5f });
        field->setContentSize(bg->getScaledContentSize());
        field->setPosition(bg->getPosition());
        m_mainLayer->addChild(field);

        switchToMenu(bg, field);
        switchToMenu(m_mainLayer->getChildByID(fmt::format("{}-input", prefix)), field);
        switchToMenu(m_mainLayer->getChildByID(fmt::format("{}-label", prefix)), field);

        switchToMenu(field, std::string_view(prefix) == "search" ? topMenu : bottomMenu);
    }

    switchToMenu(m_buttonMenu->getChildByID("search-button"), topMenu);
    topMenu->updateLayout();

    if (auto goBtn = m_buttonMenu->getChildByID("go-button")) {
        goBtn->setLayoutOptions(AxisLayoutOptions::create()->setPrevGap(55.f));
        switchToMenu(goBtn, bottomMenu);
    }
    bottomMenu->updateLayout();

    handleTouchPriority(this);
}

struct ThreadSearchPopupIDs : Modify<ThreadSearchPopupIDs, ThreadSearchPopup> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("ThreadSearchPopup::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set ThreadSearchPopup::init hook priority, node IDs may not work properly");
        }
    }

    bool init(ThreadViewPopup* viewPopup) {
        if (!ThreadSearchPopup::init(viewPopup)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};

#endif
