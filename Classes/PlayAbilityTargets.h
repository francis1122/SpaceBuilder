//
//  PlayAbilityTargets.h
//  RogueDeck
//
//  Created by Hunter Francis on 7/29/14.
//
//

#ifndef __RogueDeck__PlayAbilityTargets__
#define __RogueDeck__PlayAbilityTargets__

#include "cocos2d.h"
#include "AbilityTargets.h"

class UIState;
class CardSprite;
class SolarSystemObject;

USING_NS_CC;

class PlayAbilityTargets : public AbilityTargets
{
public:
    
    virtual bool init();
    
    
    bool targetNeutralSystems;
    bool targetFriendlySystems;
    
    virtual void highlightInteractiveObjects(UIState* state, Ability *ability);
    
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

#endif /* defined(__RogueDeck__PlayAbilityTargets__) */
