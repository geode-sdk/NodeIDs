// #include "AddIDs.hpp"

#include <Geode/Geode.hpp>
#include <Geode/modify/CommentCell.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(CommentCell) {
    if(m_comment->m_commentDeleted) return;

    auto winSize = CCDirector::sharedDirector()->getWinSize();

    bool smallCommentsMode = m_compactMode; // was this->m_height == 36 but it changed in some 2.2 sub-update
    bool usernameNotInMenu = m_comment->m_accountID <= 0 || m_accountComment || m_comment->m_hasLevelID;

    //there is a chance m_comment->m_accountID is not set properly before loadFromComment
    //but this is fixed inside loadFromComment itself, so that case is also handled

    if(!smallCommentsMode) setIDSafe<CCScale9Sprite>(m_mainLayer, 0, "background");

    int bmfontOffset = 0;

    if(!m_accountComment) {
        if(m_comment->m_modBadge > 0) {
            setIDSafe<CCSprite>(m_mainLayer, 0, "mod-badge");
        }
        if(m_comment->m_percentage > 0) {
            setIDSafe<CCLabelBMFont>(m_mainLayer, bmfontOffset++, "percentage-label");
        }
    }

    if (usernameNotInMenu) {
        setIDSafe<CCLabelBMFont>(m_mainLayer, bmfontOffset++, "username-label");
    }

    if(smallCommentsMode) {
        setIDSafe<CCLabelBMFont>(m_mainLayer, bmfontOffset++, "comment-text-label");
    }

    if(!m_comment->m_isSpam) {
        if(!m_comment->m_unkMultiplayerBool) {
            setIDSafe<CCLabelBMFont>(m_mainLayer, bmfontOffset++, "likes-label");
        }
        if(!(m_comment->m_uploadDate).empty()) {
            setIDSafe<CCLabelBMFont>(m_mainLayer, bmfontOffset++, "date-label");
        }
    }

    if(!smallCommentsMode) setIDSafe<TextArea>(m_mainLayer, 0, "comment-text-area-label");

    if (auto mainMenu = setIDSafe<CCMenu>(m_mainLayer, 0, "main-menu")) {
        int menuOffset = 0;
        if(!usernameNotInMenu) {
            setIDSafe(mainMenu, menuOffset++, "username-button");
        }
        if(m_comment->m_hasLevelID) {
            setIDSafe(mainMenu, menuOffset++, "level-id-button");
        }
        if(m_comment->m_isSpam) {
            setIDSafe(mainMenu, menuOffset++, "spam-button");
        } else if(!m_comment->m_unkMultiplayerBool) {
            setIDSafe(mainMenu, menuOffset++, "like-button");
            setIDSafe(mainMenu, menuOffset++, "delete-button");
        }

        if (!m_accountComment) {
            CCNode* usernameLabel = nullptr;
            auto userMenu = CCMenu::create();

            if (!usernameNotInMenu) {
                usernameLabel = mainMenu->getChildByID("username-button");
                usernameLabel->setContentHeight(usernameLabel->getContentHeight() - 5.f);
                userMenu->setPositionY(usernameLabel->getPositionY() - 2.f);
            } else {
                usernameLabel = m_mainLayer->getChildByID("username-label");
                usernameLabel->setContentHeight(usernameLabel->getContentHeight() - 5.f);
                userMenu->setPositionY(- winSize.height / 2 + 25.f);
            }

            if (!smallCommentsMode) userMenu->setPositionY(- (winSize.height / 2) + 60.f);

            if(auto playerIcon = m_mainLayer->getChildByType<SimplePlayer>(0)) {
                auto iconSpr = playerIcon->getChildByType<CCSprite>(0);
                playerIcon->setContentSize({40, 40}); // to make it work with layouts
                iconSpr->setPosition(ccp(playerIcon->getContentWidth() / 2.f, playerIcon->getContentHeight() / 2.f));
                if (auto robotSpr = playerIcon->getChildByType<GJRobotSprite>(0)) robotSpr->setPosition(ccp(20.f, 20.f));
                playerIcon->removeFromParent();
                playerIcon->setZOrder(-1);
                playerIcon->setLayoutOptions(AxisLayoutOptions::create()->setAutoScale(false));
                playerIcon->setID("player-icon");

                userMenu->addChild(playerIcon);
            }

            userMenu->setID("user-menu");
            userMenu->setLayout(RowLayout::create()->setAxisAlignment(AxisAlignment::Center)->setGap(5.f)->setAutoScale(false)->setCrossAxisOverflow(false));
            userMenu->setPositionX(- (winSize.width / 2) + 171.f);
            userMenu->setContentSize({320, 30});

            mainMenu->addChild(userMenu);

            auto usernameMenu = CCMenu::create();
            usernameMenu->setID("username-menu");
            usernameMenu->setLayout(RowLayout::create()->setAxisAlignment(AxisAlignment::Start)->setGap(2.f)->setAutoScale(false)->setCrossAxisOverflow(false));
            usernameMenu->setPositionY(usernameLabel->getPositionY() - 2.f);
            usernameMenu->setPositionX(-114.f);
            usernameMenu->setContentSize({320, 30});

            size_t usernameMenuIdx = 0;

            switchToMenu(usernameLabel, usernameMenu);
            setIDSafe(usernameMenu, usernameMenuIdx++, "username-button");

            if (m_comment->m_modBadge > 0 && !m_accountComment) {
                switchToMenu(m_mainLayer->getChildByType<CCSprite>(0), usernameMenu);
                setIDSafe(usernameMenu, usernameMenuIdx++, "mod-badge");
            }

            if (m_comment->m_percentage > 0 && !m_accountComment) {
                switchToMenu(m_mainLayer->getChildByType<CCLabelBMFont>(0), usernameMenu);
                setIDSafe(usernameMenu, usernameMenuIdx++, "percentage-label");
            }

            userMenu->addChild(usernameMenu);

            usernameMenu->updateLayout();
            userMenu->updateLayout();
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

        this->setID("");
        NodeIDs::get()->provide(this);
    }
};