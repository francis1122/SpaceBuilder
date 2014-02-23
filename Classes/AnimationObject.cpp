//
//  AnimationObject.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/7/14.
//
//

#include "AnimationObject.h"

#include "CardSprite.h"
#include "CardTargets.h"
#include "Action.h"

USING_NS_CC;


bool AnimationObject::init()
{
    animationArray = new CCArray();
    animationArray->init();
    isArray = true;
    duration = 0.3;
    return true;
}

// on "init" you need to initialize your instance
bool AnimationObject::init(CCFiniteTimeAction *_action, BaseObject *_object)
{
    isArray = false;
    duration = -1.0;
    this->setNodeObject(NULL);
    this->setObject(_object);
    this->setAction(_action);
    this->setDebugString(CCString::create("nothing"));
    return true;
}

bool AnimationObject::initWithNode(CCFiniteTimeAction *_action, CCNode *_object)
{
    isArray = false;
    duration = -1.0;
    this->setObject(NULL);
    this->setNodeObject(_object);
    this->setAction(_action);
    this->setDebugString(CCString::create("nothing"));
    return true;
}

void AnimationObject::addAnimation(AnimationObject *animationObject)
{
/*    float objectDuration = animationObject->action->getDuration();
    if(objectDuration > duration){
        duration = objectDuration;
    }*/
    this->animationArray->addObject(animationObject);
}


