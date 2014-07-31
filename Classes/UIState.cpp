//
//  UIState.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/18/13.
//
//

#include "UIState.h"
#include "GameManager.h"
#include "GameLayer.h"
#include "CardSprite.h"
#include "CardTargets.h"
#include "HandLayer.h"
#include "MonsterTurnState.h"
#include "MonsterLayer.h"
#include "LLMath.h"
#include "SolarSystemObject.h"
#include "SolarSystemDetailsLayer.h"
#include "SolarSystemDetailsState.h"
#include "ResearchSelectState.h"
#include "ResearchTypeTargetLayer.h"
#include "ResearchTypeTargetState.h"
#include "ResourceCardInfoLayer.h"
#include "CardInfoLayer.h"
#include "SolarSystemWorldDetailsLayer.h"
#include "ShipModel.h"
#include "ShipSprite.h"
#include "shipWorldDetailsLayer.h"

#define PAN_VELOCITY_SPEED 6.8
#define PAN_VELOCITY_FRICTION .65
#define PAN_VELOCITY_MAX 2000.0
#define PAN_VELOCITY_MIN 0.3

#define OVERLAY_HEIGHT 100


CCPoint UIState::previousTouchPoint;
CCPoint UIState::deltaTouch;
CCPoint UIState::cameraVelocity;
bool UIState::isDraggingCamera = false;

// on "init" you need to initialize your instance
bool UIState::init()
{
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    return true;
}

#pragma mark - utility functions
CardSprite *UIState::handCardAtPoint(cocos2d::CCTouch*touch){
    //get touch location
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    CCObject *object;
    CCARRAY_FOREACH(GM->player->handCards, object){
        CardSprite *card = (CardSprite*)object;
        CCRect collisionRect = CCRectMake(card->getPosition().x - card->getContentSize().width/2 * card->getScale(), card->getPosition().y - card->getContentSize().height/2 * card->getScale(), card->getContentSize().width * card->getScale(), card->getContentSize().height * card->getScale() );
        bool stuff = collisionRect.containsPoint(touchPoint);
        if(stuff){
            return card;
        }
    }
    return NULL;
}

SolarSystemObject *UIState::solarSystemObjectAtPoint(cocos2d::CCTouch *touch){
    //get touch location
    CCPoint touchPoint = GM->gameLayer->monsterLayer->convertTouchToNodeSpace(touch);
//    CCLog("solarTouch: %f, %f", touchPoint.x, touchPoint.y);
    CCObject *object;
    CCARRAY_FOREACH(GM->solarSystemArray, object){
        SolarSystemObject *solarSystem = (SolarSystemObject*)object;
        CCRect collisionRect = CCRectMake(solarSystem->getPosition().x - solarSystem->getContentSize().width/2 * solarSystem->getScale(), solarSystem->getPosition().y - solarSystem->getContentSize().height/2 * solarSystem->getScale(), solarSystem->getContentSize().width * solarSystem->getScale(), solarSystem->getContentSize().height * solarSystem->getScale() );
        bool isHit = collisionRect.containsPoint(touchPoint);
        if(isHit){
            return solarSystem;
        }
    }
    return NULL;
}


CardSprite *UIState::marketCardAtPoint(cocos2d::CCTouch*touch){
    /*
    GameManager *GM = GameManager::sharedGameManager();
    //get touch location
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    CCObject *object;
    CCARRAY_FOREACH(GM->marketCardArray, object){
        CardSprite *card = (CardSprite*)object;
        CCRect collisionRect = CCRectMake(card->getPosition().x - card->getContentSize().width/2 * card->getScale(), card->getPosition().y - card->getContentSize().height/2 * card->getScale(), card->getContentSize().width * card->getScale(), card->getContentSize().height * card->getScale() );
        bool stuff = collisionRect.containsPoint(touchPoint);
        if(stuff){
            return card;
        }
    }
    */
    return NULL;
}

