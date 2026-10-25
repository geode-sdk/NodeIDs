#pragma once

#include <Geode/cocos/base_nodes/CCNode.h>

using namespace geode::prelude;

namespace geode::node_ids {

class Spacer : public CCNode{
public:
    static Spacer* create(const CCSize& size, int zOrder = 0) {
        auto ret = new Spacer();
        ret->autorelease();
        ret->setContentSize(size);
        ret->setAnchorPoint({0.5f, 0.5f});
        ret->setZOrder(zOrder);
        return ret;
    }
};

};