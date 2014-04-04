//
//  ArcherBossTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 2/27/14.
//
//

#include "ArcherBossTemplate.h"
#include "Statuses.h"


const std::string ArcherBossTemplate::CLASS_NAME = "ArcherBossTemplate";

void ArcherBossTemplate::addAugmentationStatus()
{
    
}


void ArcherBossTemplate::addMainStats()
{
    createdMonster->life = 1 + (int)(powerLevel/2 + LLMath::diceRoll(powerLevel/5,1));
    createdMonster->maxLife = createdMonster->life;
    createdMonster->attack = (int)(powerLevel/4 + LLMath::getIntValue(0,powerLevel/10));
    createdMonster->location = 3;
    createdMonster->monsterLevel = (int)powerLevel;
    createdMonster->hasRange = true;
    augmentationDescription = CCString::createWithFormat("Ranged");
    
    createdMonster->isBoss = true;
    monsterSpriteName =CCString::createWithFormat("Minion");
}


void ArcherBossTemplate::addRewards()
{
    
    rewardDescription = CCString::createWithFormat("Boss");
    
}
