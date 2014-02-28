//
//  MonsterSelfDamage.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 2/25/14.
//
//

#include "MonsterSelfDamageStatus.h"
#include "GainSoulStatus.h"
#include "MonsterSprite.h"
#include "GameManager.h"
#include "Player.h"
#include "Constants.h"


USING_NS_CC;

bool MonsterSelfDamageStatus::init(){
    if(!Status::init()){
        return false;
    }
    
    return true;
}

void MonsterSelfDamageStatus::addStatusToGameObject(MonsterSprite *monster){
    //damage immediate, no need to add to monster
    int healthOffset = monsterHealthOffsetAmount;
    if(GM->player->playedCards->count() <= 0){
        //preemptive bounus
        healthOffset += preemptiveBonus;
    }
    
    monster->changeMonsterHealth(-monster->attack);
}

//checks whether the status can be used
bool MonsterSelfDamageStatus::checkStart(){
    return true;
}

//called when status is given to object
void MonsterSelfDamageStatus::applyStatus(){

}

//called when the status ends
void MonsterSelfDamageStatus::applyEndStatus(){
    
}

//checks whether the status should be destroyed
bool MonsterSelfDamageStatus::checkEnd(){
    return true;
}

//called at end of turn
void MonsterSelfDamageStatus::updateStatus(){
    
}
