//
//  SkillLayer.cpp
//  block
//
//  Created by TonyKID on 12-10-22.
//
//
//tag 1 技能按钮
//skill_type:
//1:解除石化
//2:透视
//3:减速
//4:鼓舞
//5:攻击
//


#include "SkillLayer.h"

using namespace cocos2d;

bool SkillLayer::init(){
    if (!CCLayer::init()) {
        return false;
    }
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite* skillframe = CCSprite::create("Icon-small-50.png");
    skillframe->setPosition(ccp(20, screenSize.width/2));
    this->addChild(skillframe,-1,TypeUnRock);
    
    this->setTouchEnabled(true);
    return true;
}

bool SkillLayer::isTouchForMe(CCPoint touchLocation){
    CCNode* node = this->getChildByTag(1);
    CCRect rec = node->boundingBox();
    return CCRect::CCRectContainsPoint(rec, touchLocation);
}

void SkillLayer::ccTouchesEnded(CCSet* touches, CCEvent* event){
    CCTouch* pTouch = (CCTouch*)(touches->anyObject());
    CCPoint point = pTouch->getLocationInView();
    point = CCDirector::sharedDirector()->convertToGL(point);
    bool isTouchHandeled = this->isTouchForMe(point);
    if (isTouchHandeled) {
        this->consumeResource(TypeUnRock);
        CCNode* node = this->getChildByTag(TypeUnRock);
        //node->setVisible(false);
    }
}

//根据技能类型获得所需的资源（三位分别代表：绿红黄）
int getConsumeByType(int skill_type){
    switch (skill_type) {
        case 1:
            return 111;
            break;
            
        case 2:
            return 111;
            break;
            
        case 3:
            return 111;
            break;
            
        case 4:
            return 111;
            break;
            
        case 5:
            return 111;
            break;
            
        default:
            break;
    }
}

void SkillLayer::consumeResource(Type t){
    int res = getConsumeByType(t);
    this->share_board->_resourceBar1->consumeResource(res/100);
    this->share_board->_resourceBar2->consumeResource(res/10-(res/100)*10);
    this->share_board->_resourceBar3->consumeResource(res-(res/10)*10);
}