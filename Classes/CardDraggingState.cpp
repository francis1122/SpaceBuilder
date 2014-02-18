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
#include "MonsterSprite.h"
#include "CardTargets.h"
#include "Constants.h"
#include "HandLayer.h"
#include "GameLayer.h"
#include "MarketLayer.h"

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

void CardDraggingState::highlightInteractiveObjects(CardSprite *card){
    clearInteractiveState();
    CCObject *object;
    TargetingType indicatorState = card->cardTargets->targetingType;
   // GM->gameLayer->changeIndicatorState(card->cardTargets->targetingType);
    
    if(card->turnsLeftInMarket > 0){
        //if it's a market card lead the user to the discard pile
        GM->gameLayer->handLayer->enableDiscardInteractive();
        return;
    }else{
        GM->gameLayer->marketLayer->enableSellInteractive();
    }
    if(indicatorState == None){
        
    }else if(indicatorState == PlayArea){
        GM->gameLayer->enablePlayAreaInteractive();
    }else if (indicatorState == Monsters){
        GM->gameLayer->enablePlayAreaInteractive();
        CCARRAY_FOREACH(GM->monsterArray, object){
            MonsterSprite *monster = (MonsterSprite*)object;
            monster->enableInteractive();
        }
    }else if(indicatorState == DiscardArea){
        GM->gameLayer->handLayer->enableDiscardInteractive();
    }else if(indicatorState == RequireActions){
        //      visualIndicatorLabel->setString("More Actions Required");
    }else if(indicatorState == DiscardCard){
        //    visualIndicatorLabel->setString("Must Discard a Card");
    }else if(indicatorState == DrawCard){
        GM->gameLayer->handLayer->enableDeckInteractive();
    }else if(indicatorState == DrawCard_DiscardCard){
        CCARRAY_FOREACH(GM->player->handCards, object){
            CardSprite *card = (CardSprite*)object;
            card->enableInteractive();
        }
    }
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


