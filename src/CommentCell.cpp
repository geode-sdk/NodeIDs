// #include "AddIDs.hpp"

#include <Geode/Geode.hpp>
#include <Geode/modify/CommentCell.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(CommentCell) {
    if(m_comment->m_commentDeleted) return;

    auto winSize = CCDirector::sharedDirector()->getWinSize();
    
    bool smallCommentsMode = this->m_height == 36; //this is how robtop does the check
    bool usernameNotInMenu = m_comment->m_accountID <= 0 || m_accountComment || m_comment->m_hasLevelID;

    //there is a chance m_comment->m_accountID is not set properly before loadFromComment
    //but this is fixed inside loadFromComment itself, so that case is also handled

    if(!smallCommentsMode) m_mainLayer->getChildByType<CCScale9Sprite>(0)->setID("background");

    int bmfontOffset = 0;
    if(m_comment->m_modBadge > 0) {
        m_mainLayer->getChildByType<CCSprite>(0)->setID("mod-badge");
    }
    if(m_comment->m_percentage > 0) {
        m_mainLayer->getChildByType<CCLabelBMFont>(0 + bmfontOffset)->setID("percentage-label");
        bmfontOffset += 1;
    }
    if (usernameNotInMenu) {
        m_mainLayer->getChildByType<CCLabelBMFont>(0 + bmfontOffset)->setID("username-label");
        bmfontOffset += 1;
    }

    if(smallCommentsMode) {
        m_mainLayer->getChildByType<CCLabelBMFont>(0 + bmfontOffset)->setID("comment-text-label");
        bmfontOffset += 1;
    }

    if(!m_comment->m_isSpam) {
        m_mainLayer->getChildByType<CCLabelBMFont>(0 + bmfontOffset)->setID("likes-label");
        bmfontOffset += 1;
        if(!(m_comment->m_uploadDate).empty()) m_mainLayer->getChildByType<CCLabelBMFont>(0 + bmfontOffset)->setID("date-label");
        bmfontOffset += 1;
    }

    if (!m_accountComment && usernameNotInMenu) {
        m_mainLayer->getChildByType<SimplePlayer>(0)->setID("player-icon");
    }

    if(!smallCommentsMode) m_mainLayer->getChildByType<TextArea>(0)->setID("comment-text-area");

    if (auto mainMenu = m_mainLayer->getChildByType<CCMenu>(0)) {
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
                userMenu->setPositionY(-135.f);
            }

            if (!smallCommentsMode) userMenu->setPositionY(- (winSize.height / 2) + 60.f);

            auto playerIcon = m_mainLayer->getChildByType<SimplePlayer>(0);
            auto iconSpr = playerIcon->getChildByType<CCSprite>(0);
            playerIcon->setContentSize({40, 40}); // to make it work with layouts
            iconSpr->setPosition(ccp(playerIcon->getContentWidth() / 2.f, playerIcon->getContentHeight() / 2.f));
            if (auto robotSpr = playerIcon->getChildByType<GJRobotSprite>(0)) robotSpr->setPosition(ccp(20.f, 20.f));
            playerIcon->removeFromParent();
            playerIcon->setZOrder(-1);
            playerIcon->setLayoutOptions(AxisLayoutOptions::create()->setAutoScale(false));

            userMenu->setID("user-menu");
            userMenu->setLayout(RowLayout::create()->setAxisAlignment(AxisAlignment::Center)->setGap(5.f)->setAutoScale(false)->setCrossAxisOverflow(false));
            userMenu->setPositionX(- (winSize.width / 2) + 171.f);
            userMenu->setContentSize({320, 30});
            userMenu->addChild(playerIcon);
            setIDSafe(userMenu, 0, "player-icon");

            mainMenu->addChild(userMenu);

            auto usernameMenu = CCMenu::create();
            usernameMenu->setID("username-menu");
            usernameMenu->setLayout(RowLayout::create()->setAxisAlignment(AxisAlignment::Start)->setGap(2.f)->setAutoScale(false)->setCrossAxisOverflow(false));
            usernameMenu->setPositionY(usernameLabel->getPositionY() - 2.f);
            usernameMenu->setPositionX(-114.f);
            usernameMenu->setContentSize({320, 30});

            switchToMenu(usernameLabel, usernameMenu);
            setIDSafe(usernameMenu, 0, "username-button");

            if (m_comment->m_modBadge > 0) {
                switchToMenu(m_mainLayer->getChildByType<CCSprite>(0), usernameMenu);
                setIDSafe(usernameMenu, 1, "mod-badge");
            }

            if (m_comment->m_percentage > 0) {
                switchToMenu(m_mainLayer->getChildByType<CCLabelBMFont>(0), usernameMenu);
                setIDSafe(usernameMenu, 2, "percentage-label");
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
