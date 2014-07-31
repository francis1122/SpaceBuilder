//
//  ShipWorldDetailsState.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 7/28/14.
//
//

#include "ShipWorldDetailsState.h"
#include "ShipModel.h"
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
#include "HandLayer.h"
#include "ShipWorldDetailsLayer.h"
#include "SolarSystemWorldDetailsState.h"
#include "ShipWorldDetailsState.h"
#include "ShipTargetingState.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool ShipWorldDetailsState::init(ShipModel *_shipModel)
{
    if(!UIState::init()){
        return false;
    }
    
    selectedShipModel = _shipModel;
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    UIState::defaultInteractiveState();
//    GM->gameLayer->enableLeftButtonInteractive();
    GM->gameLayer->enableRightButtonInteractive();
    GM->gameLayer->handLayer->setVisible(false);
    GM->gameLayer->shipWorldDetailsLayer->updateInterface(_shipModel);
    GM->gameLayer->shipWorldDetailsLayer->setVisible(true);
    GM->gameLayer->updateInterface();
    return true;
}

#pragma mark - touch events
bool ShipWorldDetailsState::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    UIState::ccTouchBegan(touch, event);
    
    
    return true;
}

void ShipWorldDetailsState::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    UIState::cameraOnTouchMoved(touch);
}

void ShipWorldDetailsState::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    
    if(!isDraggingCamera){
        //checks for a solarSystem touch
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

void ShipWorldDetailsState::ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
    //    UIState::ccTouchCancelled(touch, event);
    UIState::ccTouchCancelled(touch, event);
}

void ShipWorldDetailsState::doubleTap(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
    //    CCLog("Normal doubletap");
    CardSprite *handCard = this->handCardAtPoint(touch);
    if(handCard){
        this->transitionToZoomState(handCard, 0);
        return;
    }
/*    SolarSystemObject *solarSystem = this->solarSystemObjectAtPoint(touch);
    if(solarSystem){
        //go to
        this->transitionToSolarSystemDetailsState(solarSystem);
        return;
    }
 */
}

//button touches
void ShipWorldDetailsState::leftButtonTouch(){
//    CCLog("UIState::leftButtonTouch");
}

void ShipWorldDetailsState::rightButtonTouch(){
    //used to deselect
    transitionToNormalState();
}

#pragma mark - state transitions

void ShipWorldDetailsState::transitionToNormalState(){
    NormalState *NS =  new NormalState();
    NS->init();
    NS->autorelease();
    GM->gameLayer->changeState(NS);
    GM->player->finishedPlayingCard();
    GM->player->organizeHand();
    GM->gameLayer->updateInterface();
    
}

void ShipWorldDetailsState::transitionToSolarSystemWorldDetailsState(SolarSystemObject *selectedSolarSystem)
{
    SolarSystemWorldDetailsState *SSWDS = new SolarSystemWorldDetailsState();
    SSWDS->init(selectedSolarSystem);
    SSWDS->autorelease();
    GM->gameLayer->changeState(SSWDS);
}

void ShipWorldDetailsState::transitionToSolarSystemDetailsState(SolarSystemObject *selectedSolarSystem)
{
    SolarSystemDetailsState *SSDS = new SolarSystemDetailsState();
    SSDS->init(selectedSolarSystem);
    SSDS->autorelease();
    GM->gameLayer->changeState(SSDS);
}

void ShipWorldDetailsState::transitionToShipWorldDetailsState(ShipModel *selectedShipModel)
{
    ShipWorldDetailsState *SWDS = new ShipWorldDetailsState();
    SWDS->init(selectedShipModel);
    SWDS->autorelease();
    GM->gameLayer->changeState(SWDS);
}

void ShipWorldDetailsState::transitionToShipTargetingState(Ability *ability)
{
    ShipTargetingState *STS = new ShipTargetingState();
    STS->init(ability);
    STS->autorelease();
    GM->gameLayer->changeState(STS);
    
}
