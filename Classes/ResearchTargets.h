//
//  ResearchTargets.h
//  RogueDeck
//
//  Created by Hunter Francis on 7/14/14.
//
//

#ifndef __RogueDeck__ResearchTargets__
#define __RogueDeck__ResearchTargets__

#include "cocos2d.h"
#include "CardTargets.h"



class UIState;
class CardSprite;
USING_NS_CC;

class ResearchTargets : public CardTargets
{
public:
    
    //which research branches can be chosen
    bool militaryTech;
    bool industryTech;
    bool explorationTech;
    bool scienceTech;
    
    int currentTarget;
    
    virtual bool initWithCardSprite(CardSprite *card);
    
    virtual void highlightInteractiveObjects(UIState* state);
    virtual void highlightNextInteractiveObjects(UIState* state);
    
    //checks whether the ability can be activated
    virtual bool isAbilityActivatable(UIState* state);
    
    //targets objects to use ability on
    virtual bool targetObjectWithHandCard(CCTouch* touch, UIState* state, CardSprite *card);
    
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

#endif /* defined(__RogueDeck__ResearchTargets__) */
