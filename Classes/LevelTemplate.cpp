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
    maxLanes = 6;
    return true;
}

MonsterSprite* LevelTemplate::spawnMonster(){

    
    MonsterSprite *monster;
    

    
    return monster;
}