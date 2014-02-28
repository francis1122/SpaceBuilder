//
//  MonsterAdjacentTargets.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 2/23/14.
//
//

#include "MonsterAdjacentTargets.h"
#include "GameManager.h"
#include "CardSprite.h"
#include "MonsterSprite.h"
#include "UIState.h"
#include "Player.h"
#include "Constants.h"
#include "Statuses.h"



void MonsterAdjacentTargets::highlightInteractiveObjects(UIState* state){
    GM->gameLayer->enablePlayAreaInteractive();
    CCObject *object;
    CCARRAY_FOREACH(GM->monsterArray, object){
        MonsterSprite *monster = (MonsterSprite*)object;
        if(this->validMonsterTargetCheck(monster)){
            monster->enableInteractive();
        }
    }
    GM->gameLayer->changeIndicatorState("Play Area or Target Monster");
    
}

void MonsterAdjacentTargets::highlightNextInteractiveObjects(UIState* state){
    //highlight only monsters
    CCObject *object;
    
    CCARRAY_FOREACH(GM->monsterArray, object){
        MonsterSprite *monster = (MonsterSprite*)object;
        if(this->validMonsterTargetCheck(monster)){
            monster->enableInteractive();
        }
    }
    GM->gameLayer->changeIndicatorState("Target Monster");
    
}

//checks whether the ability can be activated
bool MonsterAdjacentTargets::isAbilityActivatable(UIState* state){
    int targetCount = 0;
    CCObject *object;
    CCARRAY_FOREACH(GM->monsterArray, object){
        MonsterSprite *monster = (MonsterSprite*)object;
        if(this->validMonsterTargetCheck(monster)){
            targetCount++;
        }
    }
    
    
    if(targetCount >= targetAmount){
        return true;
    }else{
        return false;
    }
}

//targets objects to use ability on
bool MonsterAdjacentTargets::targetObjectWithHandCard(CCTouch* touch, UIState* state, CardSprite *card){
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    
    //monsters are an exceptable place
    CCObject *object;
    CCARRAY_FOREACH(GM->monsterArray, object){
        MonsterSprite *monster = (MonsterSprite*)object;
        CCRect collisionRect = CCRectMake(monster->getPosition().x - monster->getContentSize().width/2 * monster->getScale(), monster->getPosition().y - monster->getContentSize().height/2 * monster->getScale(), monster->getContentSize().width * monster->getScale(), monster->getContentSize().height * monster->getScale());
        if(collisionRect.containsPoint(touchPoint)){
            if(this->validMonsterTargetCheck(monster)){
                selectedTargets->addObject(monster);
                //also add any monsters adjacent to this one
                int selectedLane = monster->lane;
                CCObject *objectTwo;
                CCARRAY_FOREACH(GM->monsterArray, objectTwo){
                    MonsterSprite *adjacentMonster = (MonsterSprite*)objectTwo;
                    if(adjacentMonster->lane == selectedLane - 1 ||adjacentMonster->lane == selectedLane + 1){
                        selectedTargets->addObject(adjacentMonster);
                    }
                }
                return true;
            }
        }
    }
    
    //play area is an exceptable place
    if(state->cardInPlayArea(card)){
        return true;
    }
    return false;
}

//targets objects to use ability on
bool MonsterAdjacentTargets::targetObjectWithTargetingState(CCTouch* touch, UIState* state, CardSprite *card){
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    
    //monsters are an exceptable place
    CCObject *object;
    CCARRAY_FOREACH(GM->monsterArray, object){
        MonsterSprite *monster = (MonsterSprite*)object;
        CCRect collisionRect = CCRectMake(monster->getPosition().x - monster->getContentSize().width/2 * monster->getScale(), monster->getPosition().y - monster->getContentSize().height/2 * monster->getScale(), monster->getContentSize().width * monster->getScale(), monster->getContentSize().height * monster->getScale());
        if(collisionRect.containsPoint(touchPoint)){
            if(this->validMonsterTargetCheck(monster)){
                selectedTargets->addObject(monster);
                //also add any monsters adjacent to this one
                int selectedLane = monster->lane;
                CCObject *objectTwo;
                CCARRAY_FOREACH(GM->monsterArray, objectTwo){
                    MonsterSprite *adjacentMonster = (MonsterSprite*)objectTwo;
                    if(adjacentMonster->lane == selectedLane - 1 ||adjacentMonster->lane == selectedLane + 1){
                        selectedTargets->addObject(adjacentMonster);
                    }
                }
                return true;
            }
        }
    }
    return false;
}

// checks whether the ability can be used
bool MonsterAdjacentTargets::isAbilityReady(){
    if(selectedTargets->count() >= targetAmount){
        return true;
    }else{
        return false;
    }
}

//changes the state
void MonsterAdjacentTargets::changeState(UIState* state, CardSprite *card){
    state->transitionToCardTargetingState(card);
}

void MonsterAdjacentTargets::useInitialAbility(){
    
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
void MonsterAdjacentTargets::useAbility(){
    CardTargets::useAbility();
    CCObject *object;
    CCARRAY_FOREACH(selectedTargets, object){
        //TODO: can target more than just monsters
        MonsterSprite *monster = (MonsterSprite*)object;
        CCObject *object2;
        CCARRAY_FOREACH(statuses, object2){
            Status *status = (Status*)object2;
            status->addStatusToGameObject(monster);
        }
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
