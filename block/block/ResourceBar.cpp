//
//  ResourceBar.cpp
//  block
//
//  Created by TonyKID on 12-10-19.
//
//

#include "ResourceBar.h"

using namespace cocos2d;

bool ResourceBar::myInit(int type){CCLog("resource");
    this->bar_type = type;
    this->setVisible(true);
    this->scheduleUpdate();
    return true;
}

void ResourceBar::update(float dt){
    this->setScaleY(resource_count/10.0);
}

/*CCSprite* ResourceBar::spriteWithFile(const char *pszFileName)
{
    ResourceBar *pobSprite = new ResourceBar();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->myInit();
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}
*/
CCSprite* ResourceBar::ResourceWithType(int type){
    CCTexture2D* r_cache[3];
    r_cache[0] = CCTextureCache::sharedTextureCache()->addImage("resource_green.png");
    r_cache[1] = CCTextureCache::sharedTextureCache()->addImage("resource_red.png");
    r_cache[2] = CCTextureCache::sharedTextureCache()->addImage("resource_yellow.png");
    ResourceBar *pobSprite = new ResourceBar();
    if (pobSprite && pobSprite->initWithTexture(r_cache[type]))
    {
        pobSprite->myInit(type);
        pobSprite->setPosition(ccp(10*(type+1), 5));
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void ResourceBar::addResource(){
    this->resource_count++;
    if (this->resource_count>this->resource_max) {
        this->resource_count = this->resource_max;
    }
}

void ResourceBar::consumeResource(int num){
    this->resource_count -= num;
    if (this->resource_count<0) {
        this->resource_count = 0;
    }
}