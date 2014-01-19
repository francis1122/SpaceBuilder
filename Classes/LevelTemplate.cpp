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
    monstersLeft = 14;
    maxLanes = 5;
    return true;
}

MonsterSprite* LevelTemplate::spawnMonster(){

    
    MonsterSprite *monster;
    

    
    return monster;
}