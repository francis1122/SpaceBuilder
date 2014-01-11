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
    createdMonster->life = powerLevel/6 + LLMath::diceRoll(powerLevel/3,3);
    createdMonster->attack = powerLevel/5 + LLMath::getIntValue(0,powerLevel/4);
    createdMonster->location = 2 + arc4random()%3;
    createdMonster->monsterLevel = (int)powerLevel;
    

}


void WeakMinionTemplate::addRewards()
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