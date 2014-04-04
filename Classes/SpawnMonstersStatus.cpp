//
//  SpawnMonstersStatus.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 3/5/14.
//
//

#include "SpawnMonstersStatus.h"

#include "MonsterSprite.h"
#include "GameManager.h"
#include "Player.h"

USING_NS_CC;



bool SpawnMonstersStatus::init(){
    if(!Status::init()){
        return false;
    }
    return true;
}


void SpawnMonstersStatus::addStatusToGameObject(MonsterSprite *monster)
{
    this->applyStatus();
}

void SpawnMonstersStatus::addStatusToCardSprite(CardSprite *card)
{
    this->applyStatus();
}

//checks whether the status can be used
bool SpawnMonstersStatus::checkStart(){
    return true;
}

//called when status is given to object
void SpawnMonstersStatus::applyStatus(){

}

//called when the status ends
void SpawnMonstersStatus::applyEndStatus(){
    
}

//checks whether the status should be destroyed
bool SpawnMonstersStatus::checkEnd(){
    return true;
}

//called at end of turn
void SpawnMonstersStatus::updateStatus(MonsterSprite *monster){
    GameManager *GM = GameManager::sharedGameManager();
    GM->spawnMonster();
}
