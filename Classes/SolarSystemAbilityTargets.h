//
//  SolarSystemAbilityTargets.h
//  RogueDeck
//
//  Created by Hunter Francis on 7/29/14.
//
//

#ifndef __RogueDeck__SolarSystemAbilityTargets__
#define __RogueDeck__SolarSystemAbilityTargets__

#include "cocos2d.h"
#include "AbilityTargets.h"

class UIState;
class CardSprite;
class SolarSystemObject;

USING_NS_CC;

class SolarSystemAbilityTargets : public AbilityTargets
{
public:
    
    virtual bool init();
    
    virtual void highlightInteractiveObjects(UIState* state, Ability *ability);
    
    bool targetNeutralSystems;
    bool targetFriendlySystems;
    bool adjacentOnly;
    bool needsFuel;
    
    //state to change to while card is being dragged around
    virtual void initialChangeState(UIState *state, Ability *ability);
    
    //targets objects to use ability on
    virtual bool targetObjectWithTargetingState(CCTouch* touch, UIState* state, Ability *ability);
    
    
    //checks whether the ability can be activated
    virtual bool isAbilityActivatable(UIState* state, Ability *ability);
    
    
    // checks whether the ability can be used
    virtual bool isAbilityReady( Ability *ability);
    
    //does what the ability should do
    virtual void useAbility(Ability *ability);
    
    bool isValidSolarSystem(SolarSystemObject *solarSystemObject, Ability *ability);
    
};

#endif /* defined(__RogueDeck__SolarSystemAbilityTargets__) */
