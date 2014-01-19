//
//  InstantKillMonsterStatus.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/18/14.
//
//

#include "InstantKillMonsterStatus.h"
#include "GainSoulStatus.h"
#include "MonsterSprite.h"
#include "GameManager.h"
#include "Player.h"


USING_NS_CC;


// on "init" you need to initialize your instance
bool InstantKillMonsterStatus::init()
{
    if(!Status::init()){
        return false;
    }
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    className = new CCString();
    className->initWithFormat("InstantKillMonsterStatus");
    return true;
}


void InstantKillMonsterStatus::addStatusToGameObject(MonsterSprite *monster){
    //damage immediate, no need to add to monster
    monster->isDead = true;
}

//checks whether the status can be used
bool InstantKillMonsterStatus::checkStart(){
    return true;
}

//called when status is given to object
void InstantKillMonsterStatus::applyStatus(){
    //    GameManager *GM = GameManager::sharedGameManager();
    //    GM->player->soul += soulGainAmount;
}

//called when the status ends
void InstantKillMonsterStatus::applyEndStatus(){
    
}

//checks whether the status should be destroyed
bool InstantKillMonsterStatus::checkEnd(){
    return true;
}

//called at end of turn
void InstantKillMonsterStatus::updateStatus(){
    
}