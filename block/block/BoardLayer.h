//
//  BoardLayer.h
//  block
//
//  Created by TonyKID on 12-10-23.
//
//

#ifndef __block__BoardLayer__
#define __block__BoardLayer__

#include "cocos2d.h"
#include "board.h"
#include "ResourceBar.h"

using namespace cocos2d;
class BoardLayer : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    NODE_FUNC(BoardLayer);
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    //static cocos2d::CCScene* scene();
    
    // a selector callback
    
    //cocos2d::CCArray* scene_board;
    board* share_board;
    // implement the "static node()" method manually
    CREATE_FUNC(BoardLayer);
    void ccTouchesEnded(cocos2d::CCSet* touches,cocos2d::CCEvent* event);
    void test();
    void addRow();
};

#endif /* defined(__block__BoardLayer__) */
