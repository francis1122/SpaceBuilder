//
//  BloodGiantTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/15/14.
//
//

#include "BloodGiantTemplate.h"


#include "Statuses.h"


const std::string BloodGiantTemplate::CLASS_NAME = "BloodGiantTemplate";

void BloodGiantTemplate::addAugmentationStatus()
{
    int rand = arc4random()%1;
    if(rand == 0){
        //chance of taunt
        augmentationDescription = CCString::createWithFormat("Taunt\n");
        createdMonster->hasTaunt = true;
    }
    
    
}


void BloodGiantTemplate::addMainStats()
{
    createdMonster->life = (int)(powerLevel/4 + LLMath::diceRoll(powerLevel/9,2));
    createdMonster->maxLife = createdMonster->life;
    createdMonster->attack = (int)(powerLevel/5 + LLMath::getIntValue(0,powerLevel/10));
    createdMonster->location = 5;
    createdMonster->monsterLevel = (int)powerLevel;
    monsterSpriteName =CCString::createWithFormat("BloodGiant");
}


void BloodGiantTemplate::addRewards()
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
