//
//  CardTargets.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/21/13.
//
//

#include "CardTargets.h"
#include "GameManager.h"
#include "CardSprite.h"
#include "MonsterSprite.h"
#include "UIState.h"
#include "Player.h"
#include "Statuses.h"
#include "GameLayer.h"
#include "Constants.h"


USING_NS_CC;


// on "init" you need to initialize your instance
bool CardTargets::initWithCardSprite(CardSprite *card)
{
    
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    selectedTargets = new CCArray();
    statuses = new CCArray();
    initialStatuses = new CCArray();
    
    targetingType = PlayArea;
    
    selectedTargets->init();
    statuses->init();
    initialStatuses->init();
    targetAmount = 1;
    
    minMonsterLife = -1;
    maxMonsterLife = -1;
    timesCardCanBePlayed = -1;
    timesCardHasBeenPlayed = 0;
    
    isPreemptive = false;
    
    cardSprite = card;
    
    return true;
}


void CardTargets::highlightInteractiveObjects(UIState* state)
{
    
}

void CardTargets::highlightNextInteractiveObjects(UIState* state)
{
    
}

void CardTargets::highlightInteractiveObjectsWithDraggingState(UIState* state)
{
    
}

void CardTargets::highlightInteractiveObjectsWithDraggingCard(UIState* state)
{
    
}

void CardTargets::unableToActivateHighlight(UIState*)
{
    GM->gameLayer->changeIndicatorState("Cannot Play Card");
}

//checks whether the ability can be activated
bool CardTargets::isAbilityActivatable(UIState* state){
    //check if proper amount is possible
    if(targetingType == PlayArea_TargetMonsters){
        if(GM->monsterArray->count() >= targetAmount){
            return true;
        }else{
            return false;
        }
    }else if(targetingType == PlayArea){
        return true;
    }else if(targetingType == Monsters){
        if(GM->monsterArray->count() >= targetAmount){
            return true;
        }else{
            return false;
        }
    }else if(targetingType == DiscardArea){
        if(GM->player->handCards->count() >= targetAmount){
            return true;
        }else{
            return false;
        }
    }else if(targetingType == DrawCard_DiscardCard){
        return true;
    }else if(targetingType == MonsterDefend){
        int validTargetCount = 0;
        for(int i = 0; i < GM->monsterArray->count(); i++){
            MonsterSprite *monsterSprite = (MonsterSprite*)GM->monsterArray->objectAtIndex(i);
            if(monsterSprite->location <= 0){
                validTargetCount++;
            }
        }
        if(validTargetCount > targetAmount){
            return true;
        }else{
            return false;
        }
    }
    CCLog("CardTargets::isAbilityActivatable error");
    return false;
}


//targets objects to use ability on
bool CardTargets::targetObjectWithHandCard(CCTouch* touch, UIState* state, CardSprite *card){
    //get touch location
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    CCObject *object;
    
    //TODO: make this target specific objects such as cards in hand or market cards
    
    
    if(targetingType == MonsterDefend){
        for(int i = 0; i < GM->monsterArray->count(); i++){
            MonsterSprite *monster = (MonsterSprite*)GM->monsterArray->objectAtIndex(i);
            CCRect collisionRect = CCRectMake(monster->getPosition().x - monster->getContentSize().width/2 * monster->getScale(), monster->getPosition().y - monster->getContentSize().height/2 * monster->getScale(), monster->getContentSize().width * monster->getScale(), monster->getContentSize().height * monster->getScale());
            if(monster->location <= 0){
                if(collisionRect.containsPoint(touchPoint)){
                    selectedTargets->addObject(monster);
                    return true;
                }
            }
        }
        return false;

    }
    
    //monster selection
    CCARRAY_FOREACH(GM->monsterArray, object){
        //TODO: can target more than just monsters
        MonsterSprite *monster = (MonsterSprite*)object;
        CCRect collisionRect = CCRectMake(monster->getPosition().x - monster->getContentSize().width/2 * monster->getScale(), monster->getPosition().y - monster->getContentSize().height/2 * monster->getScale(), monster->getContentSize().width * monster->getScale(), monster->getContentSize().height * monster->getScale());
        if(collisionRect.containsPoint(touchPoint)){
            CCLog("monster has been hit");
            selectedTargets->addObject(monster);
            return true;
        }
    }
    return false;
}

//targets objects to use ability on
bool CardTargets::targetObjectWithTargetingState(CCTouch* touch, UIState* state, CardSprite *card){
    return false;
}

CardSprite* CardTargets::targetObjectWithDraggingState(CCTouch* touch, UIState* state, CardSprite *card){
    return NULL;
}

bool CardTargets::targetObjectWithDraggingCard(CCTouch* touch, UIState* state, CardSprite *card){
    return false;
}

// checks whether the ability can be used
bool CardTargets::isAbilityReady(){
    if(targetingType == PlayArea_TargetMonsters ||
       targetingType == Monsters ||
       targetingType == MonsterDefend){
        //targets
        if(selectedTargets->count() >= targetAmount){
            return true;
        }else{
            return false;
        }
    }else if(targetingType == DiscardCard){
        //dragging
        if(selectedTargets->count() >= targetAmount){
            return true;
        }else{
            return false;
        }
    }else if(targetingType == PlayArea ||
             targetingType == DrawCard ||
             targetingType == BuyCard ||
             targetingType == DrawCard_DiscardCard){
        return true;
    }
    CCLog("CardTargets::isAbilityReady error");
    return false;
}


//changes the state
void CardTargets::changeState(UIState* state, CardSprite *card){

}

void CardTargets::useInitialAbility(){

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
void CardTargets::useAbility()
{
    timesCardHasBeenPlayed++;
}


bool CardTargets::shouldCardBeDestroyed()
{
    if(timesCardCanBePlayed != -1){
        if(timesCardHasBeenPlayed >= timesCardCanBePlayed ){
            return true;
        }
    }
    return false;
}

//utility functions
#pragma mark - utility functions

bool  CardTargets::validMonsterTargetCheck(MonsterSprite *monster)
{
    if(monster->life < minMonsterLife && minMonsterLife != -1){
        return false;
    }
    if(monster->life > maxMonsterLife && maxMonsterLife != -1){
        return false;
    }
    if(GM->tauntPresent()){
        if(!monster->hasTaunt){
            return false;
        }
    }
    
    if(this->isPreemptive)
    {
        if(GM->player->playedCards->count() > 0){
            return false;
        }
    }

    return true;
}