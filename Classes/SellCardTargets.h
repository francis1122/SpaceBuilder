//
//  SellCardTargets.h
//  RogueDeck
//
//  Created by Hunter Francis on 1/17/14.
//
//

#ifndef __RogueDeck__SellCardTargets__
#define __RogueDeck__SellCardTargets__

#include "CardTargets.h"

class CardSprite;
class UIState;
class BaseObject;
USING_NS_CC;

class SellCardTargets : public CardTargets
{
public:

    virtual void highlightInteractiveObjects(UIState* state);
    
    virtual void highlightInteractiveObjectsWithDraggingState(UIState* state);
    
    virtual void highlightInteractiveObjectsWithDraggingCard(UIState* state);
    
    //checks whether the ability can be activated
    virtual bool isAbilityActivatable(UIState* state);
    
    //targets objects to use ability on
    virtual bool targetObjectWithHandCard(CCTouch* touch, UIState* state, CardSprite *card);
    
    virtual CardSprite* targetObjectWithDraggingState(CCTouch* touch, UIState* state, CardSprite *card);
    
    virtual bool targetObjectWithDraggingCard(CCTouch* touch, UIState* state, CardSprite *card);
    
    
    // checks whether the ability can be used
    virtual bool isAbilityReady();
    
    //changes the state
    virtual void changeState(UIState* state, CardSprite *card);
    
    //exectutes the intialStatuses
    virtual void useInitialAbility();
    
    //does what the ability should do
    virtual void useAbility();
    
};

#endif /* defined(__RogueDeck__SellCardTargets__) */
