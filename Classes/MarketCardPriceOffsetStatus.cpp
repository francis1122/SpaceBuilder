//
//  MarketCardPriceOffsetStatus.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 2/17/14.
//
//

#include "MarketCardPriceOffsetStatus.h"

#include "MonsterSprite.h"
#include "GameManager.h"
#include "Player.h"

USING_NS_CC;


// on "init" you need to initialize your instance
bool MarketCardPriceOffsetStatus::init()
{
    
    if(!Status::init()){
        return false;
    }
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    className = new CCString();
    className->initWithFormat("MarketCardPriceOffsetStatus");
    return true;
}



void MarketCardPriceOffsetStatus::addStatusToCardSprite(CardSprite *card){
    GameManager *GM = GameManager::sharedGameManager();
    int soul = card->soulCost + priceOffset;
    if(GM->player->playedCards->count() <= 0){
        //preemptive bounus
        soul += preemptiveBonus;
    }
    
    card->setSoulCostOfCard(soul);
}

//checks whether the status can be used
bool MarketCardPriceOffsetStatus::checkStart(){
    return true;
}

//called when status is given to object
void MarketCardPriceOffsetStatus::applyStatus(){
    
}

//called when the status ends
void MarketCardPriceOffsetStatus::applyEndStatus(){
    
}

//checks whether the status should be destroyed
bool MarketCardPriceOffsetStatus::checkEnd(){
    return true;
}

//called at end of turn
void MarketCardPriceOffsetStatus::updateStatus(){
    
}