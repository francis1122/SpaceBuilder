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


#define PAN_VELOCITY_SPEED 6.8
#define PAN_VELOCITY_FRICTION .65
#define PAN_VELOCITY_MAX 2000.0
#define PAN_VELOCITY_MIN 0.3

#define OVERLAY_HEIGHT 100

// on "init" you need to initialize your instance
bool UIState::init()
{
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    return true;
}

#pragma mark - utility functions
CardSprite *UIState::handCardAtPoint(cocos2d::CCTouch*touch){
    GameManager *GM = GameManager::sharedGameManager();
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
    GameManager *GM = GameManager::sharedGameManager();
    //get touch location
    CCPoint touchPoint = GM->gameLayer->monsterLayer->convertTouchToNodeSpace(touch);
    CCLog("solarTouch: %f, %f", touchPoint.x, touchPoint.y);
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

MonsterSprite *UIState::monsterCardAtPoint(cocos2d::CCTouch*touch){
    /*
    GameManager *GM = GameManager::sharedGameManager();
    //get touch location
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    CCObject *object;
    CCARRAY_FOREACH(GM->monsterArray, object){
        MonsterSprite *monster = (MonsterSprite*)object;
        CCRect collisionRect = CCRectMake(monster->getPosition().x - monster->getContentSize().width/2 * monster->getScale(), monster->getPosition().y - monster->getContentSize().height/2 * monster->getScale(), monster->getContentSize().width  * monster->getScale(), monster->getContentSize().height * monster->getScale());
        bool stuff = collisionRect.containsPoint(touchPoint);
        if(stuff){
            return monster;
        }
    }
     */
    return NULL;
}


CCObject* UIState::objectAtPoint(cocos2d::CCTouch* touch){
    GameManager *GM = GameManager::sharedGameManager();
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
    GameManager *GM = GameManager::sharedGameManager();
    CCObject *object;
    GM->gameLayer->changeIndicatorState("");
    CCARRAY_FOREACH(GM->player->handCards, object){
        CardSprite *card = (CardSprite*)object;
        card->disableInteractive();
    }
    
    
    GM->gameLayer->setButtonLabels("", "");
    GM->gameLayer->handLayer->disableDeckInteractive();
    GM->gameLayer->handLayer->disableDiscardInterative();
    GM->gameLayer->disablePlayAreaInteractive();
    GM->gameLayer->disablePlayAreaInteractive();
    GM->gameLayer->disableLeftButtonInteractive();
    GM->gameLayer->disableRightButtonInteractive();
    
}


void UIState::highlightInteractiveObjects(CardSprite *card){
    clearInteractiveState();
    
}

void UIState::defaultInteractiveState(){
    //clear state
    clearInteractiveState();
    
    GameManager *GM = GameManager::sharedGameManager();
    CCObject *object;
    GM->gameLayer->solarSystemDetailsLayer->setVisible(false);
    GM->gameLayer->changeIndicatorState("");
    GM->gameLayer->enableRightButtonInteractive();
    GM->gameLayer->setButtonLabels("", "End Turn");
    
    //if there are no actions left, make right action glow
    if(!GM->hasMorePlayerInteraction()){
        GM->gameLayer->enableRightButtonMustEndTurnInteractive();
    }

}


#pragma mark - touch events
bool UIState::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    GameManager *GM = GameManager::sharedGameManager();
    CCPoint touchPoint = GM->gameLayer->monsterLayer->convertTouchToNodeSpace(touch);
    previousTouchPoint = touchPoint;
    return true;
}

void UIState::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    GameManager *GM = GameManager::sharedGameManager();
    CCPoint touchPoint = GM->gameLayer->monsterLayer->convertTouchToNodeSpace(touch);
    previousTouchPoint = touchPoint;
    
}

void UIState::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    deltaTouch = CCPointZero;
}

void UIState::ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
    deltaTouch = CCPointZero;
}

void UIState::doubleTap(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
    CCLog("doubletap");
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
    CCRect collisionRect = CCRectMake(0, 180, visibleSize.width, 160);
    if(collisionRect.containsPoint(card->getPosition()) ){
        return true;
    }
    return false;
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
    GameManager *GM = GameManager::sharedGameManager();
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
    GameManager *GM = GameManager::sharedGameManager();
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
    GameManager *GM = GameManager::sharedGameManager();
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
    GameManager *GM = GameManager::sharedGameManager();
    CCPoint touchPoint = GM->gameLayer->monsterLayer->convertTouchToNodeSpace(touch);
    previousTouchPoint = touchPoint;
    //    cameraVelocity = CGPointZero;
}

