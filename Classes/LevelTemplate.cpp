//
//  LevelTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/15/14.
//
//

#include "LevelTemplate.h"
#include "Constants.h"


bool LevelTemplate::init(int _levelNumber){
    this->levelNumber = _levelNumber;
    levelPower = 10 + (levelNumber * MONSTER_IMPROVEMENT_PER_LEVEL);
    this->powerLevel = levelPower;
    monstersLeft = 20;
    levelName = new CCString();
    levelName->initWithFormat("LevelName");
    levelDescription = new CCString();
    levelDescription->initWithFormat("Level Description");
    return true;
}

MonsterSprite *LevelTemplate::getMonster(){
    MonsterSprite *monster;
    if(monstersLeft <= 0){
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