ShipModel *UIState::shipAtPoint(CCTouch*touch)
{
    CCPoint touchPoint = GM->gameLayer->monsterLayer->convertTouchToNodeSpace(touch);
    //    CCLog("solarTouch: %f, %f", touchPoint.x, touchPoint.y);
    CCObject *object;
    CCARRAY_FOREACH(GM->shipsArray, object){
        ShipModel *shipModel = (ShipModel*)object;
        ShipSprite *shipSprite = shipModel->worldShipSprite;
        CCRect collisionRect = CCRectMake(shipSprite->getPosition().x - shipSprite->getContentSize().width/2 * shipSprite->getScale(), shipSprite->getPosition().y - shipSprite->getContentSize().height/2 * shipSprite->getScale(), shipSprite->getContentSize().width * shipSprite->getScale(), shipSprite->getContentSize().height * shipSprite->getScale() );
        bool isHit = collisionRect.containsPoint(touchPoint);
        if(isHit){
            return shipModel;
        }
    }
    return NULL;
}


CCObject* UIState::objectAtPoint(cocos2d::CCTouch* touch){
    //get touch location
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    //cycle through possible things that can be touched in state
    CCObject *objectAtPoint = NULL;
    CCObject *object;
    CCARRAY_FOREACH(GM->player->handCards, object){
        CardSprite *card = (CardSprite*)object;
        CCRect collisionRect = CCRectMake(card->getPosition().x - card->getContentSize().width/2 * card->getScale(), card->getPosition().y - card->getContentSize().height/2 * card->getScale(), card->getContentSize().width * card->getScale(), card->getContentSize().height * card->getScale() );
        bool stuff = collisionRect.containsPoint(touchPoint);
        if(stuff){
            return object;
        }
    }
    
    
    return objectAtPoint;
}

//visualize what can be touched
void UIState::clearInteractiveState(){
    CCObject *object;
    GM->gameLayer->changeIndicatorState("");
    CCARRAY_FOREACH(GM->player->handCards, object){
        CardSprite *card = (CardSprite*)object;
        card->disableInteractive();
    }
    
    //unhighlight planets
    CCARRAY_FOREACH(GM->solarSystemArray, object){
        SolarSystemObject *solarSystem = (SolarSystemObject*)object;
            solarSystem->setHighlighted(false);
    }
    
    GM->gameLayer->researchTypeTargetLayer->setVisible(false);
    
    GM->gameLayer->setButtonLabels("", "");
    GM->gameLayer->handLayer->disableDeckInteractive();
    GM->gameLayer->disablePlayAreaInteractive();
    GM->gameLayer->disablePlayAreaInteractive();
    GM->gameLayer->disableLeftButtonInteractive();
    GM->gameLayer->disableRightButtonInteractive();
    
}


void UIState::defaultInteractiveState(){
    //clear state
    clearInteractiveState();
    CCObject *object;
    CCARRAY_FOREACH(GM->solarSystemArray, object){
        SolarSystemObject *solarSystem = (SolarSystemObject*)object;
        solarSystem->setHighlighted(false);
    }
    
    GM->gameLayer->researchTypeTargetLayer->setVisible(false);
    GM->gameLayer->solarSystemDetailsLayer->setVisible(false);
    GM->gameLayer->cardInfoLayer->setVisible(false);
    GM->gameLayer->resourceCardInfoLayer->setVisible(false);
    GM->gameLayer->handLayer->setVisible(true);
    GM->gameLayer->solarSystemWorldDetailsLayer->setVisible(false);
    GM->gameLayer->shipWorldDetailsLayer->setVisible(false);
    GM->gameLayer->changeIndicatorState("");
    
    
    GM->gameLayer->setButtonLabels("", "End Turn");
    
    GM->gameLayer->disableLeftButtonInteractive();
    GM->gameLayer->disableRightButtonInteractive();
    
    //if there are no actions left, make right action glow
  /*  if(!GM->hasMorePlayerInteraction()){
        GM->gameLayer->enableRightButtonMustEndTurnInteractive();
    }
*/
}


