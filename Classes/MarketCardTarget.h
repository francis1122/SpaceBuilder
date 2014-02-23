//
//  MarketCardTarget.h
//  RogueDeck
//
//  Created by Hunter Francis on 2/18/14.
//
//

#ifndef __RogueDeck__MarketCardTarget__
#define __RogueDeck__MarketCardTarget__

#include "cocos2d.h"
#include "CardTargets.h"

class UIState;
class CardSprite;
class MonsterSprite;
USING_NS_CC;

class MarketCardTarget : public CardTargets
{
public:
    
    virtual void highlightInteractiveObjects(UIState* state);
    virtual void highlightNextInteractiveObjects(UIState* state);
    
    //checks whether the ability can be activated
    virtual bool isAbilityActivatable(UIState* state);
    
    //targets objects to use ability on
    virtual bool targetObjectWithHandCard(CCTouch* touch, UIState* state, CardSprite *card);
    
    //targets objects to use ability on
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

#endif /* defined(__RogueDeck__MarketCardTarget__) */
