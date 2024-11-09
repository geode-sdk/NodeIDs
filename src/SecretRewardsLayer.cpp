//TODO: fix for 2.207 crashes on line 17
#include <Geode/Bindings.hpp>
#include <Geode/modify/SecretRewardsLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

// TODO: Add IDs to individual chest rooms

void assignIDsToStore(CCMenuItemSpriteExtra* store, int storeNum) {
  switch (storeNum) {
    case 0:
      store->setID("scratch-shop");
      break;
    case 1:
      store->setID("creator-shop");
      break;
    case 2:
      store->setID("mechanic-shop"); // suffix "-shop" merely for consistency
      break;
    case 3:
      store->setID("diamond-shop");
      break;
  }

  auto sprite = store->getChildByType<CCSprite>(0);
  sprite->setID("store-sprite");

  // CCNode *node = NULL;
  // CCARRAY_FOREACH(sprite->getChildren(), node)
  // {
  //   node->setID("rope");
  // }
}

void assignIDsToPage(CCLayer* page, int pageNum) {
  auto winSize = CCDirector::sharedDirector()->getWinSize();

  page->setID("page" + std::to_string(pageNum + 1));

  if (pageNum == 3) { // store page
    if (auto menu = page->getChildByType<CCMenu>(0)) {
      menu->setID("store-menu");

      // make this a row layout in case people want to add their own shops here
      menu->setPosition(winSize.width / 2, winSize.height - 100);
      menu->setLayout(
        RowLayout::create()
          ->setGap(24.f)
      );
      menu->updateLayout();

      assignIDsToStore(menu->getChildByType<CCMenuItemSpriteExtra>(0), 0);
      assignIDsToStore(menu->getChildByType<CCMenuItemSpriteExtra>(1), 1);
      assignIDsToStore(menu->getChildByType<CCMenuItemSpriteExtra>(2), 2);
      assignIDsToStore(menu->getChildByType<CCMenuItemSpriteExtra>(3), 3);
    }
    return;
  }

  if (auto menu = page->getChildByType<CCMenu>(0)) {
    menu->setID("chests-menu");

    setIDSafe<CCMenuItemSpriteExtra>(menu, 0, ("chest" + std::to_string(pageNum * 3 + 1)).c_str());
    setIDSafe<CCMenuItemSpriteExtra>(menu, 1, ("chest" + std::to_string(pageNum * 3 + 2)).c_str());
    setIDSafe<CCMenuItemSpriteExtra>(menu, 2, ("chest" + std::to_string(pageNum * 3 + 3)).c_str());
  }

  setIDSafe<CCLabelBMFont>(page, 0, ((pageNum == 2 ? "chest" : "chest" + std::to_string(pageNum * 3 + 1)) + "-counter").c_str()); // on all pages
  if (pageNum < 2) { // only on page 0 & 1
    setIDSafe<CCLabelBMFont>(page, 1, ((pageNum == 2 ? "milestone100" : "chest" + std::to_string(pageNum * 3 + 2)) + "-counter").c_str());
    setIDSafe<CCLabelBMFont>(page, 2, ((pageNum == 2 ? "milestone200" : "chest" + std::to_string(pageNum * 3 + 3)) + "-counter").c_str());
  }

  // don't mind the first three indeces down there, for some reason the third page mixes them up idk
  // also these calls are pretty repetitive so they are all in 1 line bc wrapping them looks frankly disgusting lol
  setIDSafe<CCSprite>(page, pageNum == 2 ? 2 : 0, pageNum == 2 ? "chest-icon" : "tier-indicator");
  setIDSafe<CCSprite>(page, pageNum == 2 ? 0 : 1, ((pageNum == 2 ? "milestone50"  : "chest" + std::to_string(pageNum * 3 + 1)) + "-platform").c_str());
  setIDSafe<CCSprite>(page, pageNum == 2 ? 1 : 2, ((pageNum == 2 ? "milestone50"  : "chest" + std::to_string(pageNum * 3 + 1)) + "-cost"    ).c_str());
  setIDSafe<CCSprite>(page, 3,                    ((pageNum == 2 ? "milestone100" : "chest" + std::to_string(pageNum * 3 + 2)) + "-platform").c_str());
  setIDSafe<CCSprite>(page, 4,                    ((pageNum == 2 ? "milestone100" : "chest" + std::to_string(pageNum * 3 + 2)) + "-cost"    ).c_str());
  setIDSafe<CCSprite>(page, 5,                    ((pageNum == 2 ? "milestone200" : "chest" + std::to_string(pageNum * 3 + 3)) + "-platform").c_str());
  setIDSafe<CCSprite>(page, 6,                    ((pageNum == 2 ? "milestone200" : "chest" + std::to_string(pageNum * 3 + 3)) + "-cost"    ).c_str());
}

$register_ids(SecretRewardsLayer) {    
    if (auto menu = this->getChildByType<CCLayer>(0)) {
      menu->setID("main-contents");

      if (auto scrollLayer = menu->getChildByType<CCLayer>(0)) {
        scrollLayer->setID("scroll-layer");
        
        if (auto pages = scrollLayer->getChildByType<ExtendedLayer>(0)) {
          pages->setID("pages");
          setIDSafe<cocos2d::CCSprite>(menu, 0, "title-label");

          assignIDsToPage(pages->getChildByType<CCLayer>(0), 0);
          assignIDsToPage(pages->getChildByType<CCLayer>(1), 1);
          assignIDsToPage(pages->getChildByType<CCLayer>(2), 2);
          assignIDsToPage(pages->getChildByType<CCLayer>(3), 3);
        }
        
        if (auto pageCircleWrapper = scrollLayer->getChildByType<cocos2d::CCSpriteBatchNode>(0)) {
          pageCircleWrapper->setID("page-circles");

          setIDSafe<CCSprite>(pageCircleWrapper, 0, "page1");
          setIDSafe<CCSprite>(pageCircleWrapper, 1, "page2");
          setIDSafe<CCSprite>(pageCircleWrapper, 2, "page3");
          setIDSafe<CCSprite>(pageCircleWrapper, 3, "page4");
        }
      }
    }

    if (auto pageNav = this->getChildByType<CCMenu>(1)) {
      pageNav->setID("page-navigation");

      setIDSafe<CCMenuItemSpriteExtra>(pageNav, 0, "left");
      setIDSafe<CCMenuItemSpriteExtra>(pageNav, 1, "right");
    }

    setIDSafe<CCSprite>(this, 0, "background");
    setIDSafe<CCSprite>(this, 1, "top-right-art");
    setIDSafe<CCSprite>(this, 2, "top-left-art");
    setIDSafe<CCSprite>(this, 3, "key-icon");
    setIDSafe<CCSprite>(this, 4, "floor");
    setIDSafe<CCLabelBMFont>(this, 0, "key-count");
    setIDSafe<CCMenu>(this, 0, "exit-menu");
};

struct SecretRewardsLayerIDs : Modify<SecretRewardsLayerIDs, SecretRewardsLayer> {
  static void onModify(auto &self) {
    if (!self.setHookPriority("SecretRewardsLayer::init", GEODE_ID_PRIORITY)) {
      log::warn("Failed to set SecretRewardsLayer::init hook priority, node IDs may "
                "not work properly");
    }
  }
  bool init(bool p0) {
    if (!SecretRewardsLayer::init(p0))
      return false;
    NodeIDs::get()->provide(this);
    return true;
  }
};
