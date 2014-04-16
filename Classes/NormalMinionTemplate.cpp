//
//  NormalMinionTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 2/27/14.
//
//

#include "NormalMinionTemplate.h"
#include "Statuses.h"

const std::string NormalMinionTemplate::CLASS_NAME = "NormalMinionTemplate";

void NormalMinionTemplate::addAugmentationStatus()
{
    
}


void NormalMinionTemplate::addMainStats()
{
    createdMonster->life = 1 + (int)(powerLevel/5 + LLMath::diceRoll(powerLevel/8,1));
    createdMonster->maxLife = createdMonster->life;
    createdMonster->attack = (int)(powerLevel/8 + LLMath::getIntValue(0,powerLevel/8));
    createdMonster->location = 3 + arc4random()%2;
    createdMonster->monsterLevel = (int)powerLevel;
    
    monsterSpriteName = CCString::createWithFormat("Minion");
}


void NormalMinionTemplate::addRewards()
{
    //add monster rewards
    int rand = arc4random()%8;
    if(rand == 0){
        GainSoulStatus *status = new GainSoulStatus();
        status->initWithSoulGain(1);
        createdMonster->afterDeathEffectArray->addObject(status);
        rewardDescription = CCString::createWithFormat("Gain 1 Soul");
        
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
