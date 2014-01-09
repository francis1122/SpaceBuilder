//
//  AnimationObject.h
//  RogueDeck
//
//  Created by Hunter Francis on 1/7/14.
//
//

#ifndef __RogueDeck__AnimationObject__
#define __RogueDeck__AnimationObject__

#include "cocos2d.h"
#include "BaseObject.h"

USING_NS_CC;


class AnimationObject : public CCObject
{
public:
    virtual bool init();
    virtual bool init(CCFiniteTimeAction *_action, BaseObject *_object );
    
    CC_SYNTHESIZE_RETAIN(CCFiniteTimeAction *, action, Action);
    CC_SYNTHESIZE_RETAIN(BaseObject *, object, Object);
    bool isArray;
    float duration;
    CCArray *animationArray;
    
    void addAnimation(AnimationObject *animationObject);
};

#endif /* defined(__RogueDeck__AnimationObject__) */
