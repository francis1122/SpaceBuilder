//
//  DemonTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 2/23/14.
//
//

#include "DemonTemplate.h"
#include "Statuses.h"
USING_NS_CC;

const std::string DemonTemplate::CLASS_NAME = "DemonTemplate";

void DemonTemplate::addAugmentationStatus()
{
    
}


void DemonTemplate::addMainStats()
{
    createdMonster->life = (int)(powerLevel/1.6 + LLMath::diceRoll(powerLevel/4,1));
    createdMonster->maxLife = createdMonster->life;
    createdMonster->attack = (int)(powerLevel/5 + LLMath::getIntValue(0,powerLevel/5));
    createdMonster->location = 4 + arc4random()%2;
    createdMonster->monsterLevel = (int)powerLevel * 1.5;
    
    monsterSpriteName =CCString::createWithFormat("Troll");
}


void DemonTemplate::addRewards()
{

    
}
