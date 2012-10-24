//
//  board.cpp
//  block
//
//  Created by TonyKID on 12-10-9.
//
//
#include "board.h"
#include "Card.h"


using namespace cocos2d;

CCArray* board::initBoard(){
    CCDirector* director = CCDirector::sharedDirector();
    CCSize winSize = director->getWinSize();
    m_cache[0] = CCTextureCache::sharedTextureCache()->addImage("card_green.png");
    m_cache[1] = CCTextureCache::sharedTextureCache()->addImage("card_red.png");
    m_cache[2] = CCTextureCache::sharedTextureCache()->addImage("card_yellow.png");
    m_cache[3] = CCTextureCache::sharedTextureCache()->addImage("test_image.png");
    m_cache[4] = CCTextureCache::sharedTextureCache()->addImage("r2-ipad.png");
    this->columnTops = new int[column];
    for (int i = 0; i < column; i ++) {
        this->columnTops[i] = row;
    }
    
    
    for (int y = 0; y < row; y++) {
        for (int x = 0; x < column; x++) {
            //CCSprite* sprite = CCSprite::create("Icon-Small-50.png");
            //CCSprite* sprite = CCSprite::createWithTexture(m_cache[0]);
            Card* card = new Card(m_cache);
            card->index = x+column*y;
            CCSprite* sprite = card->getSprite();
            float spriteW = sprite->getContentSize().width;
            float spriteH = sprite->getContentSize().height;
            sprite->setPosition(ccp(winSize.width/2-column*spriteW/2+x*spriteW+spriteW/2,y*spriteH+spriteH/2));
            //sprites->addObject(sprite);
            cards->addObject(card);
        }
        
    }
    return cards;
}

void board::addRow(){
    CCDirector* director = CCDirector::sharedDirector();
    CCSize winSize = director->getWinSize();
    for (int x = 0; x < column; x++) {
        //CCSprite* sprite = CCSprite::create("Icon-Small-50.png");
        //CCSprite* sprite = CCSprite::createWithTexture(m_cache[0]);
        Card* card = new Card(m_cache);
        card->index = row*column+x;
        CCSprite* sprite = card->getSprite();
        float spriteW = sprite->getContentSize().width;
        float spriteH = sprite->getContentSize().height;
        sprite->setPosition(ccp(winSize.width/2-column*spriteW/2+x*spriteW+spriteW/2,this->columnTops[x]*spriteH+spriteH/2));
        //sprites->addObject(sprite);
        columnTops[x]++;
        cards->addObject(card);
        gameScene->addChild(sprite,0);
    }
    this->row++;
    CCLog("%d",this->cards->count());
}

int board::getColumnTop(int col){
    
}

bool board::initSize(int x, int y){
    //sprites = new CCArray();
    cards = new CCArray();
    row = y;
    column = x;
}

Card* board::clickBlock(CCTouch* touch){
    Card* card = (Card*)cards->objectAtIndex(0);
    CCSprite* sprite = card->getSprite();
    CCSize size = sprite->getContentSize();
    for (int y = 0; y < row; y++) {
        for (int x= 0; x < column; x++) {
            //CCSprite* targetSprite = (CCSprite*) sprites->objectAtIndex(y*column+x);
            Card* targetCard = (Card*) cards->objectAtIndex(y*column+x);
            CCSprite* targetSprite = targetCard->getSprite();
            if (targetSprite->isVisible()) {//如果卡片未被消去
                CCPoint pos = targetSprite->getPosition();
                CCRect rect = CCRectMake(pos.x - size.width / 2, pos.y - size.height / 2, size.width, size.height);
                CCPoint touchPoint = touch->getLocationInView();
                touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
                
                bool flag = CCRect::CCRectContainsPoint(rect, touchPoint);
                if (flag) {
                    //this->changeSpriteTexture(targetCard);
                    this->deblockLogic(this->getLastClickedCard(),targetCard);
                    return targetCard;
                }
            }
        }
    }
    return NULL;
}

CCArray* board::getSprites(){
    return sprites;
}

Card* board::getLastClickedCard(){
    return lastClickedCard;
}

bool board::setLastClickedCard(Card* card){
    this->lastClickedCard = card;
    return true;
}

void board::changeSpriteTexture(Card* card){
    CCSprite* sprite = card->getSprite();
    int type = card->getPattern();
    CCLog("%d",type);
    sprite->setTexture(m_cache[type]);
}

