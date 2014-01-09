//
//  AnimationManager.h
//  RogueDeck
//
//  Created by Hunter Francis on 1/7/14.
//
//

#ifndef __RogueDeck__AnimationManager__
#define __RogueDeck__AnimationManager__

#include "cocos2d.h"
#include "BaseObject.h"
USING_NS_CC;

class BaseObject;
class AnimationObject;
class AnimationManager : public BaseObject
{
private:
    //Constructor
    AnimationManager();
    
    //Instance of the singleton
    static AnimationManager* m_mySingleton;
    
public:
    //Get instance of singleton
    static AnimationManager* sharedAnimationManager();
    void resetAnimationManager();
    
    bool animationInProgress;
    
    void addAnimation(AnimationObject *object);
    void updateAnimations();
    void runAnimation(AnimationObject *animation);
    
  //  void addCard(CCNode *node);
  //  void removeCard(CCNode *node);
    
private:
    CCArray *animationQueue;
    
//    MonsterSprite* createMonster(float powerLevel);
    
    
};

#endif /* defined(__RogueDeck__AnimationManager__) */
