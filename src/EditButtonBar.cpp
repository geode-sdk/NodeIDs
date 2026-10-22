#include <Geode/Bindings.hpp>
#include <Geode/Enums.hpp>
#include <Geode/modify/EditButtonBar.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

struct EditButtonBarIDs : Modify<EditButtonBarIDs, EditButtonBar> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("EditButtonBar::loadFromItems", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set EditButtonBar::loadFromItems hook priority, node IDs may not work properly");
        }
    }

    void loadFromItems(cocos2d::CCArray* objects, int rows, int columns, bool keepPage) {
        EditButtonBar::loadFromItems(objects, rows, columns, keepPage);

        auto winSize = CCDirector::get()->getWinSize();

        auto arrowsMenu = setIDSafe<CCMenu>(this, 0, "arrows-menu");
        auto dotsMenu = setIDSafe<CCMenu>(this, 1, "dots-menu");

        float fullWidth = winSize.width - 208.f;
        float width = fullWidth;

        setContentSize({fullWidth, 90.f});
        setAnchorPoint({0.5f, 0.f});

        if (arrowsMenu) {
            width = (winSize.width - 240.f);

            float rowGap = columns * 4.f - 4.f;
            float acrossScale = ((width - rows * 4.f - 4.f) / static_cast<float>(rows)) / 40.f;
            float scale = ((78.f - rowGap) / static_cast<float>(columns)) / 40.f;
            
            if (acrossScale <= scale) scale = acrossScale;

            float size = scale * 40.f;
            float arrowY = m_position.y - (static_cast<float>(columns) * size + rowGap) / 2.f;

            setIDs(arrowsMenu, 0,
                "left-button",
                "right-button"
            );

            arrowsMenu->ignoreAnchorPointForPosition(false);
            arrowsMenu->setPosition({getContentWidth() / 2.f, arrowY});
            arrowsMenu->setContentWidth(fullWidth);

            arrowsMenu->setLayout(SimpleRowLayout::create()
                ->setMainAxisScaling(AxisScaling::None)
                ->setCrossAxisScaling(AxisScaling::Fit)
                ->setMainAxisAlignment(MainAxisAlignment::Between)
            );

            arrowsMenu->updateLayout();
        }

        if (m_scrollLayer) {
            m_scrollLayer->setID("scroll-layer");
            m_scrollLayer->setContentSize({width, 90.f});
            m_scrollLayer->ignoreAnchorPointForPosition(false);
            m_scrollLayer->setPosition(getContentSize() / 2.f);

            m_scrollLayer->m_position = m_scrollLayer->getPosition();

            m_scrollLayer->m_extendedLayer->setContentSize(m_scrollLayer->getContentSize());
            m_scrollLayer->m_extendedLayer->ignoreAnchorPointForPosition(false);
            m_scrollLayer->m_extendedLayer->setAnchorPoint({0.f, 0.f});
            m_scrollLayer->m_extendedLayer->setPosition({0.f, 0.f});
            m_scrollLayer->m_extendedLayer->setID("extended-layer");

            m_scrollLayer->m_dotPosition.x = m_scrollLayer->getContentWidth() / 2.f;

            auto dots = setIDSafe<CCSpriteBatchNode>(m_scrollLayer, 0, "dots-batch");
            if (dots) {
                int idx = 0;
                for (auto node : dots->getChildrenExt()) {
                    node->setID(fmt::format("page-{}-dot", idx));
                    idx++;
                }

                dots->setAnchorPoint({0.5f, 0.f});
                dots->setPosition({getContentWidth() / 2.f, 0.f});
                dots->setContentSize({m_scrollLayer->getContentWidth(), 3.2f});
            }

            int idx = 0;
            for (auto page : m_scrollLayer->m_pages->asExt<ButtonPage>()) {
                page->setContentSize(m_scrollLayer->m_extendedLayer->getContentSize());
                page->ignoreAnchorPointForPosition(false);
                page->setID(fmt::format("page-{}", idx));

                auto menu = setIDSafe<CCMenu>(page, 0, "button-menu");
                if (menu) {
                    menu->ignoreAnchorPointForPosition(false);
                    menu->setContentSize(page->getContentSize());
                    menu->setPosition(page->getContentSize() / 2.f);

                    for (auto item : menu->getChildrenExt()) {
                        item->setPosition(item->getPosition() + CCPoint{menu->getContentWidth() / 2.f, menu->getContentHeight() * 2 - item->getContentHeight() / 2.f});
                        if (m_hasCreateItems) {
                            item->setID(fmt::format("object-{}-button", static_cast<CreateMenuItem*>(item)->m_objectID));
                        }
                    }
                }

                idx++;
            }
        }

        if (dotsMenu) {
            for (auto node : dotsMenu->getChildrenExt()) {
                node->setID(fmt::format("page-{}-dot", node->getTag()));
            }

            dotsMenu->setAnchorPoint({0.5f, 0.f});
            dotsMenu->setPosition({getContentWidth() / 2.f, 0.f});

            dotsMenu->setLayout(SimpleRowLayout::create()
                ->setGap(12.8f)
                ->setMainAxisScaling(AxisScaling::Fit)
                ->setCrossAxisScaling(AxisScaling::Fit)
            );

            dotsMenu->updateLayout();
        }

    }
};