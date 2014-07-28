//
//  CardDraggingState.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 12/6/13.
//
//

#include "CardDraggingState.h"

#include "HandCardSelectedState.h"
#include "GameManager.h"
#include "NormalState.h"
#include "CardTargets.h"
#include "Constants.h"
#include "HandLayer.h"
#include "GameLayer.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool CardDraggingState::init(CardSprite *_selectedCard)
{
    if(!UIState::init()){
        return false;
    }

    CCLog("card draggin state");
    this->selectedCard = _selectedCard;
    GM->gameLayer->setButtonLabels("", "");
    UIState::clearInteractiveState();
    this->selectedCard->cardTargets->highlightInteractiveObjectsWithDraggingState(this);
    
    //TODO: Display library or dis card pile to help player drag card from, feature still needs to be implemented
    draggingCard = NULL;
    return true;
}

#pragma mark - touch events
bool CardDraggingState::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    
    CardSprite *object = selectedCard->cardTargets->targetObjectWithDraggingState(touch, this, selectedCard);
    if(object){
        //select that card
        draggingCard = object;
        this->clearInteractiveState();
        selectedCard->cardTargets->highlightInteractiveObjectsWithDraggingCard(this);
        return  true;
    }else{
        return false;
    }
    
    /*
    if(selectedCard->cardTargets->targetingType == DiscardCard || selectedCard->cardTargets->targetingType == DrawCard_DiscardCard){
        //can only select hand cards
        CardSprite *card = UIState::handCardAtPoint(touch);
        if(card){
            //select that card
            draggingCard = card;
            this->clearInteractiveState();
            GM->gameLayer->handLayer->enableDiscardInteractive();
        }else{
            return false;
        }
    }
     */
    return false;
}

void CardDraggingState::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    //get touch location
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    if(draggingCard){
        this->draggingCard->setPosition(touchPoint);
    }
}

void CardDraggingState::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    

    if(selectedCard->cardTargets->targetObjectWithDraggingCard(touch, this, draggingCard))
    {
        if(selectedCard->cardTargets->isAbilityReady()){
            selectedCard->cardTargets->useAbility();
            this->transitionToNormalState();
        }else{
            UIState::clearInteractiveState();
            this->selectedCard->cardTargets->highlightInteractiveObjectsWithDraggingState(this);
        }
    }else{
        UIState::clearInteractiveState();
        this->selectedCard->cardTargets->highlightInteractiveObjectsWithDraggingState(this);
    }
    
    
    GM->player->organizeHand();
    draggingCard = NULL;
}

void CardDraggingState::ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
    UIState::clearInteractiveState();
    this->selectedCard->cardTargets->highlightInteractiveObjectsWithDraggingState(this);
    GM->player->organizeHand();
    draggingCard = NULL;
}

#pragma mark - state transitions

void CardDraggingState::transitionToNormalState(){
    NormalState *NS =  new NormalState();
    NS->init();
    NS->autorelease();
    GM->player->finishedPlayingCard();
    GM->gameLayer->changeState(NS);
    GM->gameLayer->updateInterface();
}

void CardDraggingState::transitionToHandCardSelectedState(CardSprite* selectedCard){

}

void CardDraggingState::transitionToSelectMonsterState(CardSprite* selectedCard){
    
}


void CardDraggingState::transitionToCardTargetingState(CardSprite* selectedCard){
    
}


