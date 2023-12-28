// #include "AddIDs.hpp"

#include <Geode/modify/CommentCell.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(CommentCell) {
    if(m_comment->m_commentDeleted) return;
    
    bool smallCommentsMode = this->m_height == 36; //this is how robtop does the check
    bool usernameNotInMenu = !m_comment->m_userScore || !m_comment->m_userScore->m_accountID || m_accountComment || m_comment->m_hasLevelID;

    if(!smallCommentsMode) getChildOfType<CCScale9Sprite>(m_mainLayer, 0)->setID("background");

    int bmfontOffset = 0;
    /*if(m_comment->m_modBadge > 0) {
        getChildOfType<CCSprite>(m_mainLayer, 0)->setID("mod-badge");
    }*/
    if(m_comment->m_percentage > 0) {
        getChildOfType<CCLabelBMFont>(m_mainLayer, 0 + bmfontOffset)->setID("percentage-label");
        bmfontOffset += 1;
    }
    if (usernameNotInMenu) {
        getChildOfType<CCLabelBMFont>(m_mainLayer, 0 + bmfontOffset)->setID("username-label");
        bmfontOffset += 1;
    }

    if(smallCommentsMode) {
        getChildOfType<CCLabelBMFont>(m_mainLayer, 0 + bmfontOffset)->setID("comment-text-label");
        bmfontOffset += 1;
    }

    if(!m_comment->m_isSpam) {
        getChildOfType<CCLabelBMFont>(m_mainLayer, 0 + bmfontOffset)->setID("likes-label");
        if(!(m_comment->m_uploadDate).empty()) getChildOfType<CCLabelBMFont>(m_mainLayer, 1 + bmfontOffset)->setID("date-label");
    }

    if(!smallCommentsMode) getChildOfType<TextArea>(m_mainLayer, 0)->setID("comment-text-area");
    //getChildOfType<SimplePlayer>(m_mainLayer, 0)->setID("player-icon");

    if (auto mainMenu = getChildOfType<CCMenu>(m_mainLayer, 0)) {
        mainMenu->setID("main-menu");

        int menuOffset = 0;
        if(!usernameNotInMenu) {
            setIDSafe(mainMenu, 0, "username-button");
            menuOffset += 1;
        }
        if(m_comment->m_hasLevelID) {
            setIDSafe(mainMenu, 0 + menuOffset, "level-id-button");
            menuOffset += 1;
        }
        if(m_comment->m_isSpam) {
            setIDSafe(mainMenu, 0 + menuOffset, "spam-button");
            menuOffset += 1;
        } else {
            setIDSafe(mainMenu, 0 + menuOffset, "like-button");
            setIDSafe(mainMenu, 1 + menuOffset, "delete-button");
        }
    }
}

struct CommentCellIDs : Modify<CommentCellIDs, CommentCell> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("CommentCell::loadFromComment", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set CommentCell::loadFromComment hook priority, node IDs may not work properly");
        }
    }

    void loadFromComment(GJComment* comment) {
        CommentCell::loadFromComment(comment);

        //TODO: figure out how to provide node IDs on second run of this function (when user clicks show on a spam comment)
        NodeIDs::get()->provide(this);
    }
};
