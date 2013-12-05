//
//  ZoomState.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/27/13.
//
//

#include "ZoomState.h"

#include "HandCardSelectedState.h"
#include "GameManager.h"
#include "NormalState.h"
#include "MonsterSprite.h"
#include "CardTargets.h"
#include "GameLayer.h"

USING_NS_CC;

bool ZoomState::init(){
    if(!UIState::init()){
        return false;
    }
    GameManager *GM = GameManager::sharedGameManager();
    GM->gameLayer->enterZoomState();
    return true;
}

// on "init" you need to initialize your instance
bool ZoomState::initCardSprite(CardSprite *_selectedCard)
{
    if(!ZoomState::init()){
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCLog("card sprite");
    this->selectedCard = _selectedCard;
    this->selectedMonsterCard = NULL;
//    GameManager *GM = GameManager::sharedGameManager();
    this->selectedCard->setScale(1);
    this->selectedCard->setZOrder(1000);
    this->selectedCard->setPosition(ccp(350, visibleSize.height/2));
    
    return true;
}

bool ZoomState::initMonsterSprite(MonsterSprite *_selectedMonsterCard){
    if(!ZoomState::init()){
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCLog("card monster sprite");
    this->selectedMonsterCard = _selectedMonsterCard;
    this->selectedMonsterCard->setScale(1);
    this->selectedMonsterCard->setZOrder(1000);
    this->selectedMonsterCard->setPosition(ccp(350, visibleSize.height/2));
    this->selectedCard = NULL;
//    GameManager *GM = GameManager::sharedGameManager();

    
    return true;
}

bool ZoomState::initMarketCard(CardSprite *_selectedCard){
    if(!ZoomState::init()){
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCLog("card market card");
    this->selectedCard = _selectedCard;
    this->selectedCard->setScale(1);
    this->selectedCard->setZOrder(1000);
    this->selectedCard->setPosition(ccp(350, visibleSize.height/2));
    this->selectedMonsterCard = NULL;

//    GameManager *GM = GameManager::sharedGameManager();
    
    return true;
}



#pragma mark - touch events
bool ZoomState::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    CCLog("card targeting touch");
    
    //tap a monster
    return true;
}

void ZoomState::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    //    GameManager *GM = GameManager::sharedGameManager();
    //get touch location
    //   CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
}

void ZoomState::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
//    GameManager *GM = GameManager::sharedGameManager();

}

void ZoomState::ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){

}

#pragma mark - state transitions

void ZoomState::transitionToNormalState(){
    GameManager *GM = GameManager::sharedGameManager();

    GM->gameLayer->leaveZoomState();
    if(selectedMonsterCard != NULL){
        selectedMonsterCard->setScale(.25);
        selectedMonsterCard->setZOrder(10);
    }else{
        selectedCard->setScale(.25);
        selectedCard->setZOrder(10);
    }
    selectedCard = NULL;
    selectedMonsterCard = NULL;
    
    
    NormalState *NS =  new NormalState();
    NS->init();
    NS->autorelease();
    GM->gameLayer->changeState(NS);
    GM->gameLayer->updateInterface();
    GM->player->organizeHand();
    GM->organizeMarket();
    GM->organizeMonsters();
}

void ZoomState::transitionToHandCardSelectedState(CardSprite* selectedCard){
    CCLog("error:already in handCardSelectedState");
}

void ZoomState::transitionToSelectMonsterState(CardSprite* selectedCard){
    
}


void ZoomState::transitionToCardTargetingState(CardSprite* selectedCard){
    
}