#pragma mark - touch events
bool UIState::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    CCPoint touchPoint = GM->gameLayer->monsterLayer->convertTouchToNodeSpace(touch);
    UIState::previousTouchPoint = touchPoint;
    UIState::isDraggingCamera = false;
    return true;
}

void UIState::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){

    CCPoint touchPoint = GM->gameLayer->monsterLayer->convertTouchToNodeSpace(touch);
    UIState::previousTouchPoint = touchPoint;
    
}

void UIState::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    UIState::deltaTouch = CCPointZero;
    UIState::isDraggingCamera = false;
}

void UIState::ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
    UIState::deltaTouch = CCPointZero;
    UIState::isDraggingCamera = false;
}

void UIState::doubleTap(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
//    CCLog("doubletap");
}


//button touches
void UIState::leftButtonTouch(){
    CCLog("UIState::leftButtonTouch");
}


void UIState::rightButtonTouch(){
    CCLog("UIState::rightButtonTouch");
}


#pragma mark -collision checks

bool UIState::cardInDiscardArea(CardSprite* card){
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCRect collisionRect = CCRectMake(950, 0, 200, 200);
    if(collisionRect.containsPoint(card->getPosition()) ){
        return true;
    }
    return false;
}

bool UIState::cardInPlayArea(CardSprite* card){
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCRect collisionRect = CCRectMake(0, 180, visibleSize.width, 960);
    if(collisionRect.containsPoint(card->getPosition()) ){
        return true;
    }
    return false;
}

int UIState::cardInTechQuadrant(CardSprite* card){
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCRect militaryRect = CCRectMake(0, 180, visibleSize.width/4, 960);
    if(militaryRect.containsPoint(card->getPosition())){
        return 0;
    }
    CCRect industryRect = CCRectMake(visibleSize.width/4, 180, visibleSize.width/4, 960);
    if(industryRect.containsPoint(card->getPosition())){
        return 1;
    }
    CCRect expandingRect = CCRectMake(visibleSize.width/2, 180, visibleSize.width/4, 960);
    if(expandingRect.containsPoint(card->getPosition())){
        return 2;
    }
    CCRect scienceRect = CCRectMake(visibleSize.width/4 + visibleSize.width/2, 180, visibleSize.width/4, 960);
    if(scienceRect.containsPoint(card->getPosition())){
        return 3;
    }
    return -1;
}

bool UIState::cardInSellArea(CardSprite*card){
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCRect collisionRect = CCRectMake(visibleSize.width - 180, visibleSize.height -  180, 180, 180);
    if(collisionRect.containsPoint(card->getPosition()) ){
        return true;
    }
    return false;
}

MonsterSprite* UIState::doesCardTouchMonster(CardSprite* card){
    CCObject *object;
  /*  CCARRAY_FOREACH(GM->monsterArray, object){
        MonsterSprite *monster = (MonsterSprite*)object;
        CCRect collisionRect = CCRectMake(monster->getPosition().x - monster->getContentSize().width/2, monster->getPosition().y - monster->getContentSize().height/2, monster->getContentSize().width, monster->getContentSize().height);
        if(collisionRect.containsPoint(card->getPosition()) ){
            CCLog("monster has been hit");
            return monster;
        }
    }
    */
    return NULL;
}

MonsterSprite* UIState::doesPointTouchMonster(CCTouch *touch){
    CCObject *object;
    //get touch location
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    
 /*   CCARRAY_FOREACH(GM->monsterArray, object){
        MonsterSprite *monster = (MonsterSprite*)object;
        CCRect collisionRect = CCRectMake(monster->getPosition().x - monster->getContentSize().width/2, monster->getPosition().y - monster->getContentSize().height/2, monster->getContentSize().width, monster->getContentSize().height);
        if(collisionRect.containsPoint(touchPoint) ){
            CCLog("monster has been hit");
            return monster;
        }
    }
  */
    
    return NULL;
}

