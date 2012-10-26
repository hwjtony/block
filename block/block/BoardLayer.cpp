//
//  BoardLayer.cpp
//  block
//
//  Created by TonyKID on 12-10-23.
//
//

#include "BoardLayer.h"
#include "SkillLayer.h"
//#include "board.h"

using namespace cocos2d;

/*CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    SkillLayer *skillLayer = SkillLayer::create();
    scene->addChild(skillLayer);
    
    // return the scene
    return scene;
}*/

// on "init" you need to initialize your instance
bool BoardLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    ResourceBar* resourceBar1 = (ResourceBar*)ResourceBar::ResourceWithType(0);
    ResourceBar* resourceBar2 = (ResourceBar*)ResourceBar::ResourceWithType(1);
    ResourceBar* resourceBar3 = (ResourceBar*)ResourceBar::ResourceWithType(2);
    //resourceBar->setPosition(ccp(5, 5));
    this->addChild(resourceBar1);
    this->addChild(resourceBar2);
    this->addChild(resourceBar3);
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    
    //CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    this->setTouchEnabled(true);
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);
    
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
    
    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    board* b = new board();
    b->boardLayer = this;
    b->_resourceBar1 = resourceBar1;
    b->_resourceBar2 = resourceBar2;
    b->_resourceBar3 = resourceBar3;
    share_board = b;
    b->initSize(4, 1);
    CCArray* cards = b->initBoard();
    for (int i = 0; i < cards->count(); i++) {
        Card* card = (Card*) cards->objectAtIndex(i);
        CCSprite* sprite = card->getSprite();
        this->addChild(sprite, 0);
    }
    float interval = 5.0f;
    this->schedule(schedule_selector(BoardLayer::addRow),interval);
    CCLog("init ended");
    return true;
}

void BoardLayer::addRow(){
    share_board->addRow();
}



void BoardLayer::test(){
    CCLog("test");
}



void BoardLayer::ccTouchesEnded(CCSet* touches, CCEvent* event){
    CCTouch* touch = (CCTouch*)(touches->anyObject());
    board* b = share_board;
    Card* targetCard = b->clickBlock(touch);
    if (targetCard) {
        CCSprite* targetSprite = targetCard->getSprite();
        //b->setLastClickedCard(targetCard);
        //this->removeChild(targetSprite, true);
    }
    
}
