//
//  ResearchSelectState.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 6/28/14.
//
//

#include "ResearchSelectState.h"
#include "ResearchState.h"
#include "GameManager.h"
#include "HandCardSelectedState.h"
#include "ZoomState.h"
#include "GameLayer.h"
#include "CardSprite.h"
#include "SolarSystemObject.h"
#include "SolarSystemDetailsLayer.h"
#include "SolarSystemDetailsState.h"
#include "ResearchLayer.h"
#include "NormalState.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool ResearchSelectState::init(CardSprite *_selectedCard)
{
    if(!UIState::init()){
        return false;
    }
    _selectedCard->setScale(.35);
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCLog("RESEARCHselectedState");
    this->selectedCard = _selectedCard;
    selectedCard->setZOrder(10000);
    //highlight should take care of buttons as well
    GM->gameLayer->setButtonLabels("", "");
    return true;
}


CardSprite *ResearchSelectState::researchCardAtPoint(cocos2d::CCTouch *touch){
    
    //get touch location
    CCPoint touchPoint = GM->gameLayer->researchLayer->cardMenu->convertTouchToNodeSpace(touch);
    //    CCLog("solarTouch: %f, %f", touchPoint.x, touchPoint.y);
    CCObject *object;
    int i = 0;
    CCARRAY_FOREACH(GM->gameLayer->researchLayer->cardSpriteArray, object){
        CardSprite *researchCard = (CardSprite*)object;
        CCRect collisionRect = CCRectMake(researchCard->getPosition().x - researchCard->getContentSize().width/2 * researchCard->getScale(), researchCard->getPosition().y - researchCard->getContentSize().height/2 * researchCard->getScale(), researchCard->getContentSize().width * researchCard->getScale(), researchCard->getContentSize().height * researchCard->getScale() );
        bool isHit = collisionRect.containsPoint(touchPoint);
        if(isHit){
            return (CardSprite*)GM->player->militaryTechCards->objectAtIndex(i);
        }
        i++;
    }
    return NULL;
}

#pragma mark - touch events
bool ResearchSelectState::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    UIState::ccTouchBegan(touch, event);
    return true;
}

void ResearchSelectState::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    
    //get touch location
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    this->selectedCard->setPosition(touchPoint);
}

void ResearchSelectState::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
    //    UIState::ccTouchEnded(touch, event);
    UIState::ccTouchEnded(touch, event);
    
    //get touch location
    CCPoint touchPoint = GM->gameLayer->convertTouchToNodeSpace(touch);
    
    this->selectedCard->setPosition(touchPoint);
    //if can play card
    
    //is selected Card on top of research Card
   /* CardSprite *researchCard = this->researchCardAtPoint(touch);
    if(researchCard){
        if(GM->player->canUpgradeCard(selectedCard, researchCard)){
            GM->player->upgradeCard(selectedCard, researchCard);
            GM->gameLayer->researchLayer->updateInterface();
            selectedCard = NULL;
        }
    }
    */
    
    GM->player->organizeHand();
    this->transitionToResearchState();
}

void ResearchSelectState::ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
    //    UIState::ccTouchCancelled(touch, event);
    UIState::ccTouchCancelled(touch, event);
    this->transitionToResearchState();
}

void ResearchSelectState::doubleTap(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
    //    CCLog("Normal doubletap");
}

//button touches
void ResearchSelectState::leftButtonTouch(){
    CCLog("UIState::leftButtonTouch");
}

void ResearchSelectState::rightButtonTouch(){
    //end turn
}

#pragma mark - state transitions
void ResearchSelectState::transitionToNormalState(){
    
    NormalState *NS =  new NormalState();
    NS->init();
    NS->autorelease();
    GM->gameLayer->changeState(NS);
    GM->player->finishedPlayingCard();
    GM->player->organizeHand();
    //    GM->organizeMarket();
    GM->gameLayer->updateInterface();
}

void ResearchSelectState::transitionToResearchState()
{
    
    ResearchState *RS =  new ResearchState();
    RS->init();
    RS->autorelease();
    GM->gameLayer->changeState(RS);
    GM->player->organizeHand();
    //    GM->organizeMarket();
    GM->gameLayer->updateInterface();
}


void ResearchSelectState::transitionToSolarSystemDetailsState(SolarSystemObject *selectedSolarSystem)
{
    
    SolarSystemDetailsState *SSDS = new SolarSystemDetailsState();
    SSDS->init(selectedSolarSystem);
    SSDS->autorelease();
    GM->gameLayer->changeState(SSDS);
}


void ResearchSelectState::transitionToCardTargetingState(CardSprite* selectedCard)
{
    
}

//type 0 = hand card, 1 = monster card, 2 = market card
void ResearchSelectState::transitionToZoomState(CCObject *selectedObject, int type){
    //this function sucks balls, i hate the type stuff
    
    ZoomState *ZS = new ZoomState;
    if(type == 0){
        CardSprite *card = (CardSprite*)selectedObject;
        ZS->initCardSprite(card);
    }
    ZS->autorelease();
    GM->gameLayer->changeState(ZS);
}