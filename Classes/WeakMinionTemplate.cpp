//
//  WeakMinionTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/9/14.
//
//

#include "WeakMinionTemplate.h"
#include "Statuses.h"


const std::string WeakMinionTemplate::CLASS_NAME = "WeakMinionTemplate";

void WeakMinionTemplate::addAugmentationStatus()
{
    
}


void WeakMinionTemplate::addMainStats()
{
    createdMonster->life = (int)(powerLevel/6 + LLMath::diceRoll(powerLevel/3,1));
    createdMonster->maxLife = createdMonster->life;
    createdMonster->attack = (int)(powerLevel/6 + LLMath::getIntValue(0,powerLevel/5));
    createdMonster->location = 4 + arc4random()%2;
    createdMonster->monsterLevel = (int)powerLevel;
    
    monsterSpriteName =CCString::createWithFormat("Minion");
}


void WeakMinionTemplate::addRewards()
{
    //add monster rewards
    int rand = arc4random()%8;
    if(rand == 0 || rand == 1){
        GainSoulStatus *status = new GainSoulStatus();
        status->initWithSoulGain(powerLevel/5);
        createdMonster->afterDeathEffectArray->addObject(status);
        rewardDescription = CCString::createWithFormat("Gain %i Soul", status->soulGainAmount);

    }else if(rand == 2){
        GainActionStatus *status = new GainActionStatus();
        CCArray *actions = new CCArray();
        actions->init();
        Action *action = new Action();
        action->init(Neutral);
        actions->addObject(action);
        status->initWithActionGain(actions);
        createdMonster->afterDeathEffectArray->addObject(status);
        rewardDescription = CCString::createWithFormat("Gain an Action");
    }
    
}

