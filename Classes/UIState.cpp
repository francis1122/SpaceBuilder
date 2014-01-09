//
//  UIState.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/18/13.
//
//

#include "UIState.h"
#include "GameManager.h"
#include "GameLayer.h"
#include "CardSprite.h"
#include "CardTargets.h"
#include "MonsterSprite.h"
#include "HandLayer.h"
#include "MarketLayer.h"

USING_NS_CC;


// on "init" you need to initialize your instance
bool UIState::init()
{
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    return true;
}

#pragma mark - utility functions
CardSprite *UIState::handCardAtPoint(cocos2d::CCTouch*touch){
    GameManager *GM = GameManager::sharedGameManager();
    //get touch location
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    CCObject *object;
    CCARRAY_FOREACH(GM->player->handCards, object){
        CardSprite *card = (CardSprite*)object;
        CCRect collisionRect = CCRectMake(card->getPosition().x - card->getContentSize().width/2 * card->getScale(), card->getPosition().y - card->getContentSize().height/2 * card->getScale(), card->getContentSize().width * card->getScale(), card->getContentSize().height * card->getScale() );
        bool stuff = collisionRect.containsPoint(touchPoint);
        if(stuff){
            return card;
        }
    }
    return NULL;
}

CardSprite *UIState::marketCardAtPoint(cocos2d::CCTouch*touch){
    GameManager *GM = GameManager::sharedGameManager();
    //get touch location
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    CCObject *object;
    CCARRAY_FOREACH(GM->marketCardArray, object){
        CardSprite *card = (CardSprite*)object;
        CCRect collisionRect = CCRectMake(card->getPosition().x - card->getContentSize().width/2 * card->getScale(), card->getPosition().y - card->getContentSize().height/2 * card->getScale(), card->getContentSize().width * card->getScale(), card->getContentSize().height * card->getScale() );
        bool stuff = collisionRect.containsPoint(touchPoint);
        if(stuff){
            return card;
        }
    }
    return NULL;
}

MonsterSprite *UIState::monsterCardAtPoint(cocos2d::CCTouch*touch){
    GameManager *GM = GameManager::sharedGameManager();
    //get touch location
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    CCObject *object;
    CCARRAY_FOREACH(GM->monsterArray, object){
        MonsterSprite *monster = (MonsterSprite*)object;
        CCRect collisionRect = CCRectMake(monster->getPosition().x - monster->getContentSize().width/2 * monster->getScale(), monster->getPosition().y - monster->getContentSize().height/2 * monster->getScale(), monster->getContentSize().width  * monster->getScale(), monster->getContentSize().height * monster->getScale());
        bool stuff = collisionRect.containsPoint(touchPoint);
        if(stuff){
            return monster;
        }
    }
    return NULL;
}


CCObject* UIState::objectAtPoint(cocos2d::CCTouch* touch){
    GameManager *GM = GameManager::sharedGameManager();
    //get touch location
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    //cycle through possible things that can be touched in state
    CCObject *objectAtPoint = NULL;
    CCObject *object;
    CCARRAY_FOREACH(GM->player->handCards, object){
        CardSprite *card = (CardSprite*)object;
        CCRect collisionRect = CCRectMake(card->getPosition().x - card->getContentSize().width/2 * card->getScale(), card->getPosition().y - card->getContentSize().height/2 * card->getScale(), card->getContentSize().width * card->getScale(), card->getContentSize().height * card->getScale() );
        bool stuff = collisionRect.containsPoint(touchPoint);
        if(stuff){
            return object;
        }
    }
    
    CCARRAY_FOREACH(GM->marketCardArray, object){
        CardSprite *card = (CardSprite*)object;
        CCRect collisionRect = CCRectMake(card->getPosition().x - card->getContentSize().width/2  * card->getScale(), card->getPosition().y - card->getContentSize().height/2  * card->getScale(), card->getContentSize().width * card->getScale(), card->getContentSize().height * card->getScale() );
        bool stuff = collisionRect.containsPoint(touchPoint);
        if(stuff){
            return object;
        }
    }
    
    return objectAtPoint;
}

//visualize what can be touched
void UIState::clearInteractiveState(){
    GameManager *GM = GameManager::sharedGameManager();
    CCObject *object;
    GM->gameLayer->changeIndicatorState(None);
    CCARRAY_FOREACH(GM->player->handCards, object){
        CardSprite *card = (CardSprite*)object;
        card->disableInteractive();
    }
    
    CCARRAY_FOREACH(GM->marketCardArray, object){
        CardSprite *card = (CardSprite*)object;
        card->disableInteractive();
    }
    
    CCARRAY_FOREACH(GM->monsterArray, object){
        MonsterSprite *monster = (MonsterSprite*)object;
        monster->disableInteractive();
    }
    
    GM->gameLayer->setButtonLabels("", "");
    GM->gameLayer->handLayer->disableDeckInteractive();
    GM->gameLayer->handLayer->disableDiscardInterative();
    GM->gameLayer->disablePlayAreaInteractive();
    GM->gameLayer->marketLayer->disableSellInteractive();
    GM->gameLayer->disablePlayAreaInteractive();
    GM->gameLayer->disableLeftButtonInteractive();
    GM->gameLayer->disableRightButtonInteractive();
    
}


