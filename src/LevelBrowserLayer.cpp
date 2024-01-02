#include <Geode/Bindings.hpp>
#include <Geode/modify/LevelBrowserLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(LevelBrowserLayer) {
    auto winSize = CCDirector::get()->getWinSize();

    size_t spriteOffset = 0;
    size_t menuOffset = 0;
    size_t bmfontOffset = 0;

    if(!m_isOverlay) {
        getChildOfType<CCSprite>(this, 0)->setID("background");
        getChildOfType<CCSprite>(this, 1)->setID("left-corner");
        getChildOfType<CCSprite>(this, 2)->setID("right-corner");
        spriteOffset += 3;
    }

    if (auto menu = getChildOfType<CCMenu>(this, 0)) {
        menu->setID("back-menu");
        auto btn = setIDSafe(menu, 0, "back-button");
        menu->setContentSize({ 100.f, 50.f });
        menu->setPositionX(
            menu->getPositionX() + 100.f / 2 - 
                getSizeSafe(btn).width / 2
        );
        menu->setLayout(
            RowLayout::create()
                ->setAxisAlignment(AxisAlignment::Start)
        );
    }

    getChildOfType<CCLabelBMFont>(this, 0)->setID("level-count-label");
    getChildOfType<TextArea>(this, 0)->setID("no-internet-text");

    if (auto menu = getChildOfType<CCMenu>(this, 1)) {
        auto navMenuWidth = 50.f * winSize.aspect();

        if (auto prevPageBtn = setIDSafe(menu, 0, "prev-page-button")) {
            auto navMenu = detachAndCreateMenu(
                this,
                "prev-page-menu",
                RowLayout::create()
                    ->setAxisAlignment(AxisAlignment::Start),
                prevPageBtn
            );
            prevPageBtn->setZOrder(-1);
            navMenu->setContentSize({ navMenuWidth, 40.f });
            navMenu->setPositionX(
                navMenu->getPositionX() + navMenuWidth / 2 - 
                    prevPageBtn->getScaledContentSize().width / 2
            );
            navMenu->updateLayout();
        }

        auto nextPageBtn = setIDSafe(menu, 0, "next-page-button");

        auto pageBtn = setIDSafe(menu, 1, "page-button");
        auto folderBtn = m_searchObject->isLevelSearchObject() ? setIDSafe(menu, 2, "folder-button") : nullptr;
        auto lastPageBtn = setIDSafe(menu, m_searchObject->isLevelSearchObject() ? 3 : 2, "last-page-button");
        auto pageMenu = detachAndCreateMenu(
            this,
            "page-menu",
            ColumnLayout::create()
                ->setAxisReverse(true)
                ->setGrowCrossAxis(true)
                ->setAxisAlignment(AxisAlignment::End),
            pageBtn,
            folderBtn,
            lastPageBtn
        );
        pageMenu->setContentSize({ 40.f, 110.f });
        pageMenu->setAnchorPoint({ 1.f, .5f });
        pageMenu->setPosition(
            pageMenu->getPositionX() + 20.f,
            pageMenu->getPositionY() - 110.f / 2 + 12.5f
        );
        pageMenu->updateLayout();

        if (auto searchBtn = setIDSafe(menu, 1, "search-button")) {
            auto clearBtn = setIDSafe(menu, 2, "clear-search-button");
            // this is a hacky fix because for some reason adding children 
            // before the clear button is made visible is inconsistent
            if (clearBtn) {
                searchBtn->setZOrder(-1);
                clearBtn->setZOrder(-1);
            }
            auto searchMenu = detachAndCreateMenu(
                this,
                "search-menu",
                ColumnLayout::create()
                    ->setAxisReverse(true)
                    ->setCrossAxisReverse(true)
                    ->setGrowCrossAxis(true)
                    ->setCrossAxisOverflow(false)
                    ->setCrossAxisAlignment(AxisAlignment::Start)
                    ->setAxisAlignment(AxisAlignment::End),
                searchBtn,
                clearBtn
            );
            auto width = 45.f * winSize.aspect();
            searchMenu->setPosition(
                searchMenu->getPositionX() + width / 2 - 
                    searchBtn->getScaledContentSize().width / 2,
                searchMenu->getPositionY() - 80.f / 2 + 
                    searchBtn->getScaledContentSize().height / 2
            );
            searchMenu->setContentSize({ width, 80.f });
            searchMenu->updateLayout();
        } else {
            auto searchMenu = CCMenu::create();
            searchMenu->setID("search-menu");
            searchMenu->setContentSize({ 45.f * winSize.aspect(), 80.f });
            searchMenu->setPosition(
                45.f * winSize.aspect() / 2 + 7.5f,
                winSize.height  / 2 + 70.f
            );
            searchMenu->setLayout(
                ColumnLayout::create()
                    ->setAxisReverse(true)
                    ->setCrossAxisReverse(true)
                    ->setGrowCrossAxis(true)
                    ->setCrossAxisOverflow(false)
                    ->setCrossAxisAlignment(AxisAlignment::Start)
                    ->setAxisAlignment(AxisAlignment::End)
            );
            searchMenu->updateLayout();
            addChild(searchMenu);
        }

        menu->setID("next-page-menu");
        menu->setLayout(
            RowLayout::create()
                ->setAxisReverse(true)
                ->setAxisAlignment(AxisAlignment::End)
        );
        menu->setContentSize({ navMenuWidth, 40.f });
        menu->setPositionX(
            winSize.width - navMenuWidth / 2 - 5.f
        );
        menu->updateLayout();
    }

    if(m_searchObject) {

        std::array<SearchType, 5> searchTypes = { SearchType::DailySafe, SearchType::WeeklySafe, SearchType::EventSafe, SearchType::Featured, SearchType::FeaturedGDW };
        for(auto& type : searchTypes) {
            if(m_searchObject->m_searchType == type) {
                //0 matches TextArea
                getChildOfType<CCSprite>(this, 1 + spriteOffset)->setID("header-sprite");
                spriteOffset++;
                break;
            }
        }

        //std::array<SearchType, 3> localTypes = { SearchType::MyLevels, SearchType::SavedLevels, SearchType::FavouriteLevels };
        if(m_searchObject->m_searchType >= SearchType::MyLevels && m_searchObject->m_searchType <= SearchType::FavouriteLevels && !m_searchObject->m_searchIsOverlay) {
            if (auto menu = getChildOfType<CCMenu>(this, 2)) {
                menu->setID("delete-menu");

                getChildOfType<CCMenuItemSpriteExtra>(menu, 0)->setID("delete-button");
                getChildOfType<CCMenuItemToggler>(menu, 0)->setID("select-all-toggler");
            }
            getChildOfType<CCLabelBMFont>(this, 1 + bmfontOffset)->setID("select-all-text");

            menuOffset++;
            bmfontOffset++;
        }

        if(m_searchObject->m_searchType == SearchType::MyLevels || m_searchObject->m_searchType == SearchType::SmartTemplates || m_searchObject->m_searchType == SearchType::MyLists) {
            if (auto menu = getChildOfType<CCMenu>(this, 2 + menuOffset)) {

                menu->setID("new-level-menu");
                auto newLvlBtn = setIDSafe(menu, 0, "new-level-button");

                if(!m_isOverlay) {

                    if(GameManager::sharedState()->m_playerUserID != 0 || GJAccountManager::sharedState()->m_accountID != 0) {
                        if (auto myLevelsBtn = setIDSafe(menu, 1, "my-levels-button")) {
                            auto menu = detachAndCreateMenu(
                                this,
                                "my-levels-menu",
                                ColumnLayout::create()
                                    ->setAxisAlignment(AxisAlignment::Start),
                                myLevelsBtn
                            );
                            menu->setPositionY(
                                menu->getPositionY() + 125.f / 2 - 
                                    myLevelsBtn->getScaledContentSize().height / 2
                            );
                            menu->setContentSize({ 50.f, 125.f });
                            menu->updateLayout();
                        }
                    }

                    getChildOfType<CCMenuItemSpriteExtra>(menu, 1)->setID("switch-mode-button");

                    menu->setLayout(
                        ColumnLayout::create()
                            ->setAxisAlignment(AxisAlignment::Start)
                    );
                    menu->setPositionY(
                        menu->getPositionY() + 130.f / 2 - 
                            getSizeSafe(newLvlBtn).height / 2
                    );
                    menu->setContentSize({ 50.f, 130.f });
                    menu->updateLayout();
                }   
            }

            menuOffset++;
        }

        if(m_searchObject->m_searchType == SearchType::SavedLevels || m_searchObject->m_searchType == SearchType::FavouriteLevels || m_searchObject->m_searchType == SearchType::FavouriteLists) {
            if (auto menu = getChildOfType<CCMenu>(this, 2 + menuOffset)) {
                menu->setID("saved-menu");

                getChildOfType<CCMenuItemSpriteExtra>(menu, 0)->setID("delete-button");
                getChildOfType<CCMenuItemSpriteExtra>(menu, 1)->setID("switch-mode-button");
                if(m_searchObject->m_searchType != SearchType::FavouriteLists) getChildOfType<CCMenuItemSpriteExtra>(menu, 2)->setID("favorite-button");
            }

            menuOffset++;
            bmfontOffset++;
        } else {
            auto intType = static_cast<int>(m_searchObject->m_searchType);
            if(intType != 98 && intType != 102 && intType != 9 && intType != 10 && intType != 14 && intType != 100 && intType != 101) {
                if (auto menu = getChildOfType<CCMenu>(this, 2 + menuOffset)) {
                    menu->setID("refresh-menu");

                    getChildOfType<CCMenuItemSpriteExtra>(menu, 0)->setID("refresh-button");
                }

                menuOffset++;

                if (auto menu = getChildOfType<CCMenu>(this, 2 + menuOffset)) {
                    menu->setID("info-menu");

                    getChildOfType<CCMenuItemSpriteExtra>(menu, 0)->setID("info-button");
                    menuOffset++;

                    menu->setContentSize({ 26.75f*2, winSize.height - 37.f });
                    menu->setPositionY(winSize.height / 2);
                    menu->setLayout(
                        ColumnLayout::create()
                            ->setGap(7.f)
                            ->setAxisAlignment(AxisAlignment::Start)
                            ->setAxisReverse(true)
                    );
                }
            }
        }

    }

    auto bottomMenu = CCMenu::create();
    bottomMenu->setID("bottom-menu");
    bottomMenu->setContentSize({ 325.f + 20.f * winSize.aspect(), 50.f });
    bottomMenu->setPosition(winSize.width / 2, 28.f);
    bottomMenu->setZOrder(15);
    bottomMenu->setLayout(RowLayout::create());

    /**
     * Sanity checks
    */
    verifyIDSafe(m_rightArrow, "next-page-button");
    verifyIDSafe(m_leftArrow, "prev-page-button");
    verifyIDSafe(m_lastBtn, "last-page-button");
    verifyIDSafe(m_cancelSearchBtn, "clear-search-button");
    verifyIDSafe(m_refreshBtn, "refresh-button");
    verifyIDSafe(m_countText, "level-count-label");
    verifyIDSafe(m_pageBtn, "page-button");
    verifyIDSafe(m_folderBtn, "folder-button");
    verifyIDSafe(m_allObjectsToggler, "select-all-toggler");

    //menus
    verifyParentIDSafe(m_rightArrow, "next-page-menu");
    verifyParentIDSafe(m_leftArrow, "prev-page-menu");
    verifyParentIDSafe(m_lastBtn, "page-menu");
    verifyParentIDSafe(m_cancelSearchBtn, "search-menu");
    verifyParentIDSafe(m_refreshBtn, "refresh-menu");
    verifyParentIDSafe(m_pageBtn, "page-menu");
    verifyParentIDSafe(m_folderBtn, "page-menu");
    verifyParentIDSafe(m_allObjectsToggler, "delete-menu");
}

struct LevelBrowserLayerIDs : Modify<LevelBrowserLayerIDs, LevelBrowserLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("LevelBrowserLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set LevelBrowserLayer::init hook priority, node IDs may not work properly");
        }
    }

    bool init(GJSearchObject* obj) {
        if (!LevelBrowserLayer::init(obj)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};