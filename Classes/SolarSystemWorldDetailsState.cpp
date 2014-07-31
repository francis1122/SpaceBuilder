//
//  SolarSystemWorldDetailsState.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 7/28/14.
//
//

#include "SolarSystemWorldDetailsState.h"
#include "GameManager.h"
#include "NormalState.h"
#include "HandCardSelectedState.h"
#include "ZoomState.h"
#include "ResearchTypeTargetState.h"
#include "GameLayer.h"
#include "CardSprite.h"
#include "SolarSystemObject.h"
#include "SolarSystemDetailsLayer.h"
#include "SolarSystemDetailsState.h"
#include "ResearchState.h"
#include "SolarSystemWorldDetailsLayer.h"
#include "ShipWorldDetailsState.h"
#include "SolarSystemWorldDetailsState.h"
#include "HandLayer.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool SolarSystemWorldDetailsState::init(SolarSystemObject *_selectedSolarSystemObject)
{
    if(!UIState::init()){
        return false;
    }
    
    selectedSolarSystemObject = _selectedSolarSystemObject;
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    UIState::defaultInteractiveState();
    GM->gameLayer->enableLeftButtonInteractive();
    GM->gameLayer->enableRightButtonInteractive();
    GM->gameLayer->handLayer->setVisible(false);
    GM->gameLayer->solarSystemWorldDetailsLayer->updateInterface(_selectedSolarSystemObject);
    GM->gameLayer->solarSystemWorldDetailsLayer->setVisible(true);
    GM->gameLayer->updateInterface();
    return true;
}

#pragma mark - touch events
bool SolarSystemWorldDetailsState::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    UIState::ccTouchBegan(touch, event);
    
    return true;
}

void SolarSystemWorldDetailsState::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    UIState::cameraOnTouchMoved(touch);
}

void SolarSystemWorldDetailsState::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    //    UIState::ccTouchEnded(touch, event);
    //checks for a solarSystem touch
    if(!isDraggingCamera){
        SolarSystemObject *selectedSolarSystem = this->solarSystemObjectAtPoint(touch);
        if(selectedSolarSystem){
            this->transitionToSolarSystemWorldDetailsState(selectedSolarSystem);
            return;
        }
        
        ShipModel *selectedShip = this->shipAtPoint(touch);
        if(selectedShip){
            this->transitionToShipWorldDetailsState(selectedShip);
            return;
        }
        
        //if nothing was touched, return to normal state
        this->transitionToNormalState();
    }
    UIState::ccTouchEnded(touch, event);
}

void SolarSystemWorldDetailsState::ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
    //    UIState::ccTouchCancelled(touch, event);
    UIState::ccTouchCancelled(touch, event);
}

void SolarSystemWorldDetailsState::doubleTap(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
    //    CCLog("Normal doubletap");
    CardSprite *handCard = this->handCardAtPoint(touch);
    if(handCard){
        this->transitionToZoomState(handCard, 0);
        return;
    }
    SolarSystemObject *solarSystem = this->solarSystemObjectAtPoint(touch);
    if(solarSystem == selectedSolarSystemObject){
        //go to
        this->transitionToSolarSystemDetailsState(solarSystem);
        return;
    }
}

//button touches
void SolarSystemWorldDetailsState::leftButtonTouch(){
    transitionToSolarSystemDetailsState(selectedSolarSystemObject);
}

void SolarSystemWorldDetailsState::rightButtonTouch(){
    //end turn
    transitionToNormalState();
}

#pragma mark - state transitions

void SolarSystemWorldDetailsState::transitionToNormalState(){
    NormalState *NS =  new NormalState();
    NS->init();
    NS->autorelease();
    GM->gameLayer->changeState(NS);
    GM->player->finishedPlayingCard();
    GM->player->organizeHand();
    GM->gameLayer->updateInterface();
    
}

void SolarSystemWorldDetailsState::transitionToSolarSystemDetailsState(SolarSystemObject *selectedSolarSystem)
{
    SolarSystemDetailsState *SSDS = new SolarSystemDetailsState();
    SSDS->init(selectedSolarSystem);
    SSDS->autorelease();
    GM->gameLayer->changeState(SSDS);
}

void SolarSystemWorldDetailsState::transitionToSolarSystemWorldDetailsState(SolarSystemObject *selectedSolarSystem)
{
    SolarSystemWorldDetailsState *SSWDS = new SolarSystemWorldDetailsState();
    SSWDS->init(selectedSolarSystem);
    SSWDS->autorelease();
    GM->gameLayer->changeState(SSWDS);
}

void SolarSystemWorldDetailsState::transitionToShipWorldDetailsState(ShipModel *selectedShipModel)
{
    ShipWorldDetailsState *SWDS = new ShipWorldDetailsState();
    SWDS->init(selectedShipModel);
    SWDS->autorelease();
    GM->gameLayer->changeState(SWDS);
}

