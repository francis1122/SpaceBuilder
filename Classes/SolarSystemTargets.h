//
//  SolarSystemTargets.h
//  RogueDeck
//
//  Created by Hunter Francis on 6/8/14.
//
//

#ifndef __RogueDeck__SolarSystemTargets__
#define __RogueDeck__SolarSystemTargets__

#include "cocos2d.h"
#include "CardTargets.h"

class UIState;
class CardSprite;
class SolarSystemObject;
USING_NS_CC;

class SolarSystemTargets : public CardTargets
{
public:
    virtual void highlightInteractiveObjects(UIState* state);
    virtual void highlightNextInteractiveObjects(UIState* state);
    
    bool targetNeutralSystems;
    bool targetFriendlySystems;
    
    //checks whether the ability can be activated
    virtual bool isAbilityActivatable(UIState* state);
    
    //targets objects to use ability on
    virtual bool targetObjectWithHandCard(CCTouch* touch, UIState* state, CardSprite *card);
    
    // checks whether the ability can be used
    virtual bool isAbilityReady();
    
    //changes the state
    virtual void changeState(UIState* state, CardSprite *card);
    
    //exectutes the intialStatuses
    virtual void useInitialAbility();
    
    //does what the ability should do
    virtual void useAbility();
    
    bool isValidSolarSystem(SolarSystemObject *solarSystemObject);
    
};

#endif /* defined(__RogueDeck__SolarSystemTargets__) */
