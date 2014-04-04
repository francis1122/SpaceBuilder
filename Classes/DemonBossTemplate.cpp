//
//  DemonBossTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 2/27/14.
//
//

#include "DemonBossTemplate.h"
#include "Statuses.h"


const std::string DemonBossTemplate::CLASS_NAME = "DemonBossTemplate";

void DemonBossTemplate::addAugmentationStatus()
{
    
}


void DemonBossTemplate::addMainStats()
{
    createdMonster->life = 1 + (int)(powerLevel/1.5 + LLMath::diceRoll(powerLevel/5,1));
    createdMonster->maxLife = createdMonster->life;
    createdMonster->attack = (int)(powerLevel/4 + LLMath::getIntValue(0,powerLevel/10));
    createdMonster->location = 4;
    createdMonster->monsterLevel = (int)powerLevel;
    createdMonster->isBoss = true;
    monsterSpriteName = CCString::createWithFormat("Minion");
    
/*    SpawnMonstersStatus *status = new SpawnMonstersStatus();
    status->init();
    createdMonster->activeStatusArray->addObject(status);
    */
    
}


void DemonBossTemplate::addRewards()
{
    rewardDescription = CCString::createWithFormat("Boss");

    
}
