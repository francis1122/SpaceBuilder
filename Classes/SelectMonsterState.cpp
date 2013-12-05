//
//  SelectMonsterState.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/21/13.
//
//

#include "SelectMonsterState.h"


#include "HandCardSelectedState.h"
#include "GameManager.h"
#include "NormalState.h"
#include "MonsterSprite.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool SelectMonsterState::init(CardSprite *_selectedCard)
{
    if(!UIState::init()){
        return false;
    }
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCLog("selectmonsterstate");
    this->selectedCard = _selectedCard;
    
    return true;
}

#pragma mark - touch events
bool SelectMonsterState::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    CCLog("selected monster");
    //tap a monster
    return true;
}

void SelectMonsterState::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
//    GameManager *GM = GameManager::sharedGameManager();
    //get touch location
 //   CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
}

void SelectMonsterState::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    GameManager *GM = GameManager::sharedGameManager();
    //get touch location
   // CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    //    this->selectedCard->setPosition(CCPointMake(touchPoint.x - this->selectedCard->getContentSize().width/2,touchPoint.y  - this->selectedCard->getContentSize().height/2));
    
    //if on a monster, play a card
    //    if(this-)
    //check for card in play area

        MonsterSprite *selectedMonster = UIState::doesPointTouchMonster(touch);
        if(selectedMonster){
            selectedMonster->location++;
            selectedCard = NULL;
            this->transitionToNormalState();
            GM->player->organizeHand();
        }
}

void SelectMonsterState::ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
    this->transitionToNormalState();
    GameManager *GM = GameManager::sharedGameManager();
    GM->player->organizeHand();
}

#pragma mark - state transitions

void SelectMonsterState::transitionToNormalState(){
    GameManager *GM = GameManager::sharedGameManager();
    NormalState *NS =  new NormalState();
    NS->init();
    NS->autorelease();
    GM->gameLayer->changeState(NS);
    GM->gameLayer->updateInterface();
}

void SelectMonsterState::transitionToHandCardSelectedState(CardSprite* selectedCard){
    CCLog("error:already in handCardSelectedState");
}

void SelectMonsterState::transitionToSelectMonsterState(CardSprite* selectedCard){
    
}

void SelectMonsterState::transitionToCardTargetingState(CardSprite* selectedCard){

}