//
//  RandomMonsterStatus.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 12/30/13.
//
//

#include "RandomMonsterStatus.h"


#include "GainSoulStatus.h"
#include "MonsterSprite.h"
#include "GameManager.h"
#include "Player.h"


USING_NS_CC;



bool RandomMonsterStatus::initWithStatus(Status *_status, int _targets){
    if(!Status::init()){
        return false;
    }

    //TODO:: put in a saftey check so status requires a monster for targeting
    randomStatus = _status;
    targets = _targets;
    
    return true;
}

void RandomMonsterStatus::addStatusToGameObject(MonsterSprite *monster){
    //damage immediate, no need to add to monster
//    monster->life += monsterHealthOffsetAmount;
}

//checks whether the status can be used
bool RandomMonsterStatus::checkStart(){
        // check if there are targets;
    GameManager *GM = GameManager::sharedGameManager();
    if(GM->monsterArray->count() > 0){
        return true;
    }else{
        return false;
    }
}

//called when status is given to object
void RandomMonsterStatus::applyStatus(){
    GameManager *GM = GameManager::sharedGameManager();

    //choose random monsters and apply status to monsters X times
    for( int i = 0; i < targets; i++){
        //choose random monster
        if(GM->monsterArray->count() > 0){
            MonsterSprite *monster = (MonsterSprite*)GM->monsterArray->objectAtIndex(arc4random()%GM->monsterArray->count());
            randomStatus->addStatusToGameObject(monster);
        }
    }
}

//called when the status ends
void RandomMonsterStatus::applyEndStatus(){
    
}

//checks whether the status should be destroyed
bool RandomMonsterStatus::checkEnd(){
    return true;
}

//called at end of turn
void RandomMonsterStatus::updateStatus(){
    
}
