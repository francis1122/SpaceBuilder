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

USING_NS_CC;

// on "init" you need to initialize your instance
bool CardDraggingState::init(CardSprite *_selectedCard)
{
    if(!UIState::init()){
        return false;
    }
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCLog("card draggin state");
    this->selectedCard = _selectedCard;
    GameManager *GM = GameManager::sharedGameManager();
    GM->gameLayer->changeIndicatorState(selectedCard->cardTargets->targetingType);
    GM->gameLayer->setButtonLabels("", "");
    
    //TODO: Display library or dis card pile to help player drag card from, feature still needs to be implemented
    draggingCard = NULL;
    return true;
}

#pragma mark - touch events
bool CardDraggingState::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    
    if(selectedCard->cardTargets->targetingType == DiscardCard){
        //can only select hand cards
        CardSprite *card = UIState::handCardAtPoint(touch);
        if(card){
            //select that card
            draggingCard = card;
        }else{
            return false;
        }
    }
    
    //tap a monster
    return true;
}

void CardDraggingState::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    GameManager *GM = GameManager::sharedGameManager();
    //get touch location
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    if(draggingCard){
        this->draggingCard->setPosition(touchPoint);
    }
}

void CardDraggingState::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    GameManager *GM = GameManager::sharedGameManager();
    
    if(selectedCard->cardTargets->targetingType == DiscardCard){
        //can only land in discard Area
        if(UIState::cardInDiscardArea(draggingCard)){
            selectedCard->cardTargets->selectedTargets->addObject(draggingCard);
            GM->player->discardCard(draggingCard);
            //check if card is ready to be played
            if(selectedCard->cardTargets->isAbilityReady()){
                selectedCard->cardTargets->useAbility();
                this->transitionToNormalState();
            }
        }
    }

    GM->player->organizeHand();
    draggingCard = NULL;
    
}

void CardDraggingState::ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
    this->transitionToNormalState();
    GameManager *GM = GameManager::sharedGameManager();
    GM->player->organizeHand();
}

#pragma mark - state transitions

void CardDraggingState::transitionToNormalState(){
    GameManager *GM = GameManager::sharedGameManager();
    NormalState *NS =  new NormalState();
    NS->init();
    NS->autorelease();
    GM->gameLayer->changeState(NS);
    GM->gameLayer->updateInterface();
}

void CardDraggingState::transitionToHandCardSelectedState(CardSprite* selectedCard){

}

void CardDraggingState::transitionToSelectMonsterState(CardSprite* selectedCard){
    
}


void CardDraggingState::transitionToCardTargetingState(CardSprite* selectedCard){
    
}