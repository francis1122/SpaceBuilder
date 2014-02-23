//
//  OozeTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/15/14.
//
//

#include "OozeTemplate.h"


#include "Statuses.h"


const std::string OozeTemplate::CLASS_NAME = "OozeTemplate";

void OozeTemplate::addAugmentationStatus()
{
    int rand = arc4random()%1;
    if(rand == 0){
        //chance of taunt
        int regen = (int)monsterPower/10 + LLMath::diceRoll((int)monsterPower/10, 1);
        MonsterHealthOffsetDurationStatus *status = new MonsterHealthOffsetDurationStatus();
        status->initWithHealthOffset(regen, 999);
        createdMonster->activeStatusArray->addObject(status);
        
        augmentationDescription = CCString::createWithFormat("Regen %i\n", regen);
    }
    
    
}


void OozeTemplate::addMainStats()
{
    createdMonster->life = (int)(powerLevel/3 + LLMath::diceRoll(powerLevel/8,2));
    createdMonster->maxLife = createdMonster->life;
    createdMonster->attack = (int)(powerLevel/7 + LLMath::getIntValue(0,powerLevel/10));
    createdMonster->location = 4 + arc4random()%2;
    createdMonster->monsterLevel = (int)powerLevel;
    monsterSpriteName =CCString::createWithFormat("Ooze"); 
}


void OozeTemplate::addRewards()
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

