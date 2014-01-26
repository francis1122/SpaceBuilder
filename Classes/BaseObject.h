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

class BaseObject : public cocos2d::CCSprite
{
public:
    
    bool initDefaultState();
    bool isZoomed;
    bool isInteractive;

    void removeBaseObject();
    
};

#endif /* defined(__RogueDeck__BaseObject__) */
