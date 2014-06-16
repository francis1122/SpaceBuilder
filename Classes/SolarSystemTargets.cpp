//
//  SolarSystemTargets.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 6/8/14.
//
//

#include "SolarSystemTargets.h"
#include "GameManager.h"
#include "CardSprite.h"
#include "MonsterLayer.h"
#include "SolarSystemDetailsLayer.h"
#include "UIState.h"
#include "Player.h"
#include "Constants.h"
#include "Statuses.h"
#include "SolarSystemObject.h"


void SolarSystemTargets::highlightInteractiveObjects(UIState* state){
    GM->gameLayer->enablePlayAreaInteractive();
    CCObject *object;
    CCARRAY_FOREACH(GM->solarSystemArray, object){
        SolarSystemObject *solarSystem = (SolarSystemObject*)object;
        if(this->isValidSolarSystem(solarSystem)){
            solarSystem->setHighlighted(true);
        }
    }
    
    GM->gameLayer->changeIndicatorState("Target System");
    
}

void SolarSystemTargets::highlightNextInteractiveObjects(UIState* state){
    //highlight only monsters
    /*
    CCARRAY_FOREACH(GM->monsterArray, object){
        MonsterSprite *monster = (MonsterSprite*)object;
        if(this->validMonsterTargetCheck(monster)){
            monster->enableInteractive();
        }
    }
     */
    GM->gameLayer->enablePlayAreaInteractive();
    CCObject *object;
    CCARRAY_FOREACH(GM->solarSystemArray, object){
        SolarSystemObject *solarSystem = (SolarSystemObject*)object;
        if(this->isValidSolarSystem(solarSystem)){
            solarSystem->setHighlighted(true);
        }
    }
    GM->gameLayer->changeIndicatorState("Target Monster");
    
}

//checks whether the ability can be activated
bool SolarSystemTargets::isAbilityActivatable(UIState* state){
    int targetCount = 0;
    CCObject *object;
    CCARRAY_FOREACH(GM->solarSystemArray, object){
        SolarSystemObject *solarSystem = (SolarSystemObject*)object;
        if(this->isValidSolarSystem(solarSystem)){
            targetCount++;
        }
    }
   /* CCARRAY_FOREACH(GM->monsterArray, object){
        MonsterSprite *monster = (MonsterSprite*)object;
        if(this->validMonsterTargetCheck(monster)){
            targetCount++;
        }
    }
    */
    
    if(targetCount >= targetAmount){
        return true;
    }else{
        return false;
    }
}

//targets objects to use ability on
bool SolarSystemTargets::targetObjectWithHandCard(CCTouch* touch, UIState* state, CardSprite *card){
    CCPoint touchPoint = GM->gameLayer->monsterLayer->convertTouchToNodeSpace(touch);
    /*
    GM->gameLayer->enablePlayAreaInteractive();
    CCObject *object;
    CCARRAY_FOREACH(GM->solarSystemArray, object){
        SolarSystemObject *solarSystem = (SolarSystemObject*)object;
        //        if(this->validMonsterTargetCheck(SolarSystemObject)){
        solarSystem->setHighlighted(true);
        //      }
    }*/
    
    //monsters are an exceptable place
    CCObject *object;
    CCARRAY_FOREACH(GM->solarSystemArray, object){
        SolarSystemObject *solarSystem = (SolarSystemObject*)object;
        CCRect collisionRect = CCRectMake(solarSystem->getPosition().x - solarSystem->getContentSize().width/2 * solarSystem->getScale(), solarSystem->getPosition().y - solarSystem->getContentSize().height/2 * solarSystem->getScale(), solarSystem->getContentSize().width * solarSystem->getScale(), solarSystem->getContentSize().height * solarSystem->getScale());
        if(collisionRect.containsPoint(touchPoint)){
            if(this->isValidSolarSystem(solarSystem)){
                selectedTargets->addObject(solarSystem);
                return true;
            }
        }
    }
    
    //play area is an exceptable place
/*    if(state->cardInPlayArea(card)){
        return true;
    }
    */
    return false;
}
/*
//targets objects to use ability on
bool SolarSystemTargets::targetObjectWithTargetingState(CCTouch* touch, UIState* state, CardSprite *card){
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    
    //monsters are an exceptable place
    CCObject *object;
    CCARRAY_FOREACH(GM->monsterArray, object){
        MonsterSprite *monster = (MonsterSprite*)object;
        CCRect collisionRect = CCRectMake(monster->getPosition().x - monster->getContentSize().width/2 * monster->getScale(), monster->getPosition().y - monster->getContentSize().height/2 * monster->getScale(), monster->getContentSize().width * monster->getScale(), monster->getContentSize().height * monster->getScale());
        if(collisionRect.containsPoint(touchPoint)){
            if(this->validMonsterTargetCheck(monster)){
                selectedTargets->addObject(monster);
                return true;
            }
        }
    }
    return false;
}
*/
// checks whether the ability can be used
bool SolarSystemTargets::isAbilityReady(){
    if(selectedTargets->count() >= targetAmount){
        return true;
    }else{
        return false;
    }
}

//changes the state
void SolarSystemTargets::changeState(UIState* state, CardSprite *card){
 //   state->transitionToCardTargetingState(card);
}

void SolarSystemTargets::useInitialAbility(){
    
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
void SolarSystemTargets::useAbility(){
    CardTargets::useAbility();
    
    
    
    CCObject *object;
    CCARRAY_FOREACH(selectedTargets, object){
        //TODO: can target more than just monsters
        SolarSystemObject *solarSystem = (SolarSystemObject*)object;
        CCObject *object2;
        CCARRAY_FOREACH(statuses, object2){
            Status *status = (Status*)object2;
            status->addStatusToSolarSystem(solarSystem);
        }
    }
    
    //apply status effects to monster
    //    monster->updateInterface();
    
    GM->gameLayer->updateInterface();
    GM->afterCardPlayedStateCheck();
    //clear targetArray
    selectedTargets->removeAllObjects();
}

bool SolarSystemTargets::isValidSolarSystem(SolarSystemObject *solarSystemObject)
{
    bool isValid = false;
    if(targetFriendlySystems){
        if(solarSystemObject->owner){
            if(solarSystemObject->owner == GM->player){
                isValid = true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
    
    if(targetNeutralSystems){
        if(solarSystemObject->owner){
            return false;
        }else{
            isValid = true;
        }
    }
    return isValid;
}
