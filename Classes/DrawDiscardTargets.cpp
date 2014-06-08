//
//  DrawDiscardTargets.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/10/14.
//
//

#include "DrawDiscardTargets.h"
#include "GameManager.h"
#include "CardSprite.h"
#include "UIState.h"
#include "Player.h"
#include "Constants.h"
#include "Statuses.h"
#include "HandLayer.h"
#include "GameLayer.h"



void DrawDiscardTargets::highlightInteractiveObjects(UIState* state){
    GM->gameLayer->enablePlayAreaInteractive();
    GM->gameLayer->changeIndicatorState("Play Area");
}

void DrawDiscardTargets::highlightInteractiveObjectsWithDraggingState(UIState* state)
{
    GM->gameLayer->changeIndicatorState("Discard Card");
    CCObject *object;
    CCARRAY_FOREACH(GM->player->handCards, object){
        CardSprite *card = (CardSprite*)object;
        card->enableInteractive();
    }
}

void DrawDiscardTargets::highlightInteractiveObjectsWithDraggingCard(UIState* state)
{
    GM->gameLayer->handLayer->enableDiscardInteractive();
    
}

//checks whether the ability can be activated
bool DrawDiscardTargets::isAbilityActivatable(UIState* state){
    return true;
}

//targets objects to use ability on
bool DrawDiscardTargets::targetObjectWithHandCard(CCTouch* touch, UIState* state, CardSprite *card){
    return state->cardInPlayArea(card);
}

CardSprite* DrawDiscardTargets::targetObjectWithDraggingState(CCTouch* touch, UIState* state, CardSprite *card){
    CardSprite *chosenCard = state->handCardAtPoint(touch);
    return chosenCard;
}

bool DrawDiscardTargets::targetObjectWithDraggingCard(CCTouch* touch, UIState* state, CardSprite *card){
    if(state->cardInDiscardArea(card)){
        this->selectedTargets->addObject(card);
        GM->player->discardCard(card);
        return true;
    }
    return false;
}

// checks whether the ability can be used
bool DrawDiscardTargets::isAbilityReady(){
    if(selectedTargets->count() >= targetAmount){
        return true;
    }else{
        return false;
    }
}

//changes the state
void DrawDiscardTargets::changeState(UIState* state, CardSprite *card){
    state->transitionToCardDraggingState(card);
}

void DrawDiscardTargets::useInitialAbility(){
    CCObject *object;
    CCARRAY_FOREACH(initialStatuses, object){
        Status *status = (Status*)object;
        status->applyStatus();
    }
    GM->gameLayer->updateInterface();
}

//does what the ability should do
void DrawDiscardTargets::useAbility(){
    CardTargets::useAbility();
    CCObject *object;
    CCARRAY_FOREACH(statuses, object){
        Status *status = (Status*)object;
        status->applyStatus();
    }
    //apply status effects to monster
    //    monster->updateInterface();
    
    
    GM->gameLayer->updateInterface();
    GM->afterCardPlayedStateCheck();
    //clear targetArray
    selectedTargets->removeAllObjects();
}
