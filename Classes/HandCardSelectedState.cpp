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
    GameManager *GM = GameManager::sharedGameManager();
    CCLog("handcardselectedState");
    this->selectedCard = _selectedCard;
    selectedCard->setZOrder(10000);
        //highlight should take care of buttons as well
    GM->gameLayer->setButtonLabels("", "");
    return true;
}


void HandCardSelectedState::highlightInteractiveObjects(CardSprite *card){
    clearInteractiveState();
   /* GameManager *GM = GameManager::sharedGameManager();
    CCObject *object;
    TargetingType indicatorState = card->cardTargets->targetingType;
    //    GM->gameLayer->changeIndicatorState(card->cardTargets->targetingType);
    
    if(card->turnsLeftInMarket > 0){
        //if it's a market card lead the user to the discard pile
        GM->gameLayer->handLayer->enableDiscardInteractive();
        GM->gameLayer->changeIndicatorState("Drag to Discard to Buy Card");
        return;
    }else{
        GM->gameLayer->marketLayer->enableSellInteractive();
    }
    if(indicatorState == None){
        
    }else if(indicatorState == PlayArea){
        GM->gameLayer->enablePlayAreaInteractive();
    }else if(indicatorState == DiscardArea){
        GM->gameLayer->handLayer->enableDiscardInteractive();
    }else if(indicatorState == RequireActions){
        //      visualIndicatorLabel->setString("More Actions Required");
    }else if(indicatorState == DiscardCard){
        //    visualIndicatorLabel->setString("Must Discard a Card");
    }else if(indicatorState == DrawCard){
        GM->gameLayer->handLayer->enableDeckInteractive();
    }else if(indicatorState == DrawCard_DiscardCard){
        GM->gameLayer->enablePlayAreaInteractive();
    }else if(indicatorState == PlayArea_TargetMonsters){
        GM->gameLayer->enablePlayAreaInteractive();
    }*/
    
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
    GameManager *GM = GameManager::sharedGameManager();
    GM->player->organizeHand();
}

#pragma mark - state transitions

void HandCardSelectedState::transitionToNormalState(){
    GameManager *GM = GameManager::sharedGameManager();
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
    GameManager *GM = GameManager::sharedGameManager();
    CardTargetingState *CTS =  new CardTargetingState();
    CTS->init(selectedCard);
    CTS->autorelease();
    GM->gameLayer->changeState(CTS);
    //    GM->organizeMarket();
    GM->gameLayer->updateInterface();
}

void HandCardSelectedState::transitionToCardDraggingState(CardSprite* selectedCard){
    GameManager *GM = GameManager::sharedGameManager();
    CardDraggingState *CDS =  new CardDraggingState();
    CDS->init(selectedCard);
    CDS->autorelease();
    GM->gameLayer->changeState(CDS);
    //    GM->organizeMarket();
    GM->gameLayer->updateInterface();
}
