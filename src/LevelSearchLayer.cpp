// #include "AddIDs.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/LevelSearchLayer.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(LevelSearchLayer) {
    // set the funny ids

    auto winSize = CCDirector::get()->getWinSize();

    setIDSafe(this, 0, "background");
    this->getChildByType<CCTextInputNode>(0)->setID("search-bar");
    this->getChildByType<CCScale9Sprite>(0)->setID("level-search-bg");
    this->getChildByType<CCScale9Sprite>(1)->setID("level-search-bar-bg");
    this->getChildByType<CCScale9Sprite>(2)->setID("quick-search-bg");
    this->getChildByType<CCScale9Sprite>(3)->setID("difficulty-filters-bg");
    this->getChildByType<CCScale9Sprite>(4)->setID("length-filters-bg");
    this->getChildByType<CCLabelBMFont>(0)->setID("quick-search-title");
    this->getChildByType<CCLabelBMFont>(1)->setID("filters-title");
    this->getChildByType<CCSprite>(1)->setID("left-corner");
    this->getChildByType<CCSprite>(2)->setID("right-corner");

    if (auto filtermenu = this->getChildByType<CCMenu>(0)) {
        filtermenu->setID("other-filter-menu");
        filtermenu->setLayout(
            ColumnLayout::create()
                ->setAxisReverse(true)
                ->setGap(10)
                ->setAxisAlignment(AxisAlignment::End)
        );
        filtermenu->setAnchorPoint({1, 0.5f});
        filtermenu->setPosition({winSize.width - 5, filtermenu->getPositionY()});
        filtermenu->setContentSize({filtermenu->getContentSize().width, winSize.height-10});

        setIDSafe(filtermenu, 0, "clear-filters-button");
        setIDSafe(filtermenu, 1, "advanced-filters-button");
        setIDSafe(filtermenu, 2, "lists-button");
        filtermenu->updateLayout();
    }
    if (auto searchmenu = this->getChildByType<CCMenu>(1)) {
        searchmenu->setID("search-button-menu");
        setIDSafe(searchmenu, 0, "search-level-button");
        setIDSafe(searchmenu, 1, "search-user-button");
        setIDSafe(searchmenu, 2, "clear-search-button");
    }
    if (auto quickmenu = this->getChildByType<CCMenu>(2)) {
        quickmenu->setID("quick-search-menu");
        setIDSafe(quickmenu, 0, "most-downloaded-button");
        setIDSafe(quickmenu, 1, "most-liked-button");
        setIDSafe(quickmenu, 2, "sent-button");
        setIDSafe(quickmenu, 3, "trending-button");
        setIDSafe(quickmenu, 4, "recent-button");
        setIDSafe(quickmenu, 5, "magic-button");
        setIDSafe(quickmenu, 6, "awarded-button");
        setIDSafe(quickmenu, 7, "followed-button");
        setIDSafe(quickmenu, 8, "friends-button");
    }
    if (auto filtersmenu = this->getChildByType<CCMenu>(3)) {
        filtersmenu->setID("difficulty-filter-menu");
        setIDSafe(filtersmenu, 0, "na-filter-button");
        setIDSafe(filtersmenu, 1, "easy-filter-button");
        setIDSafe(filtersmenu, 2, "normal-filter-button");
        setIDSafe(filtersmenu, 3, "hard-filter-button");
        setIDSafe(filtersmenu, 4, "harder-filter-button");
        setIDSafe(filtersmenu, 5, "insane-filter-button");
        setIDSafe(filtersmenu, 6, "demon-filter-button");
        setIDSafe(filtersmenu, 7, "auto-filter-button");
        setIDSafe(filtersmenu, 8, "demon-type-filter-button");
    }
    if (auto filtersmenu = this->getChildByType<CCMenu>(4)) {
        filtersmenu->setID("length-filter-menu");
        if(m_type == 0) {
            setIDSafe(filtersmenu, 0, "clock-icon");
            setIDSafe(filtersmenu, 1, "tiny-filter-button");
            setIDSafe(filtersmenu, 2, "short-filter-button");
            setIDSafe(filtersmenu, 3, "medium-filter-button");
            setIDSafe(filtersmenu, 4, "long-filter-button");
            setIDSafe(filtersmenu, 5, "xl-filter-button");
            setIDSafe(filtersmenu, 6, "plat-filter-button");
            setIDSafe(filtersmenu, 7, "star-filter-button");
        } else if(m_type == 1) {
            setIDSafe(filtersmenu, 0, "star-filter-button");
        }
    }
    if (auto backmenu = this->getChildByType<CCMenu>(5)) {
        backmenu->setID("exit-menu");
        setIDSafe(backmenu, 0, "exit-button");
    }

    auto bottomLeftMenu = CCMenu::create();
    bottomLeftMenu->setPosition(10, 10);
    bottomLeftMenu->setID("bottom-left-menu");
    bottomLeftMenu->setAnchorPoint({0, 0});
    bottomLeftMenu->setZOrder(1);
    bottomLeftMenu->setContentSize({ 40.f, winSize.height/2 });
    bottomLeftMenu->setLayout(
        ColumnLayout::create()
            ->setAxisAlignment(AxisAlignment::Start)
    );
    this->addChild(bottomLeftMenu);

}

struct LevelSearchLayerIDs : Modify<LevelSearchLayerIDs, LevelSearchLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("LevelSearchLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set LevelSearchLayer::init hook priority, node IDs may not work properly");
        }
    }

    bool init(int type) {
        if (!LevelSearchLayer::init(type)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};
