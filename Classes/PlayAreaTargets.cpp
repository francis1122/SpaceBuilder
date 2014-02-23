//
//  PlayAreaTargets.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/10/14.
//
//

#include "PlayAreaTargets.h"
#include "GameManager.h"
#include "CardSprite.h"
#include "MonsterSprite.h"
#include "UIState.h"
#include "Player.h"
#include "Constants.h"
#include "Statuses.h"



void PlayAreaTargets::highlightInteractiveObjects(UIState* state){
    GM->gameLayer->enablePlayAreaInteractive();
    GM->gameLayer->changeIndicatorState("Play Area");
}

void PlayAreaTargets::highlightNextInteractiveObjects(UIState* state){
    CCLog("shouldn't call this");
    
}

//checks whether the ability can be activated
bool PlayAreaTargets::isAbilityActivatable(UIState* state){
    return true;
}

//targets objects to use ability on
bool PlayAreaTargets::targetObjectWithHandCard(CCTouch* touch, UIState* state, CardSprite *card){

    return state->cardInPlayArea(card);
}

// checks whether the ability can be used
bool PlayAreaTargets::isAbilityReady(){
    return true;
}

//changes the state
void PlayAreaTargets::changeState(UIState* state, CardSprite *card){
    
}

void PlayAreaTargets::useInitialAbility(){
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
void PlayAreaTargets::useAbility(){
    CardTargets::useAbility();
    //do status
    CCObject *object;
    CCARRAY_FOREACH(statuses, object){
        Status *status = (Status*)object;
        status->applyStatus();
    }
    //apply status effects to monster
    GM->organizeMonsters();
    GM->organizeMarket();
    GM->gameLayer->updateInterface();
    GM->afterCardPlayedStateCheck();
    //clear targetArray
    selectedTargets->removeAllObjects();
}

