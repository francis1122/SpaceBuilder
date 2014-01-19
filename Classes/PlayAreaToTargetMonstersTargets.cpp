//
//  PlayAreaToTargetMonstersTargets.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/10/14.
//
//

#include "PlayAreaToTargetMonstersTargets.h"


#include "GameManager.h"
#include "CardSprite.h"
#include "MonsterSprite.h"
#include "UIState.h"
#include "Player.h"
#include "Constants.h"
#include "Statuses.h"

// on "init" you need to initialize your instance
bool PlayAreaToTargetMonstersTargets::init()
{
    
    if(!CardTargets::init()){
        return false;
    }
    
    return true;
}


void PlayAreaToTargetMonstersTargets::highlightInteractiveObjects(UIState* state){
    GM->gameLayer->enablePlayAreaInteractive();
    GM->gameLayer->changeIndicatorState("Play Area");
    
}

void PlayAreaToTargetMonstersTargets::highlightNextInteractiveObjects(UIState* state){
    //highlight only monsters
    CCObject *object;
    bool tauntIsPresent = GM->tauntPresent();
    
    CCARRAY_FOREACH(GM->monsterArray, object){
        MonsterSprite *monster = (MonsterSprite*)object;
        if(monster->life >= minMonsterLife || minMonsterLife == -1){
            if(monster->life <= maxMonsterLife || maxMonsterLife == -1){
                if(tauntIsPresent){
                    if(monster->hasTaunt){
                        monster->enableInteractive();
                    }
                }else{
                    monster->enableInteractive();
                }
            }
        }
    }
    GM->gameLayer->changeIndicatorState("Target Monsters");
    
    
}

//checks whether the ability can be activated
bool PlayAreaToTargetMonstersTargets::isAbilityActivatable(UIState* state){
    int targetCount = 0;
    bool tauntIsPresent = GM->tauntPresent();
    CCObject *object;
    CCARRAY_FOREACH(GM->monsterArray, object){
        MonsterSprite *monster = (MonsterSprite*)object;
        if(monster->life >= minMonsterLife || minMonsterLife == -1){
            if(monster->life <= maxMonsterLife || maxMonsterLife == -1){
                if(tauntIsPresent){
                    if(monster->hasTaunt){
                        targetCount++;
                    }
                }else{
                    targetCount++;
                }
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
bool PlayAreaToTargetMonstersTargets::targetObjectWithHandCard(CCTouch* touch, UIState* state, CardSprite *card){
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    bool tauntIsPresent = GM->tauntPresent();
    //monsters are an exceptable place
    CCObject *object;
    CCARRAY_FOREACH(GM->monsterArray, object){
        MonsterSprite *monster = (MonsterSprite*)object;
        CCRect collisionRect = CCRectMake(monster->getPosition().x - monster->getContentSize().width/2 * monster->getScale(), monster->getPosition().y - monster->getContentSize().height/2 * monster->getScale(), monster->getContentSize().width * monster->getScale(), monster->getContentSize().height * monster->getScale());
        if(collisionRect.containsPoint(touchPoint)){
            if(monster->life >= minMonsterLife || minMonsterLife == -1){
                if(monster->life <= maxMonsterLife || maxMonsterLife == -1){
                    if(tauntIsPresent){
                        if(monster->hasTaunt){
                            selectedTargets->addObject(monster);
                            return true;
                        }
                    }else{
                        selectedTargets->addObject(monster);
                        return true;
                    }
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
bool PlayAreaToTargetMonstersTargets::targetObjectWithTargetingState(CCTouch* touch, UIState* state, CardSprite *card){
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    bool tauntIsPresent = GM->tauntPresent();
    //monsters are an exceptable place
    CCObject *object;
    CCARRAY_FOREACH(GM->monsterArray, object){
        MonsterSprite *monster = (MonsterSprite*)object;
        CCRect collisionRect = CCRectMake(monster->getPosition().x - monster->getContentSize().width/2 * monster->getScale(), monster->getPosition().y - monster->getContentSize().height/2 * monster->getScale(), monster->getContentSize().width * monster->getScale(), monster->getContentSize().height * monster->getScale());
        if(collisionRect.containsPoint(touchPoint)){
            if(tauntIsPresent){
                if(monster->life >= minMonsterLife || minMonsterLife == -1){
                    if(monster->life <= maxMonsterLife || maxMonsterLife == -1){
                        if(monster->hasTaunt){
                            selectedTargets->addObject(monster);
                            return true;
                        }
                    }else{
                        selectedTargets->addObject(monster);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// checks whether the ability can be used
bool PlayAreaToTargetMonstersTargets::isAbilityReady(){
    if(selectedTargets->count() >= targetAmount){
        return true;
    }else{
        return false;
    }
}

//changes the state
void PlayAreaToTargetMonstersTargets::changeState(UIState* state, CardSprite *card){
    state->transitionToCardTargetingState(card);
}

void PlayAreaToTargetMonstersTargets::useInitialAbility(){
    
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
void PlayAreaToTargetMonstersTargets::useAbility(){
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

