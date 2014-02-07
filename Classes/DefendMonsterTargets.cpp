//
//  DefendMonsterTargets.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/14/14.
//
//

#include "DefendMonsterTargets.h"
#include "GameManager.h"
#include "CardSprite.h"
#include "MonsterSprite.h"
#include "UIState.h"
#include "Player.h"
#include "Constants.h"
#include "Statuses.h"


void DefendMonsterTargets::highlightInteractiveObjects(UIState* state){
    GM->gameLayer->enablePlayAreaInteractive();
    CCObject *object;
    CCARRAY_FOREACH(GM->monsterArray, object){
        MonsterSprite *monster = (MonsterSprite*)object;
        if(this->validMonsterTargetCheck(monster)){
            if(monster->location <= 0){
                monster->enableInteractive();
            }
        }
    }
    GM->gameLayer->changeIndicatorState("Play Area or Target Monster");
    
}

void DefendMonsterTargets::highlightNextInteractiveObjects(UIState* state){
    //highlight only monsters
    CCObject *object;
    CCARRAY_FOREACH(GM->monsterArray, object){
        MonsterSprite *monster = (MonsterSprite*)object;
        if(this->validMonsterTargetCheck(monster)){
            if(monster->location <= 0){
                monster->enableInteractive();
            }
        }
    }
    GM->gameLayer->changeIndicatorState("Target Monster");
}

//checks whether the ability can be activated
bool DefendMonsterTargets::isAbilityActivatable(UIState* state){
    int targetCount = 0;
    CCObject *object;
    CCARRAY_FOREACH(GM->monsterArray, object){
        MonsterSprite *monster = (MonsterSprite*)object;
        if(this->validMonsterTargetCheck(monster)){
            if(monster->location <= 0){
                targetCount++;
            }
        }
    }
    
    
    if(targetCount >= 1){
        return true;
    }else{
        return false;
    }
}

//targets objects to use ability on
bool DefendMonsterTargets::targetObjectWithHandCard(CCTouch* touch, UIState* state, CardSprite *card){
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    //monsters are an exceptable place
    CCObject *object;
    CCARRAY_FOREACH(GM->monsterArray, object){
        MonsterSprite *monster = (MonsterSprite*)object;
        if(monster->location <= 0){
            CCRect collisionRect = CCRectMake(monster->getPosition().x - monster->getContentSize().width/2 * monster->getScale(), monster->getPosition().y - monster->getContentSize().height/2 * monster->getScale(), monster->getContentSize().width * monster->getScale(), monster->getContentSize().height * monster->getScale());
            if(collisionRect.containsPoint(touchPoint)){
                if(this->validMonsterTargetCheck(monster)){
                    selectedTargets->addObject(monster);
                    return true;
                }
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
bool DefendMonsterTargets::targetObjectWithTargetingState(CCTouch* touch, UIState* state, CardSprite *card){
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    //monsters are an exceptable place
    CCObject *object;
    CCARRAY_FOREACH(GM->monsterArray, object){
        MonsterSprite *monster = (MonsterSprite*)object;
        if(monster->location <= 0){
            CCRect collisionRect = CCRectMake(monster->getPosition().x - monster->getContentSize().width/2 * monster->getScale(), monster->getPosition().y - monster->getContentSize().height/2 * monster->getScale(), monster->getContentSize().width * monster->getScale(), monster->getContentSize().height * monster->getScale());
            if(collisionRect.containsPoint(touchPoint)){
                if(this->validMonsterTargetCheck(monster)){
                    selectedTargets->addObject(monster);
                    return true;
                }
            }
        }
    }
    return false;
}

// checks whether the ability can be used
bool DefendMonsterTargets::isAbilityReady(){
    if(selectedTargets->count() >= targetAmount){
        return true;
    }else{
        return false;
    }
}

//changes the state
void DefendMonsterTargets::changeState(UIState* state, CardSprite *card){
    state->transitionToCardTargetingState(card);
}

void DefendMonsterTargets::useInitialAbility(){
    
    CCObject *object;
    CCARRAY_FOREACH(initialStatuses, object){
        Status *status = (Status*)object;
        status->applyStatus();
    }
    
    GM->gameLayer->updateInterface();
}

//does what the ability should do
void DefendMonsterTargets::useAbility(){
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
