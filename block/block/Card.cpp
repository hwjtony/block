//
//  board.cpp
//  block
//
//  Created by TonyKID on 12-10-9.
//
//

#include "Card.h"

using namespace cocos2d;

Card::Card(CCTexture2D* m_cache[4]){
    //MySprite = CCSprite::createWithTexture(m_cache[0]);
    this->pattern = rand()%2+3;
    this->color = rand()%3;
    MySprite = CCSprite::createWithTexture(m_cache[this->color]);
}

CCSprite* Card::getSprite(){
    return this->MySprite;
}

int Card::getPattern(){
    return this->pattern;
}

int Card::getColor(){
    return this->color;
}