#pragma mark -camera

void UIState::sideCameraMovement(cocos2d::CCTouch* touch){
    CCPoint touchPoint = GM->gameLayer->monsterLayer->convertTouchToNodeSpace(touch);
    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
        //    CCSize visibleSize =
    float edgeLimit = 50;
    moveCameraDown = false;
    moveCameraLeft = false;
    moveCameraRight = false;
    moveCameraUp = false;
    if(touchPoint.x < edgeLimit){
        //        cameraVelocity = ccp(7, cameraVelocity.y);
        moveCameraUp = true;
    }
    if(touchPoint.x > winSize.width - edgeLimit){
        //        cameraVelocity = ccp(-7, cameraVelocity.y);
        moveCameraDown = true;
    }
    if(touchPoint.y < edgeLimit){
        //      cameraVelocity = ccp(cameraVelocity.x, 7);
        moveCameraLeft = true;
    }
    if(touchPoint.y > winSize.height - edgeLimit){
        //        cameraVelocity = ccp(cameraVelocity.x, -7);
        moveCameraRight = true;
    }
}

//map movement functions
void UIState::cameraOnTouchBegan(cocos2d::CCTouch* touch){
    CCPoint touchPoint = GM->gameLayer->monsterLayer->convertTouchToNodeSpace(touch);
    UIState::previousTouchPoint = touchPoint;
    //    cameraVelocity = CGPointZero;
}

void UIState::cameraOnTouchMoved(cocos2d::CCTouch* touch){
    CCPoint touchPoint = GM->gameLayer->monsterLayer->convertTouchToNodeSpace(touch);
    //  NSLog(@"pintPoint %f, %f", touchPoint.x, touchPoint.y);
    UIState::isDraggingCamera = true;
    UIState::deltaTouch = ccpSub(touchPoint, previousTouchPoint);
    UIState::previousTouchPoint = touchPoint;
    // playLayer.boardLayer.position = ccpAdd(UIState.playLayer.boardLayer.position, deltaTouch);
 //   this->checkCameraBounds();
}

void UIState::cameraOnTouchEnded(cocos2d::CCTouch* touch){
    UIState::deltaTouch = CCPointZero;
}

void UIState::cameraOnTouchCancelled(cocos2d::CCTouch* touch){
    UIState::deltaTouch = CCPointZero;
}

void UIState::updateCamera(float dt){
    UIState::cameraVelocity = LLMath::truncate(cameraVelocity, (PAN_VELOCITY_MAX * dt));
    UIState::cameraVelocity = CCPointMake(cameraVelocity.x + PAN_VELOCITY_SPEED*(deltaTouch.x)*dt, cameraVelocity.y + PAN_VELOCITY_SPEED*(deltaTouch.y)*dt);
    CCPoint newCameraVel = ccp(cameraVelocity.x * PAN_VELOCITY_FRICTION, cameraVelocity.y * PAN_VELOCITY_FRICTION);
    CCPoint cameraDif = ccpSub(cameraVelocity, newCameraVel);
    cameraDif = ccpMult(cameraDif, dt * 15);
    //  NSLog(@"cameraVel %f, %f", cameraVelocity.x, cameraVelocity.y);
    //  NSLog(@"CameraDif %f, %f", cameraDif.x, cameraDif.y);
    UIState::cameraVelocity = ccpSub(cameraVelocity, cameraDif);
    
	if(ccpLength(cameraVelocity) * dt  < PAN_VELOCITY_MIN * dt){
		UIState::cameraVelocity = CCPointMake(0.0, 0.0);
	}
    
    if(moveCameraUp){
        UIState::cameraVelocity = ccp(7, cameraVelocity.y);
    }
    if(moveCameraDown){
        UIState::cameraVelocity = ccp(-7, cameraVelocity.y);
    }
    if(moveCameraLeft){
        UIState::cameraVelocity = ccp(cameraVelocity.x, 7);
    }
    if(moveCameraRight){
        UIState::cameraVelocity = ccp(cameraVelocity.x, -7);
    }
    
    GM->gameLayer->monsterLayer->setPosition(ccp(GM->gameLayer->monsterLayer->getPosition().x + cameraVelocity.x, GM->gameLayer->monsterLayer->getPosition().y + cameraVelocity.y));
    
    //    playLayer.boardLayer.position =;
   // this->checkCameraBounds();
}

