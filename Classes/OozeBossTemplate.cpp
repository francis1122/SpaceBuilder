//
//  OozeBossTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 2/27/14.
//
//

#include "OozeBossTemplate.h"

#include "Statuses.h"


const std::string OozeBossTemplate::CLASS_NAME = "OozeBossTemplate";

void OozeBossTemplate::addAugmentationStatus()
{
    int regen = (int)monsterPower/8 + LLMath::diceRoll((int)monsterPower/12, 1);
    MonsterHealthOffsetDurationStatus *status = new MonsterHealthOffsetDurationStatus();
    status->initWithHealthOffset(regen, 999);
    createdMonster->activeStatusArray->addObject(status);
    augmentationDescription = CCString::createWithFormat("Boss\rRegen %i\r", regen);
}


void OozeBossTemplate::addMainStats()
{
    createdMonster->life = 1 + (int)(powerLevel + LLMath::diceRoll(powerLevel/5,1));
    createdMonster->maxLife = createdMonster->life;
    createdMonster->attack = (int)(powerLevel/4 + LLMath::getIntValue(0,powerLevel/10));
    createdMonster->location = 4;
    createdMonster->monsterLevel = (int)powerLevel;
    createdMonster->isBoss = true;
    monsterSpriteName =CCString::createWithFormat("Ooze");
}


void OozeBossTemplate::addRewards()
{
    
    
}
