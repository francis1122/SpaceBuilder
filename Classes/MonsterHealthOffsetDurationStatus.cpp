//
//  MonsterHealthOffsetDurationStatus.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/4/14.
//
//

#include "MonsterHealthOffsetDurationStatus.h"


#include "GainSoulStatus.h"
#include "MonsterSprite.h"
#include "GameManager.h"
#include "Constants.h"
#include "Player.h"


USING_NS_CC;


bool MonsterHealthOffsetDurationStatus::initWithHealthOffset(int healthOffset, int duration){
    if(!Status::init()){
        return false;
    }
    monsterHealthOffsetAmount = healthOffset;
    this->duration = duration;
        isPreemptive = false;
    return true;
}

void MonsterHealthOffsetDurationStatus::addStatusToGameObject(MonsterSprite *monster){
    //damage immediate, no need to add to monster
    monster->activeStatusArray->addObject(this);
    if(GM->player->playedCards->count() <= 0){
        //preemptive bounus
        isPreemptive = true;
    }
    
}

//checks whether the status can be used
bool MonsterHealthOffsetDurationStatus::checkStart(){
    return true;
}

//called when status is given to object
void MonsterHealthOffsetDurationStatus::applyStatus(){

}

//called when the status ends
void MonsterHealthOffsetDurationStatus::applyEndStatus(){
    
}

//checks whether the status should be destroyed
bool MonsterHealthOffsetDurationStatus::checkEnd(){
    if(duration <= 0 ){
        return true;
    }
    return false;
}

//called at end of turn
void MonsterHealthOffsetDurationStatus::updateStatus(MonsterSprite *monster){
    int offset = monsterHealthOffsetAmount;
    if(isPreemptive){
        offset += preemptiveBonus;
    }
    monster->changeMonsterHealth(offset);
    duration--;
}
