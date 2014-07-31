//
//  CardTargets.h
//  RogueDeck
//
//  Created by Hunter Francis on 11/21/13.
//
//

#ifndef __RogueDeck__CardTargets__
#define __RogueDeck__CardTargets__

#include "cocos2d.h"
#include "BaseTargets.h"

class CardSprite;
class UIState;
class BaseObject;
class SolarSystemObject;
USING_NS_CC;


class CardTargets : public BaseTargets
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool initWithCardSprite(CardSprite *card);
    
    //cardsprite
    CardSprite *cardSprite;
    
    
    int timesCardCanBePlayed;
    int timesCardHasBeenPlayed;
    
    
    
    virtual void highlightInteractiveObjects(UIState* state);
    
    virtual void highlightOnMove(UIState* state, CardSprite *card);
    
    virtual void highlightNextInteractiveObjects(UIState* state);
    
    virtual void highlightInteractiveObjectsWithDraggingState(UIState* state);
    
    virtual void highlightInteractiveObjectsWithDraggingCard(UIState* state);
    
    virtual void unableToActivateHighlight(UIState*);
    
    //checks whether the ability can be activated
    virtual bool isAbilityActivatable(UIState* state);
    
    //targets objects to use ability on
    virtual bool targetObjectWithHandCard(CCTouch* touch, UIState* state, CardSprite *card);
    
    //targets objects to use ability on
    virtual bool targetObjectWithTargetingState(CCTouch* touch, UIState* state, CardSprite *card);
    
    virtual CardSprite* targetObjectWithDraggingState(CCTouch* touch, UIState* state, CardSprite *card);
    
    virtual bool targetObjectWithDraggingCard(CCTouch* touch, UIState* state, CardSprite *card);
    
    // checks whether the ability can be used
    virtual bool isAbilityReady();
    
    //state to change to while card is being dragged around
    virtual void initialChangeState(UIState *state, CardSprite *card);
    
    //changes the state
    virtual void changeState(UIState* state, CardSprite *card);
    
    //exectutes the intialStatuses
    virtual void useInitialAbility();
    
    //does what the ability should do
    virtual void useAbility();


    
};

#endif /* defined(__RogueDeck__CardTargets__) */
