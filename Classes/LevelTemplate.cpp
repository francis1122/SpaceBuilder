//
//  LevelTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/15/14.
//
//

#include "LevelTemplate.h"



bool LevelTemplate::init(float _powerLevel){
    levelPower = _powerLevel;
    this->powerLevel = _powerLevel;
    monstersLeft = 15;
    return true;
}


MonsterSprite *LevelTemplate::getMonster(){
    MonsterSprite *monster;
    if(monstersLeft <=0){
        return NULL;
    }
    if(monstersLeft <= 1){
        monster = spawnBossMonster();
    }else{
        monster = spawnMonster();
    }
    monstersLeft--;
    return monster;
}

MonsterSprite* LevelTemplate::spawnMonster(){
    return NULL;
}


MonsterSprite *LevelTemplate::spawnBossMonster(){
    return NULL;
}