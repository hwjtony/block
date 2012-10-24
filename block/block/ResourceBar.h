//
//  ResourceBar.h
//  block
//
//  Created by TonyKID on 12-10-19.
//
//

#ifndef __block__ResourceBar__
#define __block__ResourceBar__

#include "cocos2d.h"
using namespace cocos2d;

class ResourceBar:public cocos2d::CCSprite{
public:
    int resource_count = 0;
    int bar_type;
    int resource_max = 10;
    virtual bool myInit(int type);
    void reset();
    void addResource();
    void consumeResource(int num);
    virtual void update(float dt);
    static CCSprite* spriteWithFile(const char *pszFileName);
    static CCSprite* ResourceWithType(int type);
};


#endif /* defined(__block__ResourceBar__) */
