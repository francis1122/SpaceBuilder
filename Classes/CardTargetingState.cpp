//
//  CardTargetingState.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/21/13.
//
//

#include "CardTargetingState.h"

#include "HandCardSelectedState.h"
#include "GameManager.h"
#include "NormalState.h"
#include "CardTargets.h"
#include "GameLayer.h"
#include "HandLayer.h"


USING_NS_CC;

// on "init" you need to initialize your instance
bool CardTargetingState::init(CardSprite *_selectedCard)
{
    if(!UIState::init()){
        return false;
    }
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCLog("card targeting state");
    this->selectedCard = _selectedCard;
    
    UIState::clearInteractiveState();
    this->selectedCard->cardTargets->highlightNextInteractiveObjects(this);
    GM->gameLayer->setButtonLabels("", "");
    return true;
}


#pragma mark - touch events
bool CardTargetingState::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    CCLog("card targeting touch");
    
    //tap a monster
    return true;
}

void CardTargetingState::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    //    
    //get touch location
    //   CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
}

void CardTargetingState::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    
    CardTargets *targets = selectedCard->cardTargets;
    targets->targetObjectWithTargetingState(touch, this, this->selectedCard);
        if(targets->isAbilityReady()){
            targets->useAbility();
            GM->player->organizeHand();
            selectedCard = NULL;
            this->transitionToNormalState();
        }
}

void CardTargetingState::ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
//    this->transitionToNormalState();
//    
//    GM->player->organizeHand();
}

#pragma mark - state transitions

void CardTargetingState::transitionToNormalState(){
    
    NormalState *NS =  new NormalState();
    NS->init();
    NS->autorelease();
    GM->player->finishedPlayingCard();
    GM->gameLayer->changeState(NS);
    GM->gameLayer->updateInterface();
}

void CardTargetingState::transitionToHandCardSelectedState(CardSprite* selectedCard){
    CCLog("error:already in handCardSelectedState");
}

void CardTargetingState::transitionToSelectMonsterState(CardSprite* selectedCard){
    
}


void CardTargetingState::transitionToCardTargetingState(CardSprite* selectedCard){

}