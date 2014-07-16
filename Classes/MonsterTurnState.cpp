//
//  MonsterTurnState.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 2/7/14.
//
//

#include "MonsterTurnState.h"


#include "GameManager.h"
#include "HandCardSelectedState.h"
#include "ZoomState.h"
#include "GameLayer.h"
#include "CardSprite.h"
#include "NormalState.h"
#include "Constants.h"
#include "AnimationManager.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool MonsterTurnState::init()
{
    if(!UIState::init()){
        return false;
    }
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
//    GameManager *GM = GameManager::sharedGameManager();
    UIState::clearInteractiveState();
        GM->setIsInteractive(false);
    AM->endTurnAnimation();
    
    return true;
}


#pragma mark - touch events
bool MonsterTurnState::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    CCLog("touch began");
    return false;
}

void MonsterTurnState::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    //  GameManager *GM = GameManager::sharedGameManager();
    //get touch location
    //    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
}

void MonsterTurnState::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    //    GameManager *GM = GameManager::sharedGameManager();
    //get touch location
    //CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
}

void MonsterTurnState::ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
    
}

void MonsterTurnState::doubleTap(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
//    CCLog("Normal doubletap");
    /*
    CardSprite *handCard = this->handCardAtPoint(touch);
    if(handCard){
        this->transitionToZoomState(handCard, 0);
    }
    MonsterSprite *monster = this->monsterCardAtPoint(touch);
    if(monster){
        this->transitionToZoomState(monster, 1);
    }
    CardSprite *marketCard = this->marketCardAtPoint(touch);
    if(marketCard){
        this->transitionToZoomState(marketCard, 2);
    }
    */
}

//button touches
void MonsterTurnState::leftButtonTouch(){
    CCLog("UIState::leftButtonTouch");
}


void MonsterTurnState::rightButtonTouch(){
    //end turn
    GM->endTurn();
}

#pragma mark - state transitions

void MonsterTurnState::transitionToNormalState()
{
    GM->setIsInteractive(true);
    NormalState *NS =  new NormalState();
    NS->init();
    NS->autorelease();
    GM->gameLayer->changeState(NS);
}


