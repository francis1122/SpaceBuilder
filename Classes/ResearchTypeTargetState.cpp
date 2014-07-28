//
//  ResearchTypeTargetState.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 7/14/14.
//
//

#include "ResearchTypeTargetState.h"
#include "CardTargetingState.h"
#include "CardDraggingState.h"
#include "GameManager.h"
#include "NormalState.h"
#include "CardTargets.h"
#include "CardSprite.h"
#include "GameLayer.h"
#include "HandLayer.h"


USING_NS_CC;

// on "init" you need to initialize your instance
bool ResearchTypeTargetState::init(CardSprite *_selectedCard)
{
    if(!UIState::init()){
        return false;
    }
    _selectedCard->setScale(.35);
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCLog("ResearchTypeTargetState");
    this->selectedCard = _selectedCard;
    selectedCard->setZOrder(10000);
    //highlight should take care of buttons as well
    GM->gameLayer->setButtonLabels("", "");
    selectedCard->cardTargets->highlightInteractiveObjects(this);
    return true;
}

#pragma mark - touch events
bool ResearchTypeTargetState::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    CCLog("selectedState");
    return true;
}

void ResearchTypeTargetState::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    //get touch location
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    this->selectedCard->setPosition(touchPoint);
    //figure out what quadrant card is in
    selectedCard->cardTargets->highlightOnMove(this, selectedCard);
}

void ResearchTypeTargetState::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    //get touch location
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    
    
    this->selectedCard->setPosition(touchPoint);
    //if can play card
    
    if(GM->player->canPlayCard(selectedCard)){
        
        CardTargets *target = this->selectedCard->cardTargets;
        
        //check if there are targets that the card can use
        if(target->isAbilityActivatable(this)){
            //check if the card was played in the correct spot
            if(target->targetObjectWithHandCard(touch, this, this->selectedCard)){
                //play card if all targets are acquired
                if(target->isAbilityReady()){
                    target->useInitialAbility();
                    GM->player->playCard(selectedCard);
                    target->useAbility();
                    selectedCard = NULL;
                    this->transitionToNormalState();
                }else{
                    //ability is not ready to be used, change to state that allows targets to be gotten
                    target->useInitialAbility();
                    GM->player->playCard(selectedCard);
                    target->changeState(this, this->selectedCard);
                }
            }else{
                selectedCard = NULL;
                this->transitionToNormalState();
            }
        }else{
            selectedCard = NULL;
            this->transitionToNormalState();
        }
    }
    
    GM->player->organizeHand();
}

void ResearchTypeTargetState::ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
    this->transitionToNormalState();
    GM->player->organizeHand();
}

#pragma mark - state transitions

void ResearchTypeTargetState::transitionToNormalState(){
    NormalState *NS =  new NormalState();
    NS->init();
    NS->autorelease();
    GM->gameLayer->changeState(NS);
    GM->player->finishedPlayingCard();
    GM->player->organizeHand();
    //    GM->organizeMarket();
    GM->gameLayer->updateInterface();
}


