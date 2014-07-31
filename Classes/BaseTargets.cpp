//
//  BaseTargets.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 7/29/14.
//
//

#include "BaseTargets.h"
#include "BaseTargets.h"
#include "GameManager.h"
#include "CardSprite.h"
#include "UIState.h"
#include "Player.h"
#include "Statuses.h"
#include "GameLayer.h"
#include "Constants.h"


USING_NS_CC;


// on "init" you need to initialize your instance
bool BaseTargets::init()
{
    
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    selectedTargets = new CCArray();
    statuses = new CCArray();
    initialStatuses = new CCArray();
    
    
    selectedTargets->init();
    statuses->init();
    initialStatuses->init();
    targetAmount = 1;
    

    
    objectsToUse = CurrentPlayer;
    //which objects to apply status to
    applyToAllFriendly =  false;
    applyToHomeSystem = false;
    
    return true;
}


void BaseTargets::highlightInteractiveObjects(UIState* state)
{
    
}

void BaseTargets::highlightOnMove(UIState* state, CardSprite *card)
{
    
}

void BaseTargets::highlightNextInteractiveObjects(UIState* state)
{
    
}

void BaseTargets::highlightInteractiveObjectsWithDraggingState(UIState* state)
{
    
}

void BaseTargets::highlightInteractiveObjectsWithDraggingCard(UIState* state)
{
    
}

void BaseTargets::unableToActivateHighlight(UIState*)
{
    GM->gameLayer->changeIndicatorState("Cannot Play Card");
}

//checks whether the ability can be activated
bool BaseTargets::isAbilityActivatable(UIState* state){
    //check if proper amount is possible
    /* if(targetingType == PlayArea_TargetMonsters){
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
     CCLog("BaseTargets::isAbilityActivatable error");
     */
    return false;
}


//targets objects to use ability on
bool BaseTargets::targetObjectWithHandCard(CCTouch* touch, UIState* state, CardSprite *card){
    //get touch location
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    CCObject *object;
    
    //TODO: make this target specific objects such as cards in hand or market cards
    
    /*
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
     */
    return false;
}

//targets objects to use ability on
bool BaseTargets::targetObjectWithTargetingState(CCTouch* touch, UIState* state, CardSprite *card){
    return false;
}

CardSprite* BaseTargets::targetObjectWithDraggingState(CCTouch* touch, UIState* state, CardSprite *card){
    return NULL;
}

bool BaseTargets::targetObjectWithDraggingCard(CCTouch* touch, UIState* state, CardSprite *card){
    return false;
}

// checks whether the ability can be used
bool BaseTargets::isAbilityReady(){
    CCLog("BaseTargets::isAbilityReady error");
    return false;
}

//state to change to while card is being dragged around
void BaseTargets::initialChangeState(UIState *state, CardSprite *card)
{

}


//changes the state
void BaseTargets::changeState(UIState* state, CardSprite *card){
    
}

void BaseTargets::useInitialAbility(){
    
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
void BaseTargets::useAbility()
{

}

//utility functions
#pragma mark - utility functions