void UIState::highlightInteractiveObjects(CardSprite *card){
    clearInteractiveState();
    
}

void UIState::defaultInteractiveState(){
    //clear state
    clearInteractiveState();
    
    GameManager *GM = GameManager::sharedGameManager();
    CCObject *object;
    GM->gameLayer->changeIndicatorState(None);
    GM->gameLayer->enableRightButtonInteractive();
    GM->gameLayer->setButtonLabels("", "End Turn");
    //TODO: more exact action count required
    CCARRAY_FOREACH(GM->player->handCards, object){
        CardSprite *card = (CardSprite*)object;
        if(GM->player->hasAction(card->action->actionType)){
            card->enableInteractive();
        }
    }
    if(GM->player->hasAction(Neutral)){
        CCARRAY_FOREACH(GM->marketCardArray, object){
            CardSprite *card = (CardSprite*)object;
            if(card->soulCost <= GM->player->soul){
                card->enableInteractive();
            }else{
                card->disableInteractive();
            }
        }
    }
    
    CCARRAY_FOREACH(GM->monsterArray, object){
        MonsterSprite *monster = (MonsterSprite*)object;
        monster->disableInteractive();
    }
}


#pragma mark - touch events
bool UIState::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    return true;
}

void UIState::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    
}

void UIState::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    
}

void UIState::ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
    
}

void UIState::doubleTap(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
    CCLog("doubletap");
}


//button touches
void UIState::leftButtonTouch(){
    CCLog("UIState::leftButtonTouch");
}


void UIState::rightButtonTouch(){
    CCLog("UIState::rightButtonTouch");
}


#pragma mark -collision checks

bool UIState::cardInDiscardArea(CardSprite* card){
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCRect collisionRect = CCRectMake(950, 0, 200, 200);
    if(collisionRect.containsPoint(card->getPosition()) ){
        return true;
    }
    return false;
}

bool UIState::cardInPlayArea(CardSprite* card){
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCRect collisionRect = CCRectMake(0, 180, visibleSize.width, 160);
    if(collisionRect.containsPoint(card->getPosition()) ){
        return true;
    }
    return false;
}

bool UIState::cardInSellArea(CardSprite*card){
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCRect collisionRect = CCRectMake(visibleSize.width - 180, visibleSize.height -  180, 180, 180);
    if(collisionRect.containsPoint(card->getPosition()) ){
        return true;
    }
    return false;
}

MonsterSprite* UIState::doesCardTouchMonster(CardSprite* card){
    GameManager *GM = GameManager::sharedGameManager();
    CCObject *object;
    CCARRAY_FOREACH(GM->monsterArray, object){
        MonsterSprite *monster = (MonsterSprite*)object;
        CCRect collisionRect = CCRectMake(monster->getPosition().x - monster->getContentSize().width/2, monster->getPosition().y - monster->getContentSize().height/2, monster->getContentSize().width, monster->getContentSize().height);
        if(collisionRect.containsPoint(card->getPosition()) ){
            CCLog("monster has been hit");
            return monster;
        }
    }
    
    return NULL;
}

MonsterSprite* UIState::doesPointTouchMonster(CCTouch *touch){
    GameManager *GM = GameManager::sharedGameManager();
    CCObject *object;
    //get touch location
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    
    CCARRAY_FOREACH(GM->monsterArray, object){
        MonsterSprite *monster = (MonsterSprite*)object;
        CCRect collisionRect = CCRectMake(monster->getPosition().x - monster->getContentSize().width/2, monster->getPosition().y - monster->getContentSize().height/2, monster->getContentSize().width, monster->getContentSize().height);
        if(collisionRect.containsPoint(touchPoint) ){
            CCLog("monster has been hit");
            return monster;
        }
    }
    
    return NULL;
}


#pragma mark -state transitions

void UIState::transitionToNormalState(){
    
}

void UIState::transitionToHandCardSelectedState(CardSprite* selectedCard){
    
}

void UIState::transitionToSelectMonsterState(CardSprite* selectedCard){
    
}

void UIState::transitionToCardTargetingState(CardSprite* selectedCard){
    
}

void UIState::transitionToCardDraggingState(CardSprite* selectedCard){
    CCLog("empty transitionToCardDraggingState");
}

//type 0 = hand card, 1 = monster card, 2 = market card
void UIState::transitionToZoomState(CCObject *selectedObject, int type){
    
}



