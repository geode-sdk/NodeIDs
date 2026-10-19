#include <Geode/Geode.hpp>

#if GEODE_COMP_GD_VERSION >= 22090

#include <Geode/modify/MessageThreadsPage.hpp>
#include <Geode/utils/NodeIDs.hpp>

#include "IDCheck.hpp"

using namespace geode::prelude;
using namespace geode::node_ids;

static CCMenu* createMenuAround(CCNode* parent, char const* id, AxisLayout* layout, std::initializer_list<CCNode*> nodes) {
    std::vector<CCNode*> valid;
    for (auto node : nodes) {
        if (node && node->getParent()) valid.push_back(node);
    }
    if (valid.empty()) return nullptr;

    bool isRow = layout->getAxis() == Axis::Row;
    CCPoint boundsMin, boundsMax;
    float totalGap = 0.f;
    for (size_t i = 0; i < valid.size(); i++) {
        auto box = valid[i]->boundingBox();
        auto oldParent = valid[i]->getParent();
        auto min = parent->convertToNodeSpace(oldParent->convertToWorldSpace(box.origin));
        auto max = parent->convertToNodeSpace(oldParent->convertToWorldSpace(box.origin + box.size));
        if (i == 0) {
            boundsMin = min;
            boundsMax = max;
        }
        else {
            boundsMin = ccp(std::min(boundsMin.x, min.x), std::min(boundsMin.y, min.y));
            boundsMax = ccp(std::max(boundsMax.x, max.x), std::max(boundsMax.y, max.y));
        }

        if (i > 0) {
            auto prev = valid[i - 1]->boundingBox();
            totalGap += isRow
                ? std::abs(box.getMidX() - prev.getMidX()) - (box.size.width + prev.size.width) / 2
                : std::abs(box.getMidY() - prev.getMidY()) - (box.size.height + prev.size.height) / 2;
        }
    }
    if (valid.size() > 1) {
        layout->setGap(std::max(totalGap / (valid.size() - 1), 0.f));
    }

    auto menu = CCMenu::create();
    menu->setID(id);
    menu->setPosition((boundsMin + boundsMax) / 2);
    menu->setContentSize({ boundsMax.x - boundsMin.x, boundsMax.y - boundsMin.y });
    menu->setZOrder(valid[0]->getParent()->getZOrder());
    parent->addChild(menu);

    for (auto node : valid) {
        switchToMenu(node, menu);
    }
    layout->ignoreInvisibleChildren(false);
    menu->setLayout(layout);

    return menu;
}

$register_ids(MessageThreadsPage) {
    m_mainLayer->setID("main-layer");

    setIDs(
        m_mainLayer,
        0,
        "background",
        "title-label",
        "main-menu",
        "search-bar-bg",
        "search-input",
        "loading-circle",
        "error-label",
        "page-label",
        "selection-strip",
        "selected-count-label",
        "invites-label"
    );

    setIDs(
        m_buttonMenu,
        0,
        "info-button",
        "back-button",
        "legacy-button",
        "new-thread-button",
        "search-button",
        "clear-search-button",
        "user-search-button",
        "all-filter-button",
        "dm-filter-button",
        "group-filter-button",
        "prev-page-button",
        "next-page-button",
        "refresh-button",
        "scroll-to-top-button",
        "select-all-button",
        "mark-read-button",
        "delete-button",
        "invites-button"
    );

    if (auto userSearchBtn = static_cast<CCMenuItemSpriteExtra*>(m_buttonMenu->getChildByID("user-search-button"))) {
        if (auto label = userSearchBtn->getNormalImage()->getChildByType<CCLabelBMFont>(0)) {
            label->setID("user-count-label");
        }
    }

    if (auto invitesBtn = static_cast<CCMenuItemSpriteExtra*>(m_buttonMenu->getChildByID("invites-button"))) {
        if (auto badge = invitesBtn->getNormalImage()->getChildByType<CCSprite>(0)) {
            badge->setID("invites-badge");
            if (auto label = badge->getChildByType<CCLabelBMFont>(0)) {
                label->setID("invites-count-label");
            }
        }
    }

    verifyIDSafe(m_buttonMenu, "main-menu");

    createMenuAround(
        m_mainLayer, "left-menu",
        ColumnLayout::create()->setAxisReverse(true),
        {
            m_buttonMenu->getChildByID("all-filter-button"),
            m_buttonMenu->getChildByID("dm-filter-button"),
            m_buttonMenu->getChildByID("group-filter-button")
        }
    );

    createMenuAround(
        m_mainLayer, "select-menu",
        RowLayout::create(),
        {
            m_buttonMenu->getChildByID("mark-read-button"),
            m_buttonMenu->getChildByID("delete-button")
        }
    );

    createMenuAround(
        m_mainLayer, "search-options-menu",
        RowLayout::create(),
        {
            m_buttonMenu->getChildByID("search-button"),
            m_buttonMenu->getChildByID("clear-search-button"),
            m_buttonMenu->getChildByID("user-search-button")
        }
    );

    auto bottomRightMenu = createMenuAround(
        m_mainLayer, "bottom-right-menu",
        ColumnLayout::create()->setAxisAlignment(AxisAlignment::Start),
        { m_buttonMenu->getChildByID("refresh-button") }
    );
    if (bottomRightMenu) {
        auto bottom = bottomRightMenu->getPositionY() - bottomRightMenu->getContentHeight() / 2;
        bottomRightMenu->setAnchorPoint({ 0.5f, 0.f });
        bottomRightMenu->setPositionY(bottom);
        bottomRightMenu->setContentHeight(100.f);
        bottomRightMenu->updateLayout();
    }

    handleTouchPriority(this);
}

struct MessageThreadsPageIDs : Modify<MessageThreadsPageIDs, MessageThreadsPage> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("MessageThreadsPage::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set MessageThreadsPage::init hook priority, node IDs may not work properly");
        }
    }

    bool init() {
        if (!MessageThreadsPage::init()) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};

#endif
