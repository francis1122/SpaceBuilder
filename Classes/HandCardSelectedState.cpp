//
//  HandCardSelectedState.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/18/13.
//
//

#include "HandCardSelectedState.h"
#include "SelectMonsterState.h"
#include "CardTargetingState.h"
#include "CardDraggingState.h"
#include "GameManager.h"
#include "NormalState.h"
#include "CardTargets.h"
#include "CardSprite.h"
#include "MonsterSprite.h"


USING_NS_CC;

// on "init" you need to initialize your instance
bool HandCardSelectedState::init(CardSprite *_selectedCard)
{
    if(!UIState::init()){
        return false;
    }
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    GameManager *GM = GameManager::sharedGameManager();
    CCLog("handcardselectedState");
    this->selectedCard = _selectedCard;
    if(selectedCard->turnsLeftInMarket > 0){
        GM->gameLayer->changeIndicatorState(DiscardArea);
    }else if(GM->player->actionsLeft <= 0){
        GM->gameLayer->changeIndicatorState(RequireActions);
    }else{
        GM->gameLayer->changeIndicatorState(selectedCard->cardTargets->targetingType);
    }
        GM->gameLayer->setButtonLabels("", "");
    return true;
}

#pragma mark - touch events
bool HandCardSelectedState::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    CCLog("selectedState");
    return true;
}

void HandCardSelectedState::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    GameManager *GM = GameManager::sharedGameManager();
    //get touch location
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    this->selectedCard->setPosition(touchPoint);
}

void HandCardSelectedState::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    GameManager *GM = GameManager::sharedGameManager();
    //get touch location
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    this->selectedCard->setPosition(touchPoint);
    
    if(GM->player->actionsLeft > 0){
        if(selectedCard->turnsLeftInMarket > 0){
            //used for market card play
            
            //check if area is the discard area
            if(UIState::cardInDiscardArea(this->selectedCard)){
                //add card to players hand
                GM->buyCardFromMarket(this->selectedCard);
                selectedCard = NULL;
                this->transitionToNormalState();
            }else{
                selectedCard = NULL;
                this->transitionToNormalState();
            }
        }else{
            //check if card was dropped in play area
            if(UIState::cardInPlayArea(this->selectedCard)){
                //check if card needs to target other cards or can it be activated now
                if(selectedCard->cardTargets->isAbilityReady()){
                    selectedCard->cardTargets->useAbility();
                    GM->player->playCard(selectedCard);
                    GM->player->organizeHand();
                    selectedCard = NULL;
                    this->transitionToNormalState();
                }else{
                    if(selectedCard->cardTargets->isDraggingRequired){
                        //ability is not ready to be used
                        GM->player->playCard(selectedCard);
                        this->transitionToCardDraggingState(this->selectedCard);
                    }else{
                        //ability is not ready to be used
                        GM->player->playCard(selectedCard);
                        this->transitionToCardTargetingState(this->selectedCard);
                    }
                }
                
            }else if(UIState::cardInSellArea(this->selectedCard)){
                //sell card
                GM->sellCard(selectedCard);
                selectedCard = NULL;
                this->transitionToNormalState();
            }else{
                //if card is dropped randomly on board
                if(selectedCard->cardTargets->isTargetRequired){
                    selectedCard->cardTargets->targetObject(touch);
                    
                    //TODO: needs to be more robust and able to target multiple enemies
                    // if one valid target has been chosen, go into cardtargetingstate
                    if(selectedCard->cardTargets->isAbilityReady()){
                        selectedCard->cardTargets->useAbility();
                        GM->player->playCard(selectedCard);
                        selectedCard = NULL;
                        this->transitionToNormalState();
                    }else{
                        selectedCard = NULL;
                        this->transitionToNormalState();
                    }
                }else{
                    selectedCard = NULL;
                    this->transitionToNormalState();
                }
            }
        }
    }else{
        //actions are required, back to normal state
        selectedCard = NULL;
        this->transitionToNormalState();
    }
    
    GM->player->organizeHand();
    GM->organizeMarket();
}

void HandCardSelectedState::ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
    this->transitionToNormalState();
    GameManager *GM = GameManager::sharedGameManager();
    GM->player->organizeHand();
    GM->organizeMarket();
}

#pragma mark - state transitions

void HandCardSelectedState::transitionToNormalState(){
    GameManager *GM = GameManager::sharedGameManager();
    NormalState *NS =  new NormalState();
    NS->init();
    NS->autorelease();
    GM->gameLayer->changeState(NS);
    GM->player->organizeHand();
    GM->organizeMarket();
    GM->gameLayer->updateInterface();
}

void HandCardSelectedState::transitionToHandCardSelectedState(CardSprite* selectedCard){
    CCLog("error:already in handCardSelectedState");
}

void HandCardSelectedState::transitionToSelectMonsterState(CardSprite* selectedCard){
    GameManager *GM = GameManager::sharedGameManager();
    SelectMonsterState *SMS =  new SelectMonsterState();
    SMS->init(selectedCard);
    SMS->autorelease();
    GM->gameLayer->changeState(SMS);
    GM->organizeMarket();
}

void HandCardSelectedState::transitionToCardTargetingState(CardSprite* selectedCard){
    GameManager *GM = GameManager::sharedGameManager();
    CardTargetingState *CTS =  new CardTargetingState();
    CTS->init(selectedCard);
    CTS->autorelease();
    GM->gameLayer->changeState(CTS);
    GM->organizeMarket();
    GM->gameLayer->updateInterface();
}

void HandCardSelectedState::transitionToCardDraggingState(CardSprite* selectedCard){
    GameManager *GM = GameManager::sharedGameManager();
    CardDraggingState *CDS =  new CardDraggingState();
    CDS->init(selectedCard);
    CDS->autorelease();
    GM->gameLayer->changeState(CDS);
    GM->organizeMarket();
    GM->gameLayer->updateInterface();
}
