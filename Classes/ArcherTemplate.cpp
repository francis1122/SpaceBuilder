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
    createdMonster->life = (int)(powerLevel/6 + LLMath::diceRoll(powerLevel/6,1));
    createdMonster->maxLife = createdMonster->life;
    createdMonster->attack = (int)(powerLevel/10 + LLMath::getIntValue(0,powerLevel/10));
    createdMonster->location = 3;
    createdMonster->hasRange = true;
    createdMonster->monsterLevel = (int)powerLevel;
    augmentationDescription = CCString::createWithFormat("Ranged");
    monsterSpriteName =CCString::createWithFormat("Archer");
}


void ArcherTemplate::addRewards()
{
    //add monster rewards
    int rand = arc4random()%5;
    if(rand == 0){
        GainSoulStatus *status = new GainSoulStatus();
        status->initWithSoulGain(powerLevel/5);
        createdMonster->afterDeathEffectArray->addObject(status);
        rewardDescription = CCString::createWithFormat("Gain %i Soul", status->soulGainAmount);
    }
    //also gives life gain
    
}
