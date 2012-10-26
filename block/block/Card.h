//
//  Card.h
//  block
//
//  Created by TonyKID on 12-10-11.
//
//

#ifndef __CARD_H__
#define __CARD_H__

#include "cocos2d.h"
using namespace cocos2d;

class Card:public cocos2d::CCNode{
private:
    CCSprite* MySprite;
    int color;
    int pattern;
    
public:
    int index;
    float position_y;
    Card(CCTexture2D* m_cache[5]);
    void setPattern(int i);
    int getPattern();
    void setColor(int i);
    int getColor();
    CCSprite* getSprite();
    CCSpriteFrame* animFrames[1];
};

#endif /* defined(__block__board__) */
