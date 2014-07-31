//
//  ShipTargetingState.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 7/29/14.
//
//

#include "ShipTargetingState.h"

#include "HandCardSelectedState.h"
#include "GameManager.h"
#include "NormalState.h"
#include "GameLayer.h"
#include "HandLayer.h"
#include "Ability.h"
#include "Targets.h"
#include "ShipWorldDetailsState.h"


USING_NS_CC;

// on "init" you need to initialize your instance
bool ShipTargetingState::init(Ability *_ability)
{
    if(!UIState::init()){
        return false;
    }
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCLog("card targeting state");
    this->selectedAbility = _ability;
    
    UIState::clearInteractiveState();
    GM->gameLayer->enableRightButtonInteractive();
    this->selectedAbility->targets->highlightInteractiveObjects(this, this->selectedAbility);
    GM->gameLayer->setButtonLabels("", "");
    return true;
}


#pragma mark - touch events
bool ShipTargetingState::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    UIState::ccTouchBegan(touch, event);
    return true;
}

void ShipTargetingState::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    UIState::cameraOnTouchMoved(touch);
}

void ShipTargetingState::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    if(!isDraggingCamera){
        AbilityTargets *targets = this->selectedAbility->targets;
        targets->targetObjectWithTargetingState(touch, this, this->selectedAbility);
        if(targets->isAbilityReady(this->selectedAbility)){
            targets->useAbility(this->selectedAbility);
            GM->player->organizeHand();
            selectedAbility = NULL;
            this->transitionToNormalState();
        }
    }
    
    UIState::ccTouchEnded(touch, event);
}

void ShipTargetingState::ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
    UIState::ccTouchCancelled(touch, event);
}



//button touches
void ShipTargetingState::leftButtonTouch(){
    CCLog("UIState::leftButtonTouch");
}

void ShipTargetingState::rightButtonTouch(){
    selectedAbility->targets->selectedTargets->removeAllObjects();
    //end turn
    transitionToShipWorldDetailsState(selectedAbility->shipModel);
}


#pragma mark - state transitions

void ShipTargetingState::transitionToNormalState(){
    
    NormalState *NS =  new NormalState();
    NS->init();
    NS->autorelease();
    GM->player->finishedPlayingCard();
    GM->gameLayer->changeState(NS);
    GM->gameLayer->updateInterface();
}

void ShipTargetingState::transitionToHandCardSelectedState(CardSprite* selectedCard){
    CCLog("error:already in handCardSelectedState");
}

void ShipTargetingState::transitionToShipWorldDetailsState(ShipModel *selectedShipModel)
{
    ShipWorldDetailsState *SWDS = new ShipWorldDetailsState();
    SWDS->init(selectedShipModel);
    SWDS->autorelease();
    GM->gameLayer->changeState(SWDS);
}

