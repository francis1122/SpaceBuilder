//
//  AnimationManager.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/7/14.
//
//

#include "AnimationManager.h"

#include "Statuses.h"
#include "LLMath.h"
#include "BaseObject.h"
#include "AnimationObject.h"
#include "Constants.h"
#include "GameManager.h"
#include "DamageIcon.h"
#include "BaseObject.h"
#include "GameLayer.h"
#include "MonsterLayer.h"
#include "HandLayer.h"
#include "LabelWrapper.h"

using namespace cocos2d;

//All static variables need to be defined in the .cpp file
//I've added this following line to fix the problem
AnimationManager* AnimationManager::m_mySingleton = NULL;

AnimationManager::AnimationManager()
{
    this->animationQueue = new CCArray();
    this->animationQueue->init();
    animationInProgress = false;
}

AnimationManager* AnimationManager::sharedAnimationManager()
{
    //If the singleton has no instance yet, create one
    if(NULL == m_mySingleton)
    {
        //Create an instance to the singleton
        m_mySingleton = new AnimationManager();
        m_mySingleton->init();
    }
    
    //Return the singleton object
    return m_mySingleton;
}

void AnimationManager::resetAnimationManager()
{
    this->removeFromParentAndCleanup(true);
    animationInProgress = false;
    animationQueue->removeAllObjects();
}


void AnimationManager::addAnimation(AnimationObject *object){
    this->animationQueue->addObject(object);
    if(!animationInProgress){
        this->updateAnimations();
    }
}

void AnimationManager::updateAnimations(){
    //run the next animation in the queue
    if(this->animationQueue->count() >= 1){
        AnimationObject *animation = (AnimationObject*)animationQueue->objectAtIndex(0);
        
        CCString *test = animation->getDebugString();
        if(test){
            const char * bah = test->getCString();
            CCLog("AnimationManager::animation object %s", bah);
        }
        
        this->runAnimation(animation);
        float duration;
        if(animation->isArray || duration > 0.0){
            duration = animation->duration;
        }else{
            duration = animation->getAction()->getDuration();
        }
        animationQueue->removeObjectAtIndex(0);
        animationInProgress = true;
        
        //setup callback for when animation finishes
        CCDelayTime *delay = CCDelayTime::create(duration);
        CCCallFunc *func = CCCallFunc::create(this, SEL_CallFunc(&AnimationManager::updateAnimations));
        CCSequence *seq = CCSequence::createWithTwoActions(delay, func);
        this->runAction(seq);

        CCLog("animation");
    }else{
        CCLog("no animation");
        animationInProgress = false;
        GM->isInteractive = true;
    }
}

void AnimationManager::runAnimation(AnimationObject *animation){
    if(animation->isArray){
        CCArray *array = animation->animationArray;
        for(int i = 0; i < array->count(); i++){
            AnimationObject *nextObject = (AnimationObject*)array->objectAtIndex(i);
            this->runAnimation(nextObject);
        }
    }else{
        CCNode *object = animation->getObject();
        if(object == NULL){
            object = animation->getNodeObject();
        }

        if(animation->getObject() != NULL){
            if(!animation->getObject()->isZoomed){
                object->stopAllActions();
                animation->getObject()->runAction(animation->getAction());
            }
        }else{
            if(object != NULL){
                animation->getNodeObject()->runAction(animation->getAction());

            }
        }

    }

}

#pragma mark - helper functions

void AnimationManager::createDamageIcon(int damage ,CCPoint point){
    DamageIcon *icon = new DamageIcon();
    icon->init(damage);
    icon->autorelease();
    GM->gameLayer->addChild(icon, 1000000);
    icon->setPosition(point);
    icon->setScale(0.4);


//    CCScaleTo *action = CCScaleTo::create(.05, .4);
//    CCEaseIn *ease = CCEaseIn::create(action, 1.0);
    CCDelayTime *delay = CCDelayTime::create(.6);
    CCFadeOut *fade = CCFadeOut::create(.5);
    CCCallFunc *obj = CCCallFunc::create(icon, callfunc_selector(BaseObject::removeBaseObject));
    
    CCSequence *seq = CCSequence::create( delay, fade, obj, NULL);
    icon->runAction(seq);
/*    AnimationObject *animationObject = new AnimationObject();
    animationObject->init(seq, icon);
    animationObject->duration = .04;*/
    
    //this->addAnimation(animationObject);
}

void AnimationManager::createSoulIcon(int soul, CCPoint point){
    CCString *string = CCString::createWithFormat("+%i", soul);
    CCLabelTTF *soulGainLabel = CCLabelTTF::create(string->getCString(), Main_Font, 128);
    soulGainLabel->setColor(ccMAGENTA);

    LabelWrapper *labelWrapper = new LabelWrapper();
    labelWrapper->initWithLabel(soulGainLabel);
    labelWrapper->setPosition(point);
    GM->gameLayer->addChild(labelWrapper, 1000000);
    //    CCScaleTo *action = CCScaleTo::create(.05, .4);
    //    CCEaseIn *ease = CCEaseIn::create(action, 1.0);
    CCDelayTime *delay = CCDelayTime::create(.8);
    CCFadeOut *fade = CCFadeOut::create(.4);
    CCCallFunc *obj = CCCallFunc::create(labelWrapper, callfunc_selector(BaseObject::removeBaseObject));
    
    CCSequence *seq = CCSequence::create( delay, fade, obj, NULL);
    labelWrapper->runAction(seq);
    /*    AnimationObject *animationObject = new AnimationObject();
     animationObject->init(seq, icon);
     animationObject->duration = .04;*/
    
    //this->addAnimation(animationObject);
}


void AnimationManager::endTurnAnimation(){
    
    CCLabelTTF *label = CCLabelTTF::create("Monsters Turn", LARGE_NUMBER_FONT, 114);

    LabelWrapper *labelWrapper = new LabelWrapper();
    labelWrapper->initWithLabel(label);
    labelWrapper->setPosition(ccp(570, 250));
    GM->gameLayer->addChild(labelWrapper, 100000000);
    //    CCScaleTo *action = CCScaleTo::create(.05, .4);
    //    CCEaseIn *ease = CCEaseIn::create(action, 1.0);
    CCDelayTime *delay = CCDelayTime::create(.6);
    CCFadeOut *fade = CCFadeOut::create(1.0);
    CCCallFunc *obj = CCCallFunc::create(labelWrapper, callfunc_selector(BaseObject::removeBaseObject));
    
    CCSequence *seq = CCSequence::create( delay, fade, obj, NULL);
    labelWrapper->runAction(seq);
    /*    AnimationObject *animationObject = new AnimationObject();
     animationObject->init(seq, icon);
     animationObject->duration = .04;*/
    
    //this->addAnimation(animationObject);
}



