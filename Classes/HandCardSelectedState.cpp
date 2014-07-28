//
//  HandCardSelectedState.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/18/13.
//
//

#include "HandCardSelectedState.h"
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
bool HandCardSelectedState::init(CardSprite *_selectedCard)
{
    if(!UIState::init()){
        return false;
    }
    _selectedCard->setScale(.35);
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCLog("handcardselectedState");
    this->selectedCard = _selectedCard;
    selectedCard->setZOrder(10000);
        //highlight should take care of buttons as well
    GM->gameLayer->setButtonLabels("", "");
    selectedCard->cardTargets->highlightInteractiveObjects(this);
    return true;
}


#pragma mark - touch events
bool HandCardSelectedState::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    return true;
}

void HandCardSelectedState::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    //get touch location
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    this->selectedCard->setPosition(touchPoint);
}

void HandCardSelectedState::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    //get touch location
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);

    
    this->selectedCard->setPosition(touchPoint);
    //if can play card
    
    if(selectedCard->isPassive){
        selectedCard = NULL;
        this->transitionToNormalState();
    }else if(GM->player->canPlayCard(selectedCard)){
        
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
    }else{
        selectedCard = NULL;
        this->transitionToNormalState();
    }
    
    GM->player->organizeHand();
}

void HandCardSelectedState::ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
    this->transitionToNormalState();
    GM->player->organizeHand();
}

#pragma mark - state transitions

void HandCardSelectedState::transitionToNormalState(){
    NormalState *NS =  new NormalState();
    NS->init();
    NS->autorelease();
    GM->gameLayer->changeState(NS);
    GM->player->finishedPlayingCard();
    GM->player->organizeHand();
    //    GM->organizeMarket();
    GM->gameLayer->updateInterface();
    
}

void HandCardSelectedState::transitionToHandCardSelectedState(CardSprite* selectedCard){
    CCLog("error:already in handCardSelectedState");
}

void HandCardSelectedState::transitionToCardTargetingState(CardSprite* selectedCard){
    CardTargetingState *CTS =  new CardTargetingState();
    CTS->init(selectedCard);
    CTS->autorelease();
    GM->gameLayer->changeState(CTS);
    //    GM->organizeMarket();
    GM->gameLayer->updateInterface();
}

void HandCardSelectedState::transitionToCardDraggingState(CardSprite* selectedCard){
    CardDraggingState *CDS =  new CardDraggingState();
    CDS->init(selectedCard);
    CDS->autorelease();
    GM->gameLayer->changeState(CDS);
    //    GM->organizeMarket();
    GM->gameLayer->updateInterface();
}
