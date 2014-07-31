//
//  AbilityTargets.h
//  RogueDeck
//
//  Created by Hunter Francis on 7/29/14.
//
//

#ifndef __RogueDeck__AbilityTargets__
#define __RogueDeck__AbilityTargets__

#include "cocos2d.h"
#include "CardTargets.h"

class CardSprite;
class UIState;
class BaseObject;
class SolarSystemObject;
class ShipModel;
class Ability;
USING_NS_CC;


class AbilityTargets : public BaseTargets
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    CCString *normalCommandImage, *selectedCommandImage, *disabledCommandImage;
    
    virtual void highlightInteractiveObjects(UIState* state, Ability *ability);
    
    //checks whether the ability can be activated
//    virtual bool isAbilityActivatable(UIState* state);
    
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
    
    
};

#endif /* defined(__RogueDeck__AbilityTargets__) */
