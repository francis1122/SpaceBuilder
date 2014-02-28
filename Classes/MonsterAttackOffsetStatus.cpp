//
//  MonsterAttackIncreaseStatus.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 2/25/14.
//
//

#include "MonsterAttackOffsetStatus.h"
#include "GainSoulStatus.h"
#include "MonsterSprite.h"
#include "GameManager.h"
#include "Player.h"
#include "Constants.h"


USING_NS_CC;

bool MonsterAttackOffsetStatus::initWithAttackOffset(int attackOffset){
    if(!Status::init()){
        return false;
    }
    
    monsterAttackOffsetAmount = attackOffset;
    return true;
}

void MonsterAttackOffsetStatus::addStatusToGameObject(MonsterSprite *monster){
    //damage immediate, no need to add to monster
    int attackOffset = monsterAttackOffsetAmount;
    if(GM->player->playedCards->count() <= 0){
        //preemptive bounus
        attackOffset += preemptiveBonus;
    }
    
    monster->changeMonsterAttack(attackOffset);
}

//checks whether the status can be used
bool MonsterAttackOffsetStatus::checkStart(){
    return true;
}

//called when status is given to object
void MonsterAttackOffsetStatus::applyStatus(){
    //    GameManager *GM = GameManager::sharedGameManager();
    //    GM->player->soul += soulGainAmount;
}

//called when the status ends
void MonsterAttackOffsetStatus::applyEndStatus(){
    
}

//checks whether the status should be destroyed
bool MonsterAttackOffsetStatus::checkEnd(){
    return true;
}

//called at end of turn
void MonsterAttackOffsetStatus::updateStatus(){
    
}