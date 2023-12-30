#include <Geode/Bindings.hpp>
#include <Geode/modify/LevelBrowserLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

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

                    if(/*GameManager::sharedState()->m_playerUserID != 0 || */ GJAccountManager::sharedState()->m_accountID != 0) {
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
    this->addChild(bottomMenu);

    /**
     * Sanity checks
    */
    if(m_rightArrow && m_rightArrow->getID() != "next-page-button") {
        log::warn("LevelBrowserLayer::m_rightArrow has an invalid ID - {}", m_rightArrow->getID());
    }
    if(m_leftArrow && m_leftArrow->getID() != "prev-page-button") {
        log::warn("LevelBrowserLayer::m_leftArrow has an invalid ID - {}", m_leftArrow->getID());
    }
    if(m_lastBtn && m_lastBtn->getID() != "last-page-button") {
        log::warn("LevelBrowserLayer::m_lastBtn has an invalid ID - {}", m_lastBtn->getID());
    }
    if(m_cancelSearchBtn && m_cancelSearchBtn->getID() != "clear-search-button") {
        log::warn("LevelBrowserLayer::m_cancelSearchBtn has an invalid ID - {}", m_cancelSearchBtn->getID());
    }
    if(m_refreshBtn && m_refreshBtn->getID() != "refresh-button") {
        log::warn("LevelBrowserLayer::m_refreshBtn has an invalid ID - {}", m_refreshBtn->getID());
    }
    if(m_countText && m_countText->getID() != "level-count-label") {
        log::warn("LevelBrowserLayer::m_countText has an invalid ID - {}", m_countText->getID());
    }
    if(m_pageBtn && m_pageBtn->getID() != "page-button") {
        log::warn("LevelBrowserLayer::m_pageBtn has an invalid ID - {}", m_pageBtn->getID());
    }
    if(m_folderBtn && m_folderBtn->getID() != "folder-button") {
        log::warn("LevelBrowserLayer::m_folderBtn has an invalid ID - {}", m_folderBtn->getID());
    }
    if(m_allObjectsToggler && m_allObjectsToggler->getID() != "select-all-toggler") {
        log::warn("LevelBrowserLayer::m_allObjectsToggler has an invalid ID - {}", m_allObjectsToggler->getID());
    }

    //menus
    if(m_rightArrow && m_rightArrow->getParent() && m_rightArrow->getParent()->getID() != "next-page-menu") {
        log::warn("LevelBrowserLayer::m_rightArrow's parent has an invalid ID - {}", m_rightArrow->getParent()->getID());
    }
    if(m_leftArrow && m_leftArrow->getParent() && m_leftArrow->getParent()->getID() != "prev-page-menu") {
        log::warn("LevelBrowserLayer::m_leftArrow's parent has an invalid ID - {}", m_leftArrow->getParent()->getID());
    }
    if(m_lastBtn && m_lastBtn->getParent() && m_lastBtn->getParent()->getID() != "page-menu") {
        log::warn("LevelBrowserLayer::m_lastBtn's parent has an invalid ID - {}", m_lastBtn->getParent()->getID());
    }
    if(m_cancelSearchBtn && m_cancelSearchBtn->getParent() && m_cancelSearchBtn->getParent()->getID() != "search-menu") {
        log::warn("LevelBrowserLayer::m_cancelSearchBtn's parent has an invalid ID - {}", m_cancelSearchBtn->getParent()->getID());
    }
    if(m_refreshBtn && m_refreshBtn->getParent() && m_refreshBtn->getParent()->getID() != "refresh-menu") {
        log::warn("LevelBrowserLayer::m_refreshBtn's parent has an invalid ID - {}", m_refreshBtn->getParent()->getID());
    }
    if(m_countText && m_countText->getParent() && m_countText->getParent() != this) {
        log::warn("LevelBrowserLayer::m_countText's parent is invalid - {}", m_countText->getParent());
    }
    if(m_pageBtn && m_pageBtn->getParent() && m_pageBtn->getParent()->getID() != "page-menu") {
        log::warn("LevelBrowserLayer::m_pageBtn's parent has an invalid ID - {}", m_pageBtn->getParent()->getID());
    }
    if(m_folderBtn && m_folderBtn->getParent() && m_folderBtn->getParent()->getID() != "page-menu") {
        log::warn("LevelBrowserLayer::m_folderBtn's parent has an invalid ID - {}", m_folderBtn->getParent()->getID());
    }
    if(m_allObjectsToggler && m_allObjectsToggler->getParent() && m_allObjectsToggler->getParent()->getID() != "delete-menu") {
        log::warn("LevelBrowserLayer::m_allObjectsToggler's parent has an invalid ID - {}", m_allObjectsToggler->getParent()->getID());
    }
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