//
//  OffsetMonsterLocation.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 2/21/14.
//
//

#include "OffsetMonsterLocationStatus.h"

#include "GainSoulStatus.h"
#include "MonsterSprite.h"
#include "GameManager.h"
#include "Player.h"
#include "Constants.h"


USING_NS_CC;


// on "init" you need to initialize your instance
bool OffsetMonsterLocationStatus::init(int powerLevel)
{
    if(!Status::init()){
        return false;
    }
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    className = new CCString();
    className->initWithFormat("OffsetMonsterLocationStatus");
    return true;
}

bool OffsetMonsterLocationStatus::initWithLocationOffset(int p_LocationOffset){
    if(!Status::init()){
        return false;
    }
    
    locationOffset = p_LocationOffset;
    return true;
}

void OffsetMonsterLocationStatus::addStatusToGameObject(MonsterSprite *monster){
    //damage immediate, no need to add to monster
    monster->location += locationOffset;
}

//checks whether the status can be used
bool OffsetMonsterLocationStatus::checkStart(){
    return true;
}

//called when status is given to object
void OffsetMonsterLocationStatus::applyStatus(){
    
}

//called when the status ends
void OffsetMonsterLocationStatus::applyEndStatus(){
    
}

//checks whether the status should be destroyed
bool OffsetMonsterLocationStatus::checkEnd(){
    return true;
}

//called at end of turn
void OffsetMonsterLocationStatus::updateStatus(){
    
}
