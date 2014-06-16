//
//  MoneyOffsetStatus.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 6/8/14.
//
//

#include "MoneyOffsetStatus.h"
#include "GameManager.h"
#include "Player.h"


USING_NS_CC;


// on "init" you need to initialize your instance
bool MoneyOffsetStatus::initWithMoneyOffset(int _moneyOffset)
{
    moneyOffset = _moneyOffset;
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    className = new CCString();
    className->initWithFormat("MoneyOffsetStatus");
    return true;
}

void MoneyOffsetStatus::addStatusToPlayer(Player *player){
    player->changeMoney(moneyOffset);
}

//checks whether the status can be used
bool MoneyOffsetStatus::checkStart(){
    return true;
}

//called when status is given to object
void MoneyOffsetStatus::applyStatus(){
    GameManager::sharedGameManager()->player->changeMoney(moneyOffset);
}

//called when the status ends
void MoneyOffsetStatus::applyEndStatus(){
    
}

//checks whether the status should be destroyed
bool MoneyOffsetStatus::checkEnd(){
    return true;
}

//called at end of turn
void MoneyOffsetStatus::updateStatus(){
    
}

void MoneyOffsetStatus::updateStatus(Player *player)
{
    player->changeMoney(moneyOffset);
}

