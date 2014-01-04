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


USING_NS_CC;


// on "init" you need to initialize your instance
bool CardTargets::init()
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
    
    return true;
}


//checks whether the ability can be activated
bool CardTargets::isAbilityActivatable(UIState* state){
    //check if proper amount is possible
    
    return true;
}

//initial call when ability is used
void CardTargets::activateAbility(UIState* state){
    //change state?
}

//targets objects to use ability on
bool CardTargets::targetObject(CCTouch* touch){
    GameManager *GM = GameManager::sharedGameManager();
    //get touch location
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    CCObject *object;
    
    //TODO: make this target specific objects such as cards in hand or market cards
    
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

// checks whether the ability can be used
bool CardTargets::isAbilityReady(){
    if(isTargetRequired){
        if(selectedTargets->count() >= targetAmount){
            return true;
        }else{
            return false;
        }
    }else if(isDraggingRequired){
        if(selectedTargets->count() >= targetAmount){
            return true;
        }else{
            return false;
        }
    }else{
    
        return true;
    }
}

void CardTargets::useInitialAbility(){

    CCObject *object;
    CCARRAY_FOREACH(initialStatuses, object){
        Status *status = (Status*)object;
        status->applyStatus();
    }

    GameManager *GM = GameManager::sharedGameManager();
    GM->organizeMonsters();
    GM->organizeMarket();
    GM->player->organizeHand();
    GM->player->organizePlayedCards();
    GM->gameLayer->updateInterface();
}

//does what the ability should do
void CardTargets::useAbility(){
    if(isTargetRequired){
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
    }else{
        //do status
        CCObject *object;
        //        GameManager *GM = GameManager::sharedGameManager();
        CCARRAY_FOREACH(statuses, object){
            Status *status = (Status*)object;
            status->applyStatus();
        }
    }
    //apply status effects to monster
//    monster->updateInterface();
    
    
    GameManager *GM = GameManager::sharedGameManager();
    GM->organizeMonsters();
    GM->organizeMarket();
    GM->gameLayer->updateInterface();
    GM->afterCardPlayedStateCheck();
    //clear targetArray
    selectedTargets->removeAllObjects();
}

