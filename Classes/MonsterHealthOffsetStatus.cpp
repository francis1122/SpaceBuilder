//
//  MonsterHealthOffsetStatus.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/21/13.
//
//

#include "MonsterHealthOffsetStatus.h"

#include "GainSoulStatus.h"
#include "MonsterSprite.h"
#include "GameManager.h"
#include "Player.h"


USING_NS_CC;


// on "init" you need to initialize your instance
bool MonsterHealthOffsetStatus::init(int powerLevel)
{
    
    if(!Status::init()){
        return false;
    }
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    className = new CCString();
    className->initWithFormat("MonsterHealthOffsetStatus");
    monsterHealthOffsetAmount = -powerLevel;
    return true;
}


void MonsterHealthOffsetStatus::addStatusToGameObject(MonsterSprite *monster){
    //damage immediate, no need to add to monster
    monster->life += monsterHealthOffsetAmount;
}

//checks whether the status can be used
bool MonsterHealthOffsetStatus::checkStart(){
    return true;
}

//called when status is given to object
void MonsterHealthOffsetStatus::applyStatus(){
//    GameManager *GM = GameManager::sharedGameManager();
//    GM->player->soul += soulGainAmount;
}

//called when the status ends
void MonsterHealthOffsetStatus::applyEndStatus(){
    
}

//checks whether the status should be destroyed
bool MonsterHealthOffsetStatus::checkEnd(){
    return true;
}

//called at end of turn
void MonsterHealthOffsetStatus::updateStatus(){
    
}
