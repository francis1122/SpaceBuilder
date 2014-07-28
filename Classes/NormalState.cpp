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
#include "ResearchTypeTargetState.h"
#include "GameLayer.h"
#include "CardSprite.h"
#include "SolarSystemObject.h"
#include "SolarSystemDetailsLayer.h"
#include "SolarSystemDetailsState.h"
#include "ResearchState.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool NormalState::init()
{
    if(!UIState::init()){
        return false;
    }
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    UIState::defaultInteractiveState();
    GM->gameLayer->updateInterface();
    return true;
}

#pragma mark - touch events
bool NormalState::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    UIState::ccTouchBegan(touch, event);
    CCObject *object = this->objectAtPoint(touch);
    if(object != NULL){
        CardSprite *card = (CardSprite*)object;
        if(card->cardTargets){
            card->cardTargets->initialChangeState(this, (CardSprite*)object);
        }else{
            this->transitionToHandCardSelectedState((CardSprite*)object);
        }
    }
    return true;
}

void NormalState::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
//    UIState::ccTouchMoved(touch, event);
    UIState::cameraOnTouchMoved(touch);
}

void NormalState::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
//    UIState::ccTouchEnded(touch, event);
    UIState::ccTouchEnded(touch, event);
}

void NormalState::ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
//    UIState::ccTouchCancelled(touch, event);
    UIState::ccTouchCancelled(touch, event);
}

void NormalState::doubleTap(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
//    CCLog("Normal doubletap");
    CardSprite *handCard = this->handCardAtPoint(touch);
    if(handCard){
        this->transitionToZoomState(handCard, 0);
        return;
    }
    SolarSystemObject *solarSystem = this->solarSystemObjectAtPoint(touch);
    if(solarSystem){
        //go to
        this->transitionToSolarSystemDetailsState(solarSystem);
        return;
    }
}

//button touches
void NormalState::leftButtonTouch(){
    CCLog("UIState::leftButtonTouch");
}

void NormalState::rightButtonTouch(){
    //end turn
    GM->endTurn();
}

#pragma mark - state transitions
void NormalState::transitionToNormalState(){
    CCLog("error:: already in normal state");
}


void NormalState::transitionToSolarSystemDetailsState(SolarSystemObject *selectedSolarSystem)
{
    SolarSystemDetailsState *SSDS = new SolarSystemDetailsState();
    SSDS->init(selectedSolarSystem);
    SSDS->autorelease();
    GM->gameLayer->changeState(SSDS);
}

void NormalState::transitionToHandCardSelectedState(CardSprite* selectedCard){
    HandCardSelectedState *HCSS =  new HandCardSelectedState();
    HCSS->init(selectedCard);
    HCSS->autorelease();
    GM->gameLayer->changeState(HCSS);
}

void NormalState::transitionToCardTargetingState(CardSprite* selectedCard){
    
}

//type 0 = hand card, 1 = monster card, 2 = market card
void NormalState::transitionToZoomState(CCObject *selectedObject, int type){
    //this function sucks balls, i hate the type stuff
    ZoomState *ZS = new ZoomState;
    if(type == 0){
        CardSprite *card = (CardSprite*)selectedObject;
        ZS->initCardSprite(card);
    }
    ZS->autorelease();
    GM->gameLayer->changeState(ZS);
}

void NormalState::transitionToResearchTypeTargetState(CardSprite* selectedCard)
{
    ResearchTypeTargetState *RTTS = new ResearchTypeTargetState();
    RTTS->init(selectedCard);
    RTTS->autorelease();
    GM->gameLayer->changeState(RTTS);
}

void NormalState::transitionToResearchState()
{
    ResearchState *RS = new ResearchState();
    RS->init();
    RS->autorelease();
    GM->gameLayer->changeState(RS);
}