void UIState::checkCameraBounds(){
    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint pos = GM->gameLayer->monsterLayer->getPosition();
    //   NSLog(@"%f, %f", pos.x, pos.y);
    if(pos.x > 0){
        GM->gameLayer->monsterLayer->setPosition(ccp(0, pos.y));
        UIState::cameraVelocity = ccp(0, cameraVelocity.y);
    }
    if(pos.y > OVERLAY_HEIGHT){
        GM->gameLayer->monsterLayer->setPosition(ccp(pos.x, OVERLAY_HEIGHT));
        UIState::cameraVelocity = ccp(cameraVelocity.x, 0);
    }
    
    //board limit
    CCSize limit = CCSizeMake(900,900);
    float widthLimit = -(limit.width - winSize.width);
    float heightLimit = -(limit.height - winSize.height);
    if(pos.x < widthLimit){
        GM->gameLayer->monsterLayer->setPosition(ccp(widthLimit, pos.y));
        UIState::cameraVelocity = ccp(0, cameraVelocity.y);
    }
    if(pos.y < heightLimit){
        GM->gameLayer->monsterLayer->setPosition(ccp(pos.x, heightLimit));
        UIState::cameraVelocity = ccp(cameraVelocity.x, 0);
    }
}

void UIState::cleanCameraVariables(){
    UIState::cameraVelocity = CCPointZero;
    UIState::deltaTouch = CCPointZero;
    UIState::previousTouchPoint = CCPointZero;
    moveCameraDown = false;
    moveCameraLeft = false;
    moveCameraRight = false;
    moveCameraUp = false;
}




#pragma mark -state transitions

void UIState::transitionToNormalState(){
    
}

void UIState::transitionToHandCardSelectedState(CardSprite* selectedCard){
    
}

void UIState::transitionToSelectMonsterState(CardSprite* selectedCard){
    
}

void UIState::transitionToCardTargetingState(CardSprite* selectedCard){
    
}

void UIState::transitionToSolarSystemDetailsState(SolarSystemObject *selectedSolarSystem)
{
    
}

void UIState::transitionToResearchTypeTargetState(CardSprite* selectedCard)
{
    
}

void UIState::transitionToResearchState()
{
    
}

void UIState::transitionToResearchSelectState(CardSprite *selectedCard)
{
    ResearchTypeTargetState *RTTS = new ResearchTypeTargetState();
    RTTS->init(selectedCard);
    RTTS->autorelease();
    GM->gameLayer->changeState(RTTS);
}

void UIState::transitionToCardDraggingState(CardSprite* selectedCard){
    CCLog("empty transitionToCardDraggingState");
}

void UIState::transitionToMonsterTurnState()
{
    MonsterTurnState *MTS = new MonsterTurnState();
    MTS->init();
    MTS->autorelease();
    GM->gameLayer->changeState(MTS);
}

//type 0 = hand card, 1 = monster card, 2 = market card
void UIState::transitionToZoomState(CCObject *selectedObject, int type){
    
}


void UIState::transitionToShipTargetingState(Ability *ability)
{
    
}

void UIState::transitionToSolarSystemWorldDetailsState(SolarSystemObject *selectedSolarSystem)
{
    
}

void UIState::transitionToShipWorldDetailsState(ShipModel *selectedShipModel)
{
    
}

