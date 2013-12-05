//
//  NormalState.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/18/13.
//
//

#include "NormalState.h"
#include "GameManager.h"
#include "HandCardSelectedState.h"
#include "ZoomState.h"
#include "GameLayer.h"
#include "CardSprite.h"
#include "MonsterSprite.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool NormalState::init()
{
    if(!UIState::init()){
        return false;
    }
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    GameManager *GM = GameManager::sharedGameManager();
    GM->gameLayer->changeIndicatorState(None);
    return true;
}


#pragma mark - touch events
bool NormalState::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    CCLog("touch began");
    CCObject *object = this->objectAtPoint(touch);
    if(object != NULL){
        this->transitionToHandCardSelectedState((CardSprite*)object);
    }
    return true;
}

void NormalState::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
  //  GameManager *GM = GameManager::sharedGameManager();
    //get touch location
//    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
}

void NormalState::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
//    GameManager *GM = GameManager::sharedGameManager();
    //get touch location
    //CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
}

void NormalState::ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
    
}

void NormalState::doubleTap(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
    CCLog("Normal doubletap");

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
    
}

#pragma mark - state transitions

void NormalState::transitionToNormalState(){
    CCLog("error:: already in normal state");
}

void NormalState::transitionToHandCardSelectedState(CardSprite* selectedCard){
    GameManager *GM = GameManager::sharedGameManager();
    HandCardSelectedState *HCSS =  new HandCardSelectedState();
    HCSS->init(selectedCard);
    HCSS->autorelease();
    GM->gameLayer->changeState(HCSS);
}

void NormalState::transitionToSelectMonsterState(CardSprite* selectedCard){
    
}

void NormalState::transitionToCardTargetingState(CardSprite* selectedCard){
    
}

//type 0 = hand card, 1 = monster card, 2 = market card
void NormalState::transitionToZoomState(CCObject *selectedObject, int type){
    //this function sucks balls, i hate the type stuff
    GameManager *GM = GameManager::sharedGameManager();
    ZoomState *ZS = new ZoomState;
    if(type == 0){
        CardSprite *card = (CardSprite*)selectedObject;
        ZS->initCardSprite(card);
    }else if(type == 1){
        MonsterSprite *monster = (MonsterSprite*)selectedObject;
        ZS->initMonsterSprite(monster);
    }else if(type == 2){
        CardSprite *card = (CardSprite*)selectedObject;
        ZS->initMarketCard(card);
    }
    ZS->autorelease();
    GM->gameLayer->changeState(ZS);
}


