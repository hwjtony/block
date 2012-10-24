//
//  SkillLayer.h
//  block
//
//  Created by TonyKID on 12-10-22.
//
//

#ifndef __block__SkillLayer__
#define __block__SkillLayer__

#include "cocos2d.h"
#include "board.h"
#include "ResourceBar.h"

using namespace cocos2d;

typedef enum{
    TypeMin=0,
    TypeUnRock,
    TypePerspection,
    TypeSlowSpeed,
    TypeBuffUp,
    TypeAttack,
    TypeMax,
}Type;

class SkillLayer : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    NODE_FUNC(SkillLayer);
    CREATE_FUNC(SkillLayer);
    bool isTouchForMe(CCPoint touchLocation);
    //void registerWithTouchDispatcher();
    //bool ccTouchBegan(cocos2d::CCTouch* pTouch,cocos2d::CCEvent* pEvent);
    void ccTouchesEnded(cocos2d::CCSet* touches,cocos2d::CCEvent* event);
    board* share_board;
    void consumeResource(Type t);
};

#endif /* defined(__block__SkillLayer__) */
