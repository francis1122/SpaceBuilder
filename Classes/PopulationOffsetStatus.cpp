//
//  PopulationOffsetStatus.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 6/9/14.
//
//

#include "PopulationOffsetStatus.h"
#include "GameManager.h"
#include "Player.h"
#include "SolarSystemObject.h"


USING_NS_CC;


// on "init" you need to initialize your instance
bool PopulationOffsetStatus::initWithPopulationOffset(int _populationOffset, int _populationFractionOffset)
{
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    className = new CCString();
    className->initWithFormat("PopulationOffsetStatus");
    populationOffset = _populationOffset;
    populationFractionOffset = _populationFractionOffset;
    return true;
}

void PopulationOffsetStatus::addStatusToSolarSystem(SolarSystemObject *solarSystemObject){
   // GameManager *GM = GameManager::sharedGameManager();
    solarSystemObject->populationOffset(populationOffset, populationFractionOffset);
    solarSystemObject->updateInterface();
//    solarSystemObject->change
}

//checks whether the status can be used
bool PopulationOffsetStatus::checkStart(){
    return true;
}

//called when status is given to object
void PopulationOffsetStatus::applyStatus(){
    //    GameManager::sharedGameManager()->player->changeMoney(moneyOffset);
}

void PopulationOffsetStatus::applyStatus(SolarSystemObject *solarSystem)
{
    solarSystem->populationGrowth += populationFractionOffset;
}


//called when the status ends
void PopulationOffsetStatus::applyEndStatus()
{
    
}

void PopulationOffsetStatus::applyEndStatus(SolarSystemObject *solarSystem)
{
    solarSystem->populationGrowth -= populationFractionOffset;
}

//checks whether the status should be destroyed
bool PopulationOffsetStatus::checkEnd(){
    return true;
}

//called at end of turn
void PopulationOffsetStatus::updateStatus(){
    
}

void PopulationOffsetStatus::updateStatus(Player *player)
{
    
}

void PopulationOffsetStatus::updateStatus(SolarSystemObject *solarSystem)
{
    
}


