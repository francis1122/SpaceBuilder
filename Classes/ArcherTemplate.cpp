//
//  ArcherTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/15/14.
//
//

#include "ArcherTemplate.h"

#include "Statuses.h"


const std::string ArcherTemplate::CLASS_NAME = "ArcherTemplate";

void ArcherTemplate::addAugmentationStatus()
{
    
    
}


void ArcherTemplate::addMainStats()
{
    createdMonster->life = (int)(powerLevel/5 + LLMath::diceRoll(powerLevel/7,1));
    createdMonster->maxLife = createdMonster->life;
    createdMonster->attack = (int)(powerLevel/9 + LLMath::getIntValue(0,powerLevel/10));
    createdMonster->location = 3;
    createdMonster->hasRange = true;
    createdMonster->monsterLevel = (int)powerLevel;
    augmentationDescription = CCString::createWithFormat("Ranged");
    monsterSpriteName =CCString::createWithFormat("Archer");
}


void ArcherTemplate::addRewards()
{
    //add monster rewards
    int rand = arc4random()%7;
    if(rand == 0){
        GainSoulStatus *status = new GainSoulStatus();
        status->initWithSoulGain(1);
        createdMonster->afterDeathEffectArray->addObject(status);
        rewardDescription = CCString::createWithFormat("Gain 1 Soul");
    }
    //also gives life gain
    
}
