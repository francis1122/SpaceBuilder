//
//  LeechMonsterLifeStatus.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 2/25/14.
//
//

#include "LeechMonsterLifeStatus.h"
#include "GainSoulStatus.h"
#include "MonsterSprite.h"
#include "GameManager.h"
#include "Player.h"
#include "Constants.h"


USING_NS_CC;


// on "init" you need to initialize your instance
bool LeechMonsterLifeStatus::init(int powerLevel)
{
    if(!Status::init()){
        return false;
    }
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    className = new CCString();
    className->initWithFormat("LeechMonsterLifeStatus");
    monsterHealthOffsetAmount = -powerLevel;
    return true;
}

bool LeechMonsterLifeStatus::initWithHealthOffset(int healthOffset){
    if(!Status::init()){
        return false;
    }
    
    monsterHealthOffsetAmount = healthOffset;
    return true;
}

void LeechMonsterLifeStatus::addStatusToGameObject(MonsterSprite *monster){
    //damage immediate, no need to add to monster
    int healthOffset = monsterHealthOffsetAmount;
    if(GM->player->playedCards->count() <= 0){
        //preemptive bounus
        healthOffset += preemptiveBonus;
    }

    int lifeGain = MIN(-healthOffset, monster->life);
    GM->player->changeHealth(lifeGain);
    monster->changeMonsterHealth(healthOffset);

}

//checks whether the status can be used
bool LeechMonsterLifeStatus::checkStart(){
    return true;
}

//called when status is given to object
void LeechMonsterLifeStatus::applyStatus(){
    //    GameManager *GM = GameManager::sharedGameManager();
    //    GM->player->soul += soulGainAmount;
}

//called when the status ends
void LeechMonsterLifeStatus::applyEndStatus(){
    
}

//checks whether the status should be destroyed
bool LeechMonsterLifeStatus::checkEnd(){
    return true;
}

//called at end of turn
void LeechMonsterLifeStatus::updateStatus(){
    
}