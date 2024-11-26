#include "IDCheck.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/GJMessageCell.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(GJMessageCell) {
    size_t offset = 0;

    setIDSafe(m_mainLayer, offset++, "title-label");
    setIDSafe(m_mainLayer, offset++, "main-menu");
    
    if(!m_message->m_uploadDate.empty()) setIDSafe(m_mainLayer, offset++, "date-label");
    if(!m_message->m_read && !m_message->m_outgoing) setIDSafe(m_mainLayer, offset++, "unread-mark");

    if(auto menu = m_mainLayer->getChildByID("main-menu")) {
        setIDs(
            menu,
            0,
            "view-button",
            "delete-button",
            "user-button",
            "select-toggler"
        );

        auto viewMenu = CCMenu::create();
        viewMenu->setLayout(
            RowLayout::create()
                ->setGap(10.f)
                ->setAxisAlignment(AxisAlignment::End)
        );
        viewMenu->setID("view-menu");
        viewMenu->setContentSize({100, m_height - 2});
        viewMenu->setPosition({m_width - 60 + 0.25f, (m_height / 2) + 1.f});
        viewMenu->setZOrder(10);
        m_mainLayer->addChild(viewMenu);

        switchToMenu(menu->getChildByID("view-button"), viewMenu);
        switchToMenu(menu->getChildByID("delete-button"), viewMenu);
        viewMenu->updateLayout();
    }

    verifyIDSafe(m_toggler, "select-toggler");
}

struct GJMessageCellIDs : Modify<GJMessageCellIDs, GJMessageCell> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("GJMessageCell::loadFromMessage", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set GJMessageCell::loadFromMessage hook priority, node IDs may not work properly");
        }
    }

    void loadFromMessage(GJUserMessage* message) {
        GJMessageCell::loadFromMessage(message);

        NodeIDs::get()->provide(this);
    }
};
