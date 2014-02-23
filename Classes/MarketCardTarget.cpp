//
//  MarketCardTarget.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 2/18/14.
//
//

#include "MarketCardTarget.h"
#include "GameManager.h"
#include "CardSprite.h"
#include "MonsterSprite.h"
#include "UIState.h"
#include "Player.h"
#include "Constants.h"
#include "Statuses.h"



void MarketCardTarget::highlightInteractiveObjects(UIState* state){
    GM->gameLayer->enablePlayAreaInteractive();
    CCObject *object;
    CCARRAY_FOREACH(GM->marketCardArray, object){
        CardSprite *card = (CardSprite*)object;
            card->enableInteractive();
    }
    GM->gameLayer->changeIndicatorState("Play Area or Target Card");
    
}

void MarketCardTarget::highlightNextInteractiveObjects(UIState* state){
    //highlight only monsters
    CCObject *object;
    CCARRAY_FOREACH(GM->marketCardArray, object){
        CardSprite *card = (CardSprite*)object;
        card->enableInteractive();
    }
    GM->gameLayer->changeIndicatorState("Target Card");
    
}

//checks whether the ability can be activated
bool MarketCardTarget::isAbilityActivatable(UIState* state){
    int targetCount = 0;
    CCObject *object;
    CCARRAY_FOREACH(GM->marketCardArray, object){
        targetCount++;
    }

    if(targetCount >= targetAmount){
        return true;
    }else{
        return false;
    }
}

//targets objects to use ability on
bool MarketCardTarget::targetObjectWithHandCard(CCTouch* touch, UIState* state, CardSprite *card){
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    
    //monsters are an exceptable place
    CCObject *object;
    CCARRAY_FOREACH(GM->marketCardArray, object){
        CardSprite *card = (CardSprite*)object;
        CCRect collisionRect = CCRectMake(card->getPosition().x - card->getContentSize().width/2 * card->getScale(), card->getPosition().y - card->getContentSize().height/2 * card->getScale(), card->getContentSize().width * card->getScale(), card->getContentSize().height * card->getScale());
        if(collisionRect.containsPoint(touchPoint)){
            selectedTargets->addObject(card);
            return true;
        }
    }
    
    //play area is an exceptable place
    if(state->cardInPlayArea(card)){
        return true;
    }
    return false;
}

//targets objects to use ability on
bool MarketCardTarget::targetObjectWithTargetingState(CCTouch* touch, UIState* state, CardSprite *card){
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    
    //monsters are an exceptable place
    CCObject *object;
    CCARRAY_FOREACH(GM->marketCardArray, object){
        CardSprite *card = (CardSprite*)object;
        CCRect collisionRect = CCRectMake(card->getPosition().x - card->getContentSize().width/2 * card->getScale(), card->getPosition().y - card->getContentSize().height/2 * card->getScale(), card->getContentSize().width * card->getScale(), card->getContentSize().height * card->getScale());
        if(collisionRect.containsPoint(touchPoint)){
                selectedTargets->addObject(card);
                return true;
        }
    }
    return false;
}

// checks whether the ability can be used
bool MarketCardTarget::isAbilityReady(){
    if(selectedTargets->count() >= targetAmount){
        return true;
    }else{
        return false;
    }
}

//changes the state
void MarketCardTarget::changeState(UIState* state, CardSprite *card){
    state->transitionToCardTargetingState(card);
}

void MarketCardTarget::useInitialAbility(){
    
    CCObject *object;
    CCARRAY_FOREACH(initialStatuses, object){
        Status *status = (Status*)object;
        status->applyStatus();
    }
    GM->gameLayer->updateInterface();
}

//does what the ability should do
void MarketCardTarget::useAbility(){
    CardTargets::useAbility();
    CCObject *object;
    CCARRAY_FOREACH(selectedTargets, object){
        //TODO: can target more than just monsters
        CardSprite *card = (CardSprite*)object;
        CCObject *object2;
        CCARRAY_FOREACH(statuses, object2){
            Status *status = (Status*)object2;
            status->addStatusToCardSprite(card);
        }
    }
    GM->organizeMonsters();
    GM->organizeMarket();
    GM->gameLayer->updateInterface();
    GM->afterCardPlayedStateCheck();
    //clear targetArray
    selectedTargets->removeAllObjects();
}


