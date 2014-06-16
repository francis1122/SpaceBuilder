//
//  BaseObject.h
//  RogueDeck
//
//  Created by Hunter Francis on 1/7/14.
//
//

#ifndef __RogueDeck__BaseObject__
#define __RogueDeck__BaseObject__

#include "cocos2d.h"

USING_NS_CC;

class BaseObject : public cocos2d::CCSprite
{
public:
    
    bool initDefaultState();
    bool isZoomed;
    bool isInteractive;

    void removeBaseObject();
    virtual void doDamage();
    
    //used to keep track of passive stat changes from cards
    CCArray *cardsAffectingNode;
    
    
};

#endif /* defined(__RogueDeck__BaseObject__) */
