#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "SkillLayer.h"
#include "BoardLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;

GameScene::GameScene(){
    
}

GameScene::~GameScene(){
    
}

bool GameScene::init(){
    if ( !CCLayer::init() )
    {
        return false;
    }
    bool bRet = false;
    do {
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                              "CloseNormal.png",
                                                              "CloseSelected.png",
                                                              this,
                                                              menu_selector(GameScene::menuCloseCallback) );
        pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );
        
        // create menu, it's an autorelease object
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition( CCPointZero );
        this->addChild(pMenu, 1);
        this->schedule(schedule_selector(GameScene::update));
        bRet = true;
    } while (0);
    return bRet;
}

void GameScene::update(cocos2d::CCTime dt){
    share_boardLayer->share_board->dropLogic();
    CCLog("update");
}

CCScene* GameScene::scene() {
    CCScene *pScene = NULL;
    do {
        pScene = CCScene::create();
        GameScene *main = GameScene::create();
        BoardLayer *boardLayer = BoardLayer::create();
        SkillLayer *skillLayer = SkillLayer::create();
        main->share_boardLayer = boardLayer;
        main->share_skillLayer = skillLayer;
        main->share_skillLayer->share_board = main->share_boardLayer->share_board;
        
        //将main层添加到最下层
        pScene->addChild(main, 0, 1);
        //game层为中间层
        pScene->addChild(boardLayer, 1, 2);
        //ui为最上层
        pScene->addChild(skillLayer, 2, 3);
    } while (0);
    return pScene;
}



void GameScene::menuCloseCallback(CCObject* pSender)
{
    //CCDirector::sharedDirector()->end();
    CCDirector::sharedDirector()->replaceScene(GameScene::scene());
    //#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
    //#endif
}

void GameScene::setBoardLayer(BoardLayer* boardLayer){
    
}
void GameScene::setSkillLayer(SkillLayer* skillLayer){
    
}

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
}

// on "init" you need to initialize your instance
bool GameScene::init()
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
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(GameScene::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
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
    b->gameScene = this;
    b->_resourceBar1 = resourceBar1;
    b->_resourceBar2 = resourceBar2;
    b->_resourceBar3 = resourceBar3;
    share_board = b;
    b->initSize(4, 5);
    CCArray* cards = b->initBoard();
    for (int i = 0; i < cards->count(); i++) {
        Card* card = (Card*) cards->objectAtIndex(i);
        CCSprite* sprite = card->getSprite();
        this->addChild(sprite, 0);
    }
    CCLog("init ended");
    return true;
}

void GameScene::menuCloseCallback(CCObject* pSender)
{
    //CCDirector::sharedDirector()->end();
    CCDirector::sharedDirector()->replaceScene(GameScene::scene());
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
//#endif
}

void GameScene::test(){
    CCLog("test");
}



void GameScene::ccTouchesEnded(CCSet* touches, CCEvent* event){   
    CCTouch* touch = (CCTouch*)(touches->anyObject());
    board* b = share_board;
    Card* targetCard = b->clickBlock(touch);
    if (targetCard) {
        CCSprite* targetSprite = targetCard->getSprite();
        //b->setLastClickedCard(targetCard);
        //this->removeChild(targetSprite, true);
    }
}
*/