//
//  RushMinionTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/15/14.
//
//

#include "RushMinionTemplate.h"


#include "Statuses.h"


const std::string RushMinionTemplate::CLASS_NAME = "RushMinionTemplate";

void RushMinionTemplate::addAugmentationStatus()
{
    
}


void RushMinionTemplate::addMainStats()
{
    createdMonster->life = (int)(powerLevel/4 + LLMath::diceRoll(powerLevel/6,1));
    createdMonster->maxLife = createdMonster->life;
    createdMonster->attack = (int)(powerLevel/8 + LLMath::getIntValue(0,powerLevel/8));
    createdMonster->location = 2 + arc4random()%2;
    createdMonster->monsterLevel = (int)powerLevel;
    
    monsterSpriteName =CCString::createWithFormat("Troll");
}


void RushMinionTemplate::addRewards()
{
    //add monster rewards
    int rand = arc4random()%5;
    if(rand == 0){
        GainSoulStatus *status = new GainSoulStatus();
        status->initWithSoulGain(powerLevel/5);
        createdMonster->afterDeathEffectArray->addObject(status);
        rewardDescription = CCString::createWithFormat("Gain %i Soul", status->soulGainAmount);
        
    }else if(rand ==1){
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
