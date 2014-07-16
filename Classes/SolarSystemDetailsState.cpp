//
//  SolarSystemDetailsState.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 6/7/14.
//
//

#include "SolarSystemDetailsState.h"
#include "CardTargetingState.h"
#include "CardDraggingState.h"
#include "GameManager.h"
#include "SolarSystemObject.h"
#include "NormalState.h"
#include "SolarSystemDetailsLayer.h"
#include "CardTargets.h"
#include "CardSprite.h"
#include "GameLayer.h"
#include "HandLayer.h"


USING_NS_CC;

// on "init" you need to initialize your instance
bool SolarSystemDetailsState::init(SolarSystemObject *_selectedSolarSystemObject)
{
    if(!UIState::init()){
        return false;
    }
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    GM->gameLayer->solarSystemDetailsLayer->setVisible(true);
    CCLog("SolarSystemDetailsState");
    selectedSolarSystemObject = _selectedSolarSystemObject;
    //highlight should take care of buttons as well
    GM->gameLayer->setButtonLabels("", "Back");
    GM->gameLayer->solarSystemDetailsLayer->updateInterface(selectedSolarSystemObject);
    return true;
}

void SolarSystemDetailsState::doubleTap(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
}

#pragma mark - touch events
bool SolarSystemDetailsState::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    CCLog("selectedState");
    return true;
}

void SolarSystemDetailsState::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    //get touch location
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
}

void SolarSystemDetailsState::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    //get touch location
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    GM->player->organizeHand();
}

void SolarSystemDetailsState::ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
    this->transitionToNormalState();
    GM->player->organizeHand();
}

//button touches
void SolarSystemDetailsState::leftButtonTouch(){
    CCLog("UIState::leftButtonTouch");
}

void SolarSystemDetailsState::rightButtonTouch(){
    //end turn
    transitionToNormalState();
}

#pragma mark - state transitions

void SolarSystemDetailsState::transitionToNormalState(){
    NormalState *NS =  new NormalState();
    NS->init();
    NS->autorelease();
    GM->gameLayer->changeState(NS);
    GM->player->finishedPlayingCard();
    GM->player->organizeHand();
    //    GM->organizeMarket();
    GM->gameLayer->updateInterface();
    
}

void SolarSystemDetailsState::transitionToSolarSystemDetailsState(SolarSystemObject *selectedSolarSystem){
    CCLog("error:already in SolarSystemDetailsState");
}

void SolarSystemDetailsState::transitionToCardTargetingState(CardSprite* selectedCard){
    CardTargetingState *CTS =  new CardTargetingState();
    CTS->init(selectedCard);
    CTS->autorelease();
    GM->gameLayer->changeState(CTS);
    //    GM->organizeMarket();
    GM->gameLayer->updateInterface();
}

void SolarSystemDetailsState::transitionToCardDraggingState(CardSprite* selectedCard){
  //  GameManager *GM = GameManager::sharedGameManager();
}