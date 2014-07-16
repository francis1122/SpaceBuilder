//
//  ResearchState.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 6/28/14.
//
//

#include "ResearchState.h"

#include "ResearchState.h"
#include "GameManager.h"
#include "HandCardSelectedState.h"
#include "ZoomState.h"
#include "GameLayer.h"
#include "CardSprite.h"
#include "SolarSystemObject.h"
#include "SolarSystemDetailsLayer.h"
#include "SolarSystemDetailsState.h"
#include "ResearchLayer.h"
#include "NormalState.h"
#include "ResearchSelectState.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool ResearchState::init()
{
    if(!UIState::init()){
        return false;
    }
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    UIState::defaultInteractiveState();
    GM->gameLayer->researchLayer->updateInterface();
    GM->gameLayer->researchLayer->setVisible(true);
    GM->gameLayer->updateInterface();
    return true;
}

#pragma mark - touch events
bool ResearchState::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    UIState::ccTouchBegan(touch, event);
    CCLog("touch began");
    CCObject *object = this->objectAtPoint(touch);
    if(object != NULL){
        this->transitionToResearchSelectState((CardSprite*)object);
    }
    return true;
}

void ResearchState::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    //    UIState::ccTouchMoved(touch, event);
    UIState::cameraOnTouchMoved(touch);
}

void ResearchState::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    //    UIState::ccTouchEnded(touch, event);
    UIState::ccTouchEnded(touch, event);
}

void ResearchState::ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
    //    UIState::ccTouchCancelled(touch, event);
    UIState::ccTouchCancelled(touch, event);
}

void ResearchState::doubleTap(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
    //    CCLog("Normal doubletap");
    CardSprite *handCard = this->handCardAtPoint(touch);
    if(handCard){
        this->transitionToZoomState(handCard, 0);
        return;
    }
}

//button touches
void ResearchState::leftButtonTouch(){
    CCLog("UIState::leftButtonTouch");
}

void ResearchState::rightButtonTouch(){
    //end turn
    
    GM->endTurn();
}

#pragma mark - state transitions
void ResearchState::transitionToNormalState(){
    
    NormalState *NS =  new NormalState();
    NS->init();
    NS->autorelease();
    GM->gameLayer->changeState(NS);
    GM->player->finishedPlayingCard();
    GM->player->organizeHand();
    //    GM->organizeMarket();
    GM->gameLayer->updateInterface();
}

void ResearchState::transitionToResearchSelectState(CardSprite *selectedCard)
{
    
    ResearchSelectState *RSS =  new ResearchSelectState();
    RSS->init(selectedCard);
    RSS->autorelease();
    GM->gameLayer->changeState(RSS);
}

void ResearchState::transitionToSolarSystemDetailsState(SolarSystemObject *selectedSolarSystem)
{
    
    SolarSystemDetailsState *SSDS = new SolarSystemDetailsState();
    SSDS->init(selectedSolarSystem);
    SSDS->autorelease();
    GM->gameLayer->changeState(SSDS);
}

void ResearchState::transitionToHandCardSelectedState(CardSprite* selectedCard)
{
    
    HandCardSelectedState *HCSS =  new HandCardSelectedState();
    HCSS->init(selectedCard);
    HCSS->autorelease();
    GM->gameLayer->changeState(HCSS);
}

void ResearchState::transitionToCardTargetingState(CardSprite* selectedCard)
{
    
}

//type 0 = hand card, 1 = monster card, 2 = market card
void ResearchState::transitionToZoomState(CCObject *selectedObject, int type){
    //this function sucks balls, i hate the type stuff
    
    ZoomState *ZS = new ZoomState;
    if(type == 0){
        CardSprite *card = (CardSprite*)selectedObject;
        ZS->initCardSprite(card);
    }
    ZS->autorelease();
    GM->gameLayer->changeState(ZS);
}