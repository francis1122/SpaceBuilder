//
//  Status.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/21/13.
//
//

#include "Status.h"


USING_NS_CC;


// on "init" you need to initialize your instance
bool Status::init()
{
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    className = new CCString();
    className->initWithFormat("Status");
    return true;
}

void Status::addStatusToPlayer(Player *player){
    this->applyStatus();
}

void Status::addStatusToCardSprite(CardSprite *card){
    this->applyStatus();
}

void Status::addStatusToSolarSystem(SolarSystemObject *solarSystemObject)
{
    this->applyStatus();    
}

//checks whether the status can be used
bool Status::checkStart()
{
    return true;
}

//called when status is given to object
void Status::applyStatus()
{
    
}

void Status::applyStatus(SolarSystemObject *solarSystem)
{
    
}


//called when the status ends
void Status::applyEndStatus(){
    
}

void Status::applyEndStatus(SolarSystemObject *solarSystem)
{
    
}

//checks whether the status should be destroyed
bool Status::checkEnd(){
    return true;
}

//called at end of turn
void Status::updateStatus(){
    
}

//called at end of turn
void Status::updateStatus(MonsterSprite *monster){
    
}

void Status::updateStatus(SolarSystemObject *solarSystem)
{
    
}

void Status::updateStatus(Player *player)
{
    
}

