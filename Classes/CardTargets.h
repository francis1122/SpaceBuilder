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


class UIState;
USING_NS_CC;


typedef enum TargetingType{
    None,
    RequireActions,
    DiscardArea,
    PlayArea,
    Monsters
} TargetingType;

class CardTargets : public CCObject
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static node()" method manually
    CREATE_FUNC(CardTargets);
    
    bool isTargetRequired;
    
    //type of targets to highlight
    TargetingType targetingType;
    
    CCArray *selectedTargets;
    
    //array of statuses
    CCArray *statuses;


//checks whether the ability can be activated
bool isAbilityActivatable(UIState* state);

//initial call when ability is used
void activateAbility(UIState* state);

//targets objects to use ability on
void targetObject(CCTouch* touch);

// checks whether the ability can be used
bool isAbilityReady();

//does what the ability should do
void useAbility();
    
};

#endif /* defined(__RogueDeck__CardTargets__) */
