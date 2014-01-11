//
//  PlayAreaToTargetMonstersTargets.h
//  RogueDeck
//
//  Created by Hunter Francis on 1/10/14.
//
//

#ifndef __RogueDeck__PlayAreaToTargetMonstersTargets__
#define __RogueDeck__PlayAreaToTargetMonstersTargets__

#include "cocos2d.h"
#include "CardTargets.h"

class UIState;
class CardSprite;
USING_NS_CC;

class PlayAreaToTargetMonstersTargets : public CardTargets
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static node()" method manually
    CREATE_FUNC(PlayAreaToTargetMonstersTargets);
    
    virtual void highlightInteractiveObjects(UIState* state);
    virtual void highlightNextInteractiveObjects(UIState* state);
    
    //checks whether the ability can be activated
    virtual bool isAbilityActivatable(UIState* state);
    
    //targets objects to use ability on
    virtual bool targetObjectWithHandCard(CCTouch* touch, UIState* state, CardSprite *card);
    
    virtual bool targetObjectWithTargetingState(CCTouch* touch, UIState* state, CardSprite *card);
    
    // checks whether the ability can be used
    virtual bool isAbilityReady();
    
    //changes the state
    virtual void changeState(UIState* state, CardSprite *card);
    
    //exectutes the intialStatuses
    virtual void useInitialAbility();
    
    //does what the ability should do
    virtual void useAbility();
    
};

#endif /* defined(__RogueDeck__PlayAreaToTargetMonstersTargets__) */
