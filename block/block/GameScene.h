#ifndef __GameScene_SCENE_H__
#define __GameScene_SCENE_H__

#include "cocos2d.h"
#include "board.h"
#include "ResourceBar.h"
#include "BoardLayer.h"
#include "SkillLayer.h"

using namespace cocos2d;
class GameScene : public cocos2d::CCLayer
{
/*public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    NODE_FUNC(GameScene);
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    //cocos2d::CCArray* scene_board;
    board* share_board;
    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);
    void ccTouchesEnded(cocos2d::CCSet* touches,cocos2d::CCEvent* event);
    void test();
*/
public:
    GameScene();
    virtual ~GameScene();
    
    virtual bool init();
    static CCScene *scene();
    
    CREATE_FUNC(GameScene);
    
    
    void menuCloseCallback(CCObject* pSender);
    BoardLayer* share_boardLayer;
    SkillLayer* share_skillLayer;
    void setBoardLayer(BoardLayer* boardLayer);
    void setSkillLayer(SkillLayer* skillLayer);
    void update(cocos2d::CCTime dt);
};

#endif // __HELLOWORLD_SCENE_H__