void UIState::cameraOnTouchMoved(cocos2d::CCTouch* touch){
    GameManager *GM = GameManager::sharedGameManager();
    CCPoint touchPoint = GM->gameLayer->monsterLayer->convertTouchToNodeSpace(touch);
    //  NSLog(@"pintPoint %f, %f", touchPoint.x, touchPoint.y);
    deltaTouch = ccpSub(touchPoint, previousTouchPoint);
    previousTouchPoint = touchPoint;
    // playLayer.boardLayer.position = ccpAdd(UIState.playLayer.boardLayer.position, deltaTouch);
 //   this->checkCameraBounds();
}

void UIState::cameraOnTouchEnded(cocos2d::CCTouch* touch){
    deltaTouch = CCPointZero;
}

void UIState::cameraOnTouchCancelled(cocos2d::CCTouch* touch){
    deltaTouch = CCPointZero;
}

void UIState::updateCamera(float dt){
    cameraVelocity = LLMath::truncate(cameraVelocity, (PAN_VELOCITY_MAX * dt));
    cameraVelocity = CCPointMake(cameraVelocity.x + PAN_VELOCITY_SPEED*(deltaTouch.x)*dt, cameraVelocity.y + PAN_VELOCITY_SPEED*(deltaTouch.y)*dt);
    CCPoint newCameraVel = ccp(cameraVelocity.x * PAN_VELOCITY_FRICTION, cameraVelocity.y * PAN_VELOCITY_FRICTION);
    CCPoint cameraDif = ccpSub(cameraVelocity, newCameraVel);
    cameraDif = ccpMult(cameraDif, dt * 15);
    //  NSLog(@"cameraVel %f, %f", cameraVelocity.x, cameraVelocity.y);
    //  NSLog(@"CameraDif %f, %f", cameraDif.x, cameraDif.y);
    cameraVelocity = ccpSub(cameraVelocity, cameraDif);
    
	if(ccpLength(cameraVelocity) * dt  < PAN_VELOCITY_MIN * dt){
		cameraVelocity = CCPointMake(0.0, 0.0);
	}
    
    if(moveCameraUp){
        cameraVelocity = ccp(7, cameraVelocity.y);
    }
    if(moveCameraDown){
        cameraVelocity = ccp(-7, cameraVelocity.y);
    }
    if(moveCameraLeft){
        cameraVelocity = ccp(cameraVelocity.x, 7);
    }
    if(moveCameraRight){
        cameraVelocity = ccp(cameraVelocity.x, -7);
    }
    GameManager *GM = GameManager::sharedGameManager();
    
    GM->gameLayer->monsterLayer->setPosition(ccp(GM->gameLayer->monsterLayer->getPosition().x + cameraVelocity.x, GM->gameLayer->monsterLayer->getPosition().y + cameraVelocity.y));
    
    //    playLayer.boardLayer.position =;
   // this->checkCameraBounds();
}

void UIState::checkCameraBounds(){
    GameManager *GM = GameManager::sharedGameManager();
    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint pos = GM->gameLayer->monsterLayer->getPosition();
    //   NSLog(@"%f, %f", pos.x, pos.y);
    if(pos.x > 0){
        GM->gameLayer->monsterLayer->setPosition(ccp(0, pos.y));
        cameraVelocity = ccp(0, cameraVelocity.y);
    }
    if(pos.y > OVERLAY_HEIGHT){
        GM->gameLayer->monsterLayer->setPosition(ccp(pos.x, OVERLAY_HEIGHT));
        cameraVelocity = ccp(cameraVelocity.x, 0);
    }
    
    //board limit
    CCSize limit = CCSizeMake(900,900);
    float widthLimit = -(limit.width - winSize.width);
    float heightLimit = -(limit.height - winSize.height);
    if(pos.x < widthLimit){
        GM->gameLayer->monsterLayer->setPosition(ccp(widthLimit, pos.y));
        cameraVelocity = ccp(0, cameraVelocity.y);
    }
    if(pos.y < heightLimit){
        GM->gameLayer->monsterLayer->setPosition(ccp(pos.x, heightLimit));
        cameraVelocity = ccp(cameraVelocity.x, 0);
    }
}

void UIState::cleanCameraVariables(){
    cameraVelocity = CCPointZero;
    deltaTouch = CCPointZero;
    previousTouchPoint = CCPointZero;
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

void UIState::transitionToCardDraggingState(CardSprite* selectedCard){
    CCLog("empty transitionToCardDraggingState");
}

void UIState::transitionToMonsterTurnState()
{
    GameManager *GM = GameManager::sharedGameManager();
    MonsterTurnState *MTS = new MonsterTurnState();
    MTS->init();
    MTS->autorelease();
    GM->gameLayer->changeState(MTS);
}

//type 0 = hand card, 1 = monster card, 2 = market card
void UIState::transitionToZoomState(CCObject *selectedObject, int type){
    
}



