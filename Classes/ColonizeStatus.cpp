//
//  ColonizeStatus.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 6/8/14.
//
//

#include "ColonizeStatus.h"
#include "GameManager.h"
#include "Player.h"
#include "SolarSystemObject.h"


USING_NS_CC;


// on "init" you need to initialize your instance
bool ColonizeStatus::init()
{
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    className = new CCString();
    className->initWithFormat("ColonizeStatus");
    return true;
}

void ColonizeStatus::addStatusToSolarSystem(SolarSystemObject *solarSystemObject){
    GameManager *GM = GameManager::sharedGameManager();
    GM->player->acquireSolarSystem(solarSystemObject);
    
    if(solarSystemObject->population <= 0){
        solarSystemObject->population = 1;
        solarSystemObject->populationFraction = 0;
    }
}

//checks whether the status can be used
bool ColonizeStatus::checkStart(){
    return true;
}

//called when status is given to object
void ColonizeStatus::applyStatus(){
//    GameManager::sharedGameManager()->player->changeMoney(moneyOffset);
}

//called when the status ends
void ColonizeStatus::applyEndStatus(){
    
}

//checks whether the status should be destroyed
bool ColonizeStatus::checkEnd(){
    return true;
}

//called at end of turn
void ColonizeStatus::updateStatus(){
    
}

void ColonizeStatus::updateStatus(Player *player)
{
    
}
