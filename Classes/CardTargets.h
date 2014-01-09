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
    DiscardArea, //might not have cards required to discard
    DrawCard_DiscardCard, //always have cards to discard, so it's not a problem
    PlayArea, //can always be played in the play area
    PlayArea_TargetMonsters, //must be played in the play area and must have monster targets
    Monsters, //must have monster targets
    DiscardCard, //draw card from the discard pile
    DrawCard, // not sure
    BuyCard //buy a card
//    PlayToDiscard
} TargetingType;


class CardTargets : public CCObject
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static node()" method manually
    CREATE_FUNC(CardTargets);
    
    
    //only 1 or none of these can be true
//    bool isTargetRequired;
//    bool isDraggingRequired;
    
    //amount of targets that must be targetted, used for dragging as well
    int targetAmount;
    
    //type of targets to highlight
    TargetingType targetingType;
    
    //Dragging stuff
     

    CCArray *selectedTargets;
    
    //array of statuses
    //inital statuses cannot require targets
    CCArray *initialStatuses;
    CCArray *statuses;


//checks whether the ability can be activated
bool isAbilityActivatable(UIState* state);

//initial call when ability is used
void activateAbility(UIState* state);

//targets objects to use ability on
bool targetObject(CCTouch* touch);

// checks whether the ability can be used
bool isAbilityReady();

//exectutes the intialStatuses
void useInitialAbility();
    
//does what the ability should do
void useAbility();
    
};

#endif /* defined(__RogueDeck__CardTargets__) */
