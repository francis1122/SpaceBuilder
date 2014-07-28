//
//  ProductionOffsetStatus.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 7/23/14.
//
//

#include "ProductionOffsetStatus.h"
#include "GameManager.h"
#include "Player.h"
#include "SolarSystemObject.h"


USING_NS_CC;


// on "init" you need to initialize your instance
bool ProductionOffsetStatus::initWithProductionOffset(int _productionOffset)
{
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    className = new CCString();
    className->initWithFormat("ProductionOffsetStatus");
    productionOffset = _productionOffset;
    return true;
}

void ProductionOffsetStatus::addStatusToPlayer(Player *player){
    player->changeProduction(productionOffset);
}


//checks whether the status can be used
bool ProductionOffsetStatus::checkStart(){
    return true;
}

//called when status is given to object
void ProductionOffsetStatus::applyStatus(){
    //    GameManager::sharedGameManager()->player->changeMoney(moneyOffset);
}

void ProductionOffsetStatus::applyStatus(SolarSystemObject *solarSystem)
{
//    solarSystem->populationGrowth += populationFractionOffset;
}


//called when the status ends
void ProductionOffsetStatus::applyEndStatus()
{
    
}

void ProductionOffsetStatus::applyEndStatus(SolarSystemObject *solarSystem)
{
//    solarSystem->populationGrowth -= populationFractionOffset;
}

//checks whether the status should be destroyed
bool ProductionOffsetStatus::checkEnd(){
    return true;
}

//called at end of turn
void ProductionOffsetStatus::updateStatus()
{
    
}

void ProductionOffsetStatus::updateStatus(Player *player)
{
    
}

void ProductionOffsetStatus::updateStatus(SolarSystemObject *solarSystem)
{
    solarSystem->owner->changeProduction(productionOffset);
}