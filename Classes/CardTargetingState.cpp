//
//  CardTargetingState.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/21/13.
//
//

#include "CardTargetingState.h"

#include "HandCardSelectedState.h"
#include "GameManager.h"
#include "NormalState.h"
#include "MonsterSprite.h"
#include "CardTargets.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool CardTargetingState::init(CardSprite *_selectedCard)
{
    if(!UIState::init()){
        return false;
    }
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCLog("card targeting state");
    this->selectedCard = _selectedCard;
    GameManager *GM = GameManager::sharedGameManager();
    GM->gameLayer->changeIndicatorState(selectedCard->cardTargets->targetingType);
    GM->gameLayer->setButtonLabels("", "");
    return true;
}

#pragma mark - touch events
bool CardTargetingState::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    CCLog("card targeting touch");
    
    //tap a monster
    return true;
}

void CardTargetingState::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    //    GameManager *GM = GameManager::sharedGameManager();
    //get touch location
    //   CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
}

void CardTargetingState::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    GameManager *GM = GameManager::sharedGameManager();
    selectedCard->cardTargets->targetObject(touch);

    if(selectedCard->cardTargets->isAbilityReady()){
        selectedCard->cardTargets->useAbility();
        GM->player->organizeHand();
        selectedCard = NULL;
        this->transitionToNormalState();
    }

}

void CardTargetingState::ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
//    this->transitionToNormalState();
//    GameManager *GM = GameManager::sharedGameManager();
//    GM->player->organizeHand();
}

#pragma mark - state transitions

void CardTargetingState::transitionToNormalState(){
    GameManager *GM = GameManager::sharedGameManager();
    NormalState *NS =  new NormalState();
    NS->init();
    NS->autorelease();
    GM->gameLayer->changeState(NS);
    GM->gameLayer->updateInterface();
}

void CardTargetingState::transitionToHandCardSelectedState(CardSprite* selectedCard){
    CCLog("error:already in handCardSelectedState");
}

void CardTargetingState::transitionToSelectMonsterState(CardSprite* selectedCard){
    
}


void CardTargetingState::transitionToCardTargetingState(CardSprite* selectedCard){

}