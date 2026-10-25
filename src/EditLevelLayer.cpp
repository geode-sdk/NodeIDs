#include <Geode/Bindings.hpp>
#include <Geode/modify/EditLevelLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(EditLevelLayer) {
    setIDs(
        this,
        0,
        "background",
        "bottom-left-art",
        "bottom-right-art",
        "level-name-background",
        "level-name-input",
        "description-background",
        "description-input",
        "emoji-menu",
        "level-edit-menu",
        "level-length",
        "level-song",
        "level-verified",
        "version-label",
        "level-id-label",
        "level-actions-menu",
        "back-menu",
        "info-button-menu"
    );

    auto winSize = CCDirector::get()->getWinSize();
    auto descBG = this->getChildByID("description-background");

    auto descMenu = CCMenu::create();
    descMenu->setID("description-menu");
    descMenu->setLayout(ColumnLayout::create());
    descMenu->setPosition(
        descBG->getPositionX() - descBG->getScaledContentSize().width / 2 - 35.f,
        descBG->getPositionY()
    );
    descMenu->setContentSize({ 40.f, 80.f });
    this->addChild(descMenu);

    if (auto menu = this->getChildByID("level-edit-menu")) {
        setIDs(menu, 0, "edit-button", "play-button", "share-button");
        if (menu->getChildrenCount() == 4) {
            auto btn = static_cast<CCNode*>(menu->getChildren()->objectAtIndex(3));
            btn->setID("update-desc-button");
            btn->retain();
            btn->removeFromParent();
            descMenu->addChild(btn);
            btn->release();
            descMenu->updateLayout();
        }
        menu->setContentSize({ winSize.width - 160.f, 100.f });
        menu->setLayout(RowLayout::create()->setGap(20.f));
    }

    bool isPlatformer = m_level->isPlatformer();

    if (auto menu = this->getChildByID("level-actions-menu")) {
        setIDs(
            menu,
            0,
            "delete-button",
            "move-to-top-button",
            "move-to-bottom-button",
            "folder-button",
            "creator-settings-button",
            "duplicate-button"
        );
        if (isPlatformer) setIDs(
            menu,
            6,
            "leaderboards-button",
            "export-button",
            "settings-button"
        );
        else setIDs(
            menu,
            6,
            "export-button",
            "death-tracker-button",
            "settings-button"
        );

        auto folderMenu = detachAndCreateMenu(
            this, "folder-menu",
            ColumnLayout::create(),
            menu->getChildByID("move-to-bottom-button"),
            menu->getChildByID("move-to-top-button"),
            menu->getChildByID("folder-button")
        );
        folderMenu->setContentSize({ 50.f, 190.f });
        folderMenu->updateLayout();
        folderMenu->setPosition(folderMenu->getPositionX(), winSize.height / 2 + 5);

        switchToMenu(menu->getChildByID("delete-button"), getChildByID("info-button-menu"));

        menu->setPosition(
            menu->getPositionX() + static_cast<CCNode*>(
                menu->getChildren()->objectAtIndex(0)
            )->getPositionX(),
            winSize.height / 2
        );
        menu->setContentSize({ 60.f, winSize.height - 100.f });
        menu->setLayout(
            ColumnLayout::create()
                ->setGap(5.f)
                ->setAxisReverse(true)
        );
        menu->setZOrder(1);
    }

    if (auto menu = this->getChildByID("back-menu")) {
        auto backBtn = setIDSafe(menu, 0, "back-button");
        menu->setPositionX(
            menu->getPositionX() + 100.f / 2 -
                getSizeSafe(backBtn).width / 2
        );
        menu->setContentSize({ 100.f, 50.f });
        menu->setLayout(
            RowLayout::create()
                ->setAxisAlignment(AxisAlignment::Start)
        );
    }

    if (auto menu = this->getChildByID("info-button-menu")) {
        setIDSafe(menu, 0, "info-button");
        setIDSafe(menu, 1, "guidelines-button");
    }
}

struct EditLevelLayerIDs : Modify<EditLevelLayerIDs, EditLevelLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("EditLevelLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set EditLevelLayer::init hook priority, node IDs may not work properly");
        }
    }

    bool init(GJGameLevel* l) {
        if (!EditLevelLayer::init(l)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};
