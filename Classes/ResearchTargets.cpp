//
//  ResearchTargets.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 7/14/14.
//
//

#include "ResearchTargets.h"

#include "GameManager.h"
#include "CardSprite.h"
#include "UIState.h"
#include "Player.h"
#include "Constants.h"
#include "Statuses.h"
#include "SolarSystemObject.h"
#include "ResourceCardSprite.h"
#include "ResearchTypeTargetLayer.h"

// on "init" you need to initialize your instance
bool ResearchTargets::initWithCardSprite(CardSprite *card)
{
    CardTargets::initWithCardSprite(card);
    militaryTech = true;
    industryTech = true;
    explorationTech = true;
    scienceTech = true;
    currentTarget = -1;
    return true;
}

void ResearchTargets::highlightInteractiveObjects(UIState* state){
    GM->gameLayer->researchTypeTargetLayer->setVisible(true);
}

void ResearchTargets::highlightNextInteractiveObjects(UIState* state){
    CCLog("shouldn't call this");
}

//checks whether the ability can be activated
bool ResearchTargets::isAbilityActivatable(UIState* state){
    return true;
}

//targets objects to use ability on
bool ResearchTargets::targetObjectWithHandCard(CCTouch* touch, UIState* state, CardSprite *card){
    
    //figure out what quadrant card is played in
    currentTarget = state->cardInTechQuadrant(card);
    return isAbilityReady();
    
}

// checks whether the ability can be used
bool ResearchTargets::isAbilityReady(){
    if(currentTarget != -1){
        return true;
    }else{
        return false;
    }
}

//state to change to while card is being dragged around
void ResearchTargets::initialChangeState(UIState *state, CardSprite *card)
{
    state->transitionToResearchSelectState(card);
}

//changes the state
void ResearchTargets::changeState(UIState* state, CardSprite *card){
    
}

void ResearchTargets::useInitialAbility(){
    CCObject *object;
    CCARRAY_FOREACH(initialStatuses, object){
        Status *status = (Status*)object;
        status->applyStatus();
    }
    
    //    GM->player->organizeHand();
    //    GM->player->organizePlayedCards();
    GM->gameLayer->updateInterface();
}

//does what the ability should do
void ResearchTargets::useAbility(){
    CardTargets::useAbility();
    
    //add resource effects
    ResourceCardSprite *card = (ResourceCardSprite*)cardSprite;
    if(currentTarget == 0){
        card->owner->militaryTech += card->owner->calculateTechGeneration();
    }else if(currentTarget == 1){
        card->owner->industryTech += card->owner->calculateTechGeneration();
    }else if(currentTarget == 2){
        card->owner->expansionTech += card->owner->calculateTechGeneration();
    }else if(currentTarget == 3){
        card->owner->scienceTech += card->owner->calculateTechGeneration();
    }

        //depending on what quadrant/s was chosen, add tech to it
        
//        card->generateResources();
        
    
    currentTarget = -1;
    
    //apply status effects to monster
    GM->gameLayer->updateInterface();
    GM->afterCardPlayedStateCheck();
    //clear targetArray
    selectedTargets->removeAllObjects();
    GM->gameLayer->researchTypeTargetLayer->setVisible(false);
}