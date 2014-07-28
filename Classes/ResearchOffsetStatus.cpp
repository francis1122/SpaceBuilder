//
//  ResearchOffsetStatus.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 6/29/14.
//
//

#include "ResearchOffsetStatus.h"
#include "GameManager.h"
#include "Player.h"
#include "SolarSystemObject.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool ResearchOffsetStatus::initWithResearchOffset(int _researchOffset, ResearchTypes _researchType)
{
    researchType = _researchType;
    researchOffset = _researchOffset;
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    className = new CCString();
    className->initWithFormat("ResearchOffsetStatus");
    return true;
}

void ResearchOffsetStatus::addStatusToPlayer(Player *player){
    player->changeResearch(researchOffset, researchType);
}

//checks whether the status can be used
bool ResearchOffsetStatus::checkStart(){
    return true;
}

//called when status is given to object
void ResearchOffsetStatus::applyStatus(){
//    GameManager::sharedGameManager()->player->changeMoney(moneyOffset);
}

//called when the status ends
void ResearchOffsetStatus::applyEndStatus(){
    
}

//checks whether the status should be destroyed
bool ResearchOffsetStatus::checkEnd(){
    return true;
}

//called at end of turn
void ResearchOffsetStatus::updateStatus(){
    
}

void ResearchOffsetStatus::updateStatus(Player *player)
{
//    player->changeMoney(moneyOffset);
}

void ResearchOffsetStatus::updateStatus(SolarSystemObject *solarSystem)
{
    solarSystem->owner->changeResearch(researchOffset, researchType);
}


