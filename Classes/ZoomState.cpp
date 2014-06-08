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

#include "CardTargets.h"
#include "GameLayer.h"
#include "ZoomLayer.h"
#include "MonsterLayer.h"
#include "HandLayer.h"
#include "Constants.h"

USING_NS_CC;

bool ZoomState::init(){
    if(!UIState::init()){
        return false;
    }
    GM->gameLayer->enterZoomState();
    GM->gameLayer->setButtonLabels("", "");
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
    this->selectedCard->removeFromParent();
    GM->gameLayer->zoomLayer->addChild(this->selectedCard, 100);
    this->selectedCard->setScale(1);
    this->selectedCard->stopAllActions();
    this->selectedCard->setPosition(ccp(350, visibleSize.height/2));
    this->selectedCard->isZoomed = true;
    isMarketCard = false;
    
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

    GM->gameLayer->leaveZoomState();

        selectedCard->removeFromParent();
        if(isMarketCard){
            GM->gameLayer->monsterLayer->addChild(this->selectedCard, 100);
        }else{
            GM->gameLayer->handLayer->addChild(this->selectedCard, 100);
        }
        
        selectedCard->setScale(DEFAULT_CARD_SCALE);
        selectedCard->setZOrder(10000);
        this->selectedCard->isZoomed = false;
        GM->player->organizeHand();
    selectedCard = NULL;
    selectedMonsterCard = NULL;
    NormalState *NS =  new NormalState();
    NS->init();
    NS->autorelease();
    GM->gameLayer->changeState(NS);
    GM->gameLayer->updateInterface();
}

void ZoomState::transitionToHandCardSelectedState(CardSprite* selectedCard){
    CCLog("error:already in handCardSelectedState");
}

void ZoomState::transitionToSelectMonsterState(CardSprite* selectedCard){
    
}

void ZoomState::transitionToCardTargetingState(CardSprite* selectedCard){
    
}