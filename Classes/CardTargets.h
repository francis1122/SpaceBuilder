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

class CardSprite;
class UIState;
class BaseObject;
class MonsterSprite;
USING_NS_CC;


typedef enum TargetingType{
    None,
    RequireActions,
    DiscardArea, //might not have cards required to discard
    DrawCard_DiscardCard, //always have cards to discard, so it's not a problem
    PlayArea, //can always be played in the play area, no restrictions
    PlayArea_TargetMonsters, //must be played in the play area and must have monster targets
    Monsters, //must have monster targets
    DiscardCard, //draw card from the discard pile
    DrawCard, // not sure
    BuyCard, //buy a card
    MonsterDefend //can only target monsters that are on the attack line
    //    PlayToDiscard
} TargetingType;


class CardTargets : public CCObject
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool initWithCardSprite(CardSprite *card);
    
    //cardsprite
    CardSprite *cardSprite;
    
    //amount of targets that must be targetted, used for dragging as well
    int targetAmount;
    
    int minMonsterLife;
    int maxMonsterLife;
    
    bool isPreemptive;
    
    //type of targets to highlight
    TargetingType targetingType;
    
    //Dragging stuff
    CCArray *selectedTargets;
    
    //array of statuses
    //inital statuses cannot require targets, gets called before statuses get's called and before state change
    CCArray *initialStatuses;
    CCArray *statuses;
    
    
    virtual void highlightInteractiveObjects(UIState* state);
    
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
    
    //changes the state
    virtual void changeState(UIState* state, CardSprite *card);
    
    //exectutes the intialStatuses
    virtual void useInitialAbility();
    
    //does what the ability should do
    virtual void useAbility();

    //utility functions
    virtual bool validMonsterTargetCheck(MonsterSprite *monster);
    
};

#endif /* defined(__RogueDeck__CardTargets__) */
