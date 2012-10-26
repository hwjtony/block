//
//  board.h
//  block
//
//  Created by TonyKID on 12-10-9.
//
//

#ifndef __BOARD_H__
#define __BOARD_H__

#include "cocos2d.h"
#include "Card.h"
#include "ResourceBar.h"
using namespace cocos2d;

class board:public cocos2d::CCObject{
public:
    bool initSize(int x,int y);
    CCArray* initBoard();
    void changeSpriteTexture(Card* card);
    Card* clickBlock(CCTouch* touch);
    CCArray* getSprites();
    
    bool setLastClickedCard(Card* card);
    Card* getLastClickedCard();
    void deblockLogic(Card* lastClickedCard, Card* targetCard);
    
    int column;
    int row;
    int addCompleteFlag=1;
    CCLayer* boardLayer;
    ResourceBar* _resourceBar1;//绿
    ResourceBar* _resourceBar2;//红
    ResourceBar* _resourceBar3;//黄
    int* columnTops;
    Card* lastClickedCard;
    Card* targetCard;
    CCArray* sprites;
    CCArray* cards = new CCArray;
    CCArray* need_move = new CCArray;
    CCTexture2D* m_cache[5];
    void removeCard();
    void doRemove(Card* card);
    void renewCard();
    void addRow();
    void addComplete();
    int getColumnTop(int column);
    void dropLogic();
};

#endif /* defined(__block__board__) */
