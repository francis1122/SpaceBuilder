//
//  AllMonsterStatus.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 2/17/14.
//
//

#include "AllMonsterStatus.h"


#include "GainSoulStatus.h"
#include "MonsterSprite.h"
#include "GameManager.h"
#include "Player.h"


USING_NS_CC;



bool AllMonsterStatus::initWithStatus(Status *_status){
    if(!Status::init()){
        return false;
    }
    
    //TODO:: put in a saftey check so status requires a monster for targeting
    status = _status;
    
    return true;
}

void AllMonsterStatus::addStatusToGameObject(MonsterSprite *monster){
    //damage immediate, no need to add to monster
    //    monster->life += monsterHealthOffsetAmount;
}

//checks whether the status can be used
bool AllMonsterStatus::checkStart(){
    // check if there are targets;
    GameManager *GM = GameManager::sharedGameManager();
    if(GM->monsterArray->count() > 0){
        return true;
    }else{
        return false;
    }
}

//called when status is given to object
void AllMonsterStatus::applyStatus(){
    GameManager *GM = GameManager::sharedGameManager();
    
    //choose random monsters and apply status to monsters X times
    for( int i = 0; i < GM->monsterArray->count(); i++){
        MonsterSprite *monster = (MonsterSprite*)GM->monsterArray->objectAtIndex(i);
        status->addStatusToGameObject(monster);
    }
}

//called when the status ends
void AllMonsterStatus::applyEndStatus(){
    
}

//checks whether the status should be destroyed
bool AllMonsterStatus::checkEnd(){
    return true;
}

//called at end of turn
void AllMonsterStatus::updateStatus(){
    
}
