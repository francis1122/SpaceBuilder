//
//  DefendMonsterTargets.h
//  RogueDeck
//
//  Created by Hunter Francis on 1/14/14.
//
//

#ifndef __RogueDeck__DefendMonsterTargets__
#define __RogueDeck__DefendMonsterTargets__

#include "CardTargets.h"

class UIState;
class CardSprite;
USING_NS_CC;

class DefendMonsterTargets : public CardTargets
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


#endif /* defined(__RogueDeck__DefendMonsterTargets__) */
