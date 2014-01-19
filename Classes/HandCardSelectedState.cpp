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
#include "MonsterSprite.h"
#include "GameLayer.h"
#include "HandLayer.h"
#include "MarketLayer.h"


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
    selectedCard->setZOrder(10000);
    
    if(!GM->player->hasAction(selectedCard->action->actionType)){
        UIState::clearInteractiveState();
        GM->gameLayer->changeIndicatorState("Requires Actions");
    }else{
        if(selectedCard->turnsLeftInMarket > 0){
            //set state for market card
            GM->gameLayer->handLayer->enableDiscardInteractive();
            GM->gameLayer->changeIndicatorState("Drag to Discard to Buy Card");
        }else{
            UIState::clearInteractiveState();
            this->selectedCard->cardTargets->highlightInteractiveObjects(this);
        }
    }
    //highlight should take care of buttons as well
    GM->gameLayer->setButtonLabels("", "");
    return true;
}


void HandCardSelectedState::highlightInteractiveObjects(CardSprite *card){
    clearInteractiveState();
    GameManager *GM = GameManager::sharedGameManager();
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
        GM->gameLayer->enablePlayAreaInteractive();
    }else if(indicatorState == PlayArea_TargetMonsters){
        GM->gameLayer->enablePlayAreaInteractive();
    }else if(indicatorState == MonsterDefend){
        for(int i = 0; i < GM->monsterArray->count(); i++){
            MonsterSprite *monsterSprite = (MonsterSprite*)GM->monsterArray->objectAtIndex(i);
            if(monsterSprite->location <= 0){
                monsterSprite->enableInteractive();
            }
        }
    }
    
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
    
    
    if(GM->player->hasAction(selectedCard->action->actionType)){
        if(selectedCard->turnsLeftInMarket > 0){
            //used for market card play
            
            //check if area is the discard area
            if(UIState::cardInDiscardArea(this->selectedCard)){
                //add card to players hand
                GM->buyCardFromMarket(this->selectedCard);
                selectedCard = NULL;
                GM->organizeMarket();
                this->transitionToNormalState();
            }else{
                selectedCard = NULL;
                GM->organizeMarket();
                this->transitionToNormalState();
            }
        }else{
            //sell card
            if(UIState::cardInSellArea(this->selectedCard)){
                //sell card
/*                GM->sellCard(selectedCard);
                selectedCard = NULL;
                this->transitionToNormalState();*/
            }else{
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
        }
    }else{
        selectedCard = NULL;
        this->transitionToNormalState();
    }
    
    GM->player->organizeHand();
    GM->organizeMarket();
    
    /*
    //check if actions are available for card use
    if(GM->player->hasAction(selectedCard->action->actionType)){
        if(selectedCard->turnsLeftInMarket > 0){
            //used for market card play
            
            //check if area is the discard area
            if(UIState::cardInDiscardArea(this->selectedCard)){
                //add card to players hand
                GM->buyCardFromMarket(this->selectedCard);
                selectedCard = NULL;
                GM->organizeMarket();
                this->transitionToNormalState();
            }else{
                selectedCard = NULL;
                GM->organizeMarket();
                this->transitionToNormalState();
            }
        }else{
            if(UIState::cardInSellArea(this->selectedCard)){
                //sell card
                GM->sellCard(selectedCard);
                selectedCard = NULL;
                this->transitionToNormalState();
            }else if(selectedCard->cardTargets->targetingType == PlayArea){
                if(UIState::cardInPlayArea(this->selectedCard)){
                    if(selectedCard->cardTargets->isAbilityReady()){
                        GM->player->playCard(selectedCard);
                        selectedCard->cardTargets->useAbility();
                        GM->player->organizeHand();
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
                
            }else if(selectedCard->cardTargets->targetingType == Monsters){
                if(UIState::cardInPlayArea(this->selectedCard)){
                    //ability is not ready to be used
                    GM->player->playCard(selectedCard);
                    this->transitionToCardTargetingState(this->selectedCard);
                }else{
                    if(selectedCard->cardTargets->targetObject(touch)){
                        if(selectedCard->cardTargets->isAbilityReady()){
                            GM->player->playCard(selectedCard);
                            selectedCard->cardTargets->useAbility();
                            selectedCard = NULL;
                            this->transitionToNormalState();
                        }else{
                            //ability is not ready to be used
                            GM->player->playCard(selectedCard);
                            this->transitionToCardTargetingState(this->selectedCard);
                        }
                    }else{
                        selectedCard = NULL;
                        this->transitionToNormalState();
                    }
                }
            }else if(selectedCard->cardTargets->targetingType == DiscardCard ||
                     selectedCard->cardTargets->targetingType == DrawCard_DiscardCard){
                if(UIState::cardInPlayArea(this->selectedCard)){
                    if(selectedCard->cardTargets->isAbilityActivatable(this)){
                        GM->player->playCard(selectedCard);
                        this->transitionToCardDraggingState(this->selectedCard);
                    }else{
                        selectedCard = NULL;
                        this->transitionToNormalState();
                    }
                }else{
                    selectedCard = NULL;
                    this->transitionToNormalState();
                }
            }else if(selectedCard->cardTargets->targetingType == PlayArea_TargetMonsters){
                if(UIState::cardInPlayArea(this->selectedCard)){
                    if(selectedCard->cardTargets->isAbilityActivatable(this)){
                        GM->player->playCard(selectedCard);
                    }else{
                        selectedCard = NULL;
                        this->transitionToNormalState();
                    }
                }else{
                    selectedCard = NULL;
                    this->transitionToNormalState();
                }
                
            }else if(selectedCard->cardTargets->targetingType == MonsterDefend){
                if(UIState::cardInPlayArea(this->selectedCard)){
                    //ability is not ready to be used
                    GM->player->playCard(selectedCard);
                    this->transitionToCardTargetingState(this->selectedCard);
                }else{
                    if(selectedCard->cardTargets->targetObject(touch)){
                        if(selectedCard->cardTargets->isAbilityReady()){
                            GM->player->playCard(selectedCard);
                            selectedCard->cardTargets->useAbility();
                            selectedCard = NULL;
                            this->transitionToNormalState();
                        }else{
                            //ability is not ready to be used
                            GM->player->playCard(selectedCard);
                            this->transitionToCardTargetingState(this->selectedCard);
                        }
                    }else{
                        selectedCard = NULL;
                        this->transitionToNormalState();
                    }
                }

            }else{
                selectedCard = NULL;
                this->transitionToNormalState();
            }
        }
    }else{
        selectedCard = NULL;
        this->transitionToNormalState();
    }
    
    GM->player->organizeHand();
    GM->organizeMarket();
     
     */
    //
    //
    //
    //
    //
    
    //check if card was dropped in play area
    /*  if(UIState::cardInPlayArea(this->selectedCard)){
     //check if card needs to target other cards or can it be activated now
     if(selectedCard->cardTargets->isAbilityReady()){
     GM->player->playCard(selectedCard);
     selectedCard->cardTargets->useAbility();
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
     
     if(selectedCard->cardTargets->targetObject(touch)){
     
     if(selectedCard->cardTargets->isAbilityReady()){
     GM->player->playCard(selectedCard);
     selectedCard->cardTargets->useAbility();
     selectedCard = NULL;
     this->transitionToNormalState();
     }else{
     //ability is not ready to be used
     GM->player->playCard(selectedCard);
     this->transitionToCardTargetingState(this->selectedCard);
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
     }
     }else{
     //actions are required, back to normal state
     selectedCard = NULL;
     this->transitionToNormalState();
     }
     
     GM->player->organizeHand();
     GM->organizeMarket();
     */
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
