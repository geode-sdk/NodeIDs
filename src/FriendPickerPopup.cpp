#include <Geode/Geode.hpp>

#if GEODE_COMP_GD_VERSION >= 22090

#include <Geode/modify/FriendPickerPopup.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(FriendPickerPopup) {
    m_mainLayer->setID("main-layer");

    setIDs(
        m_mainLayer,
        0,
        "background",
        "main-menu",
        "title-label",
        "status-label",
        "scroll-bg",
        "scroll-layer",
        "search-bg",
        "search-input"
    );
    setIDSafe<CCLabelBMFont>(m_mainLayer, 2, "count-label");
    if (auto loadingCircle = m_mainLayer->getChildByType<LoadingCircle>(0)) {
        loadingCircle->setID("loading-circle");
    }

    setIDs(
        m_buttonMenu,
        0,
        "close-button",
        "prev-page-button",
        "next-page-button"
    );

    int buttonIdx = 3;
    float doneWidth = 0.f;
    float clearWidth = 0.f;
    auto doneBtn = m_buttonMenu->getChildByType<CCMenuItemSpriteExtra>(buttonIdx);
    if (doneBtn && typeinfo_cast<ButtonSprite*>(doneBtn->getNormalImage())) {
        doneBtn->setID("done-button");
        doneWidth = doneBtn->getScaledContentWidth();
        buttonIdx++;
    }
    auto clearBtn = m_buttonMenu->getChildByType<CCMenuItemSpriteExtra>(buttonIdx);
    if (clearBtn && typeinfo_cast<ButtonSprite*>(clearBtn->getNormalImage())) {
        clearBtn->setID("clear-button");
        clearWidth = clearBtn->getScaledContentWidth();
        buttonIdx++;
    }
    setIDs(
        m_buttonMenu,
        buttonIdx,
        "info-button",
        "search-button",
        "selected-view-button"
    );

    verifyIDSafe(m_buttonMenu, "main-menu");

    auto winSize = CCDirector::get()->getWinSize();

    auto searchBtn = m_buttonMenu->getChildByID("search-button");
    auto searchWidth = searchBtn ? searchBtn->getScaledContentWidth() : 0.f;

    auto searchMenu = CCMenu::create();
    searchMenu->setLayout(
        RowLayout::create()
            ->setGap(22.f - searchWidth / 2)
            ->setAxisAlignment(AxisAlignment::Start)
            ->setAxisReverse(false)
    );
    searchMenu->setID("search-menu");
    searchMenu->setAnchorPoint({ 0.f, 0.5f });
    searchMenu->setPosition({ (winSize.width / 2) - 100.f, (winSize.height / 2) + 78.f });
    searchMenu->setContentSize({ 222.f + searchWidth / 2, 24.f });
    searchMenu->setZOrder(10);
    m_mainLayer->addChild(searchMenu);

    if (auto bg = m_mainLayer->getChildByID("search-bg")) {
        auto field = CCNode::create();
        field->setID("search-field");
        field->setAnchorPoint({ 0.5f, 0.5f });
        field->setContentSize(bg->getScaledContentSize());
        field->setPosition(bg->getPosition());
        m_mainLayer->addChild(field);

        switchToMenu(bg, field);
        switchToMenu(m_mainLayer->getChildByID("search-input"), field);
        switchToMenu(field, searchMenu);
    }

    switchToMenu(searchBtn, searchMenu);
    searchMenu->updateLayout();

    auto bottomMenu = CCMenu::create();
    bottomMenu->setLayout(
        RowLayout::create()
            ->setGap(72.f - (doneWidth + clearWidth) / 2)
            ->setAxisAlignment(AxisAlignment::Center)
            ->setAxisReverse(false)
    );
    bottomMenu->setID("bottom-menu");
    bottomMenu->setPosition({ winSize.width / 2, (winSize.height / 2) - 106.f });
    bottomMenu->setContentSize({ 230.f, 30.f });
    bottomMenu->setZOrder(10);
    m_mainLayer->addChild(bottomMenu);

    switchToMenu(m_buttonMenu->getChildByID("done-button"), bottomMenu);
    switchToMenu(m_buttonMenu->getChildByID("clear-button"), bottomMenu);
    bottomMenu->updateLayout();

    handleTouchPriority(this);
}

struct FriendPickerPopupIDs : Modify<FriendPickerPopupIDs, FriendPickerPopup> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("FriendPickerPopup::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set FriendPickerPopup::init hook priority, node IDs may not work properly");
        }
        if (!self.setHookPriority("FriendPickerPopup::mountVirtualRow", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set FriendPickerPopup::mountVirtualRow hook priority, node IDs may not work properly");
        }
    }

    bool init(FriendPickerDelegate* delegate, bool p0, bool p1, bool p2, bool p3) {
        if (!FriendPickerPopup::init(delegate, p0, p1, p2, p3)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }

    void mountVirtualRow(int index, CCNode* row, CCMenu* menu) {
        FriendPickerPopup::mountVirtualRow(index, row, menu);

        menu->setID("main-menu");

        setIDSafe<SimplePlayer>(row, 0, "player-icon");
        if (auto friendIcon = getChildBySpriteFrameName(row, "GJ_sFriendsIcon_001.png")) {
            friendIcon->setID("friend-icon");
        }

        for (auto [frame, name] : {
            std::pair{ "GJ_starsIcon_001.png", "stars" },
            std::pair{ "GJ_moonsIcon_001.png", "moons" },
            std::pair{ "GJ_demonIcon_001.png", "demons" },
            std::pair{ "GJ_hammerIcon_001.png", "creator-points" }
        }) {
            auto icon = getChildBySpriteFrameName(row, frame);
            if (!icon) continue;
            icon->setID(fmt::format("{}-icon", name));

            auto iconIdx = row->getChildren()->indexOfObject(icon);
            if (iconIdx == 0 || iconIdx == CC_INVALID_INDEX) continue;
            if (auto label = typeinfo_cast<CCLabelBMFont*>(row->getChildren()->objectAtIndex(iconIdx - 1))) {
                label->setID(fmt::format("{}-label", name));
            }
        }

        for (auto child : CCArrayExt<CCNode*>(row->getChildren())) {
            auto label = typeinfo_cast<CCLabelBMFont*>(child);
            if (!label || !label->getID().empty()) continue;
            label->setID(std::string_view(label->getString()) == "New!" ? "new-label" : "member-status-label");
        }

        setIDSafe<CCMenuItemSpriteExtra>(menu, 0, "player-name");
        setIDSafe<InfoAlertButton>(menu, 0, "friends-since-button");
        if (auto toggle = getChildBySpriteFrameName(menu, "GJ_checkOn_001.png")) {
            toggle->setID("select-button");
        }
        else if (auto toggle = getChildBySpriteFrameName(menu, "GJ_checkOff_001.png")) {
            toggle->setID("select-button");
        }
    }
};

#endif
