//
//  SellCardTargets.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/17/14.
//
//

#include "SellCardTargets.h"
#include "GameManager.h"
#include "CardSprite.h"
#include "MonsterSprite.h"
#include "UIState.h"
#include "Player.h"
#include "Constants.h"
#include "Statuses.h"
#include "HandLayer.h"
#include "GameLayer.h"
#include "MarketLayer.h"



void SellCardTargets::highlightInteractiveObjects(UIState* state){
    GM->gameLayer->enablePlayAreaInteractive();
    GM->gameLayer->changeIndicatorState("Play Area");
}

void SellCardTargets::highlightInteractiveObjectsWithDraggingState(UIState* state)
{
    GM->gameLayer->changeIndicatorState("Drag Card to Pit");
    
    CCObject *object;
    CCARRAY_FOREACH(GM->player->handCards, object){
        CardSprite *card = (CardSprite*)object;
        card->enableInteractive();
    }
}

void SellCardTargets::highlightInteractiveObjectsWithDraggingCard(UIState* state)
{
    GM->gameLayer->handLayer->enableVoidAreaInteractive();
}

//checks whether the ability can be activated
bool SellCardTargets::isAbilityActivatable(UIState* state){
    // -1 accounts for the card that is getting played
    if((GM->player->handCards->count() - 1) > targetAmount){
        return true;
    }
    return false;
}

//targets objects to use ability on
bool SellCardTargets::targetObjectWithHandCard(CCTouch* touch, UIState* state, CardSprite *card){
    return state->cardInPlayArea(card);
}

CardSprite* SellCardTargets::targetObjectWithDraggingState(CCTouch* touch, UIState* state, CardSprite *card){
    CardSprite *chosenCard = state->handCardAtPoint(touch);
    return chosenCard;
}

bool SellCardTargets::targetObjectWithDraggingCard(CCTouch* touch, UIState* state, CardSprite *card){
    if(state->cardInSellArea(card)){
        this->selectedTargets->addObject(card);
        GM->player->removeCard(card);
        return true;
    }
    return false;
}

// checks whether the ability can be used
bool SellCardTargets::isAbilityReady(){
    if(selectedTargets->count() >= targetAmount){
        return true;
    }else{
        return false;
    }
}

//changes the state
void SellCardTargets::changeState(UIState* state, CardSprite *card){
    state->transitionToCardDraggingState(card);
}

void SellCardTargets::useInitialAbility(){
    CCObject *object;
    CCARRAY_FOREACH(initialStatuses, object){
        Status *status = (Status*)object;
        status->applyStatus();
    }
    GM->gameLayer->updateInterface();
}

//does what the ability should do
void SellCardTargets::useAbility(){
    CCObject *object;
    CCARRAY_FOREACH(statuses, object){
        Status *status = (Status*)object;
        status->applyStatus();
    }
    //apply status effects to monster
    //    monster->updateInterface();
    
    
    GM->organizeMonsters();
    GM->organizeMarket();
    GM->gameLayer->updateInterface();
    GM->afterCardPlayedStateCheck();
    //clear targetArray
    selectedTargets->removeAllObjects();
}