void board::doRemove(Card* card){
    card->getSprite()->setVisible(false);
    int type = card->getColor();
    if (type == 0) {
        _resourceBar1->addResource();
    }else if (type == 1){
        _resourceBar2->addResource();
    }else{
        _resourceBar3->addResource();
    }
    CCParticleSystem* m_emitter = new CCParticleSystemQuad();
    gameScene->addChild(m_emitter, 10);
    m_emitter->initWithFile("ExplodingRing.plist");
    m_emitter->setVisible(true);
    m_emitter->setPosition(card->getSprite()->getPosition());
}

void board::removeCard(){
    this->doRemove(this->lastClickedCard);
    this->doRemove(this->targetCard);
    CCSprite* sprite = lastClickedCard->getSprite();
    CCSize size = sprite->getContentSize();
    int lastIndex = this->lastClickedCard->index;
    int targetIndex = this->targetCard->index;
    int type = (lastIndex-targetIndex)%column;
    float interval = 1.0;
    //drop cards
    if (type == 0) {//if two cards are in the same column
        CCLog("same column");
        int card_num = abs((lastIndex-targetIndex)/column)-1;
        for (int i = 0; i < card_num; i++) {//the cards between
            int index = MIN(lastIndex, targetIndex)+(i+1)*column;
            CCActionInterval* moveBy = CCMoveBy::create(interval, CCPointMake(0, -size.height));
            ((Card*)cards->objectAtIndex(index))->getSprite()->runAction(moveBy);
            CCLog("run");
        }
        int up_index = MAX(lastIndex, targetIndex);
        for (int i = up_index+column; i<cards->count(); i+=column) {
            int index = i;
            CCActionInterval* moveBy = CCMoveBy::create(interval, CCPointMake(0, -2*size.height));
            ((Card*)cards->objectAtIndex(index))->getSprite()->runAction(moveBy);
        }
        this->columnTops[lastIndex%column]-=2;
    }else{//in the different column
        for (int i = lastIndex+column; i<cards->count(); i+=column) {
            int index = i;
            CCActionInterval* moveBy = CCMoveBy::create(interval, CCPointMake(0, -size.height));
            ((Card*)cards->objectAtIndex(index))->getSprite()->runAction(moveBy);
        }
        for (int i = targetIndex+column; i<cards->count(); i+=column) {
            int index = i;
            CCActionInterval* moveBy = CCMoveBy::create(interval, CCPointMake(0, -size.height));
            ((Card*)cards->objectAtIndex(index))->getSprite()->runAction(moveBy);
        }
        this->columnTops[targetIndex%column]-=1;
        this->columnTops[lastIndex%column]-=1;
        CCLog("different column");
    }
    CCLog("%d%d%d",this->columnTops[0],this->columnTops[1],this->columnTops[2]);
    
    
    this->lastClickedCard = NULL;
    this->gameScene->setTouchEnabled(true);
    //_resourceBar1->resource_count++;
}

void board::renewCard(){
    this->lastClickedCard->getSprite()->setTexture(m_cache[lastClickedCard->getColor()]);
    this->targetCard->getSprite()->setTexture(m_cache[targetCard->getColor()]);
    this->lastClickedCard = NULL;
    this->gameScene->setTouchEnabled(true);
}


void board::deblockLogic(Card *lastClickedCard, Card *targetCard){
    this->changeSpriteTexture(targetCard);
    this->targetCard = targetCard;
    CCDelayTime *delayAction = CCDelayTime::actionWithDuration(1.0f);
    if (lastClickedCard) {
        this->gameScene->setTouchEnabled(false);
        if(lastClickedCard!=targetCard){
            if (lastClickedCard->getPattern()==targetCard->getPattern()) {
                CCFiniteTimeAction* callSelectorAction = CCCallFunc::actionWithTarget(this,callfunc_selector(board::removeCard));
                targetCard->getSprite()->runAction(CCSequence:: actions(delayAction,callSelectorAction,NULL));
                
            }else{
                CCCallFunc *callSelectorAction = CCCallFunc::actionWithTarget(this,callfunc_selector(board::renewCard));
                targetCard->getSprite()->runAction(CCSequence::actions(delayAction,callSelectorAction,NULL));
                
            }
        }else{
            this->setLastClickedCard(targetCard);
            this->gameScene->setTouchEnabled(true);
        }
    }else{
        this->setLastClickedCard(targetCard);
    }
}
