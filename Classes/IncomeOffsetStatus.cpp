//
//  IncomeOffsetStatus.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 6/17/14.
//
//

#include "IncomeOffsetStatus.h"
#include "GameManager.h"
#include "Player.h"
#include "SolarSystemObject.h"


USING_NS_CC;


// on "init" you need to initialize your instance
bool IncomeOffsetStatus::initWithIncomeOffset(int _incomeOffset)
{
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    className = new CCString();
    className->initWithFormat("IncomeOffsetStatus");
    incomeOffset = _incomeOffset;
    return true;
}

void IncomeOffsetStatus::addStatusToSolarSystem(SolarSystemObject *solarSystemObject){
      //GameManager *GM = GameManager::sharedGameManager();
//    solarSystemObject->incomeGeneration += incomeOffset;
    solarSystemObject->updateInterface();
//    solarSystemObject->income
  //  solarSystemObject->populationOffset(populationOffset, populationFractionOffset);
//    solarSystemObject->updateInterface();
    //    solarSystemObject->change
}

//checks whether the status can be used
bool IncomeOffsetStatus::checkStart(){
    return true;
}

//called when status is given to object
void IncomeOffsetStatus::applyStatus(){
    //    GameManager::sharedGameManager()->player->changeMoney(moneyOffset);
}

//called when the status ends
void IncomeOffsetStatus::applyEndStatus(){
    
}

//checks whether the status should be destroyed
bool IncomeOffsetStatus::checkEnd(){
    return true;
}

//called at end of turn
void IncomeOffsetStatus::updateStatus(){
    
}

void IncomeOffsetStatus::updateStatus(Player *player)
{
    
}