//
//  DragonBossTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/30/14.
//
//

#include "DragonBossTemplate.h"

#include "Statuses.h"


const std::string DragonBossTemplate::CLASS_NAME = "DragonBossTemplate";

void DragonBossTemplate::addAugmentationStatus()
{
    
}


void DragonBossTemplate::addMainStats()
{
    createdMonster->life = 1 + (int)(powerLevel/2 + LLMath::diceRoll(powerLevel/5,1));
    createdMonster->maxLife = createdMonster->life;
    createdMonster->attack = (int)(powerLevel/4 + LLMath::getIntValue(0,powerLevel/10));
    createdMonster->location = 4;
    createdMonster->monsterLevel = (int)powerLevel;
    createdMonster->isBoss = true;
    monsterSpriteName =CCString::createWithFormat("Minion");
}


void DragonBossTemplate::addRewards()
{
    
    rewardDescription = CCString::createWithFormat("Boss");
    
}

