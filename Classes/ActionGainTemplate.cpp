//
//  ActionGainTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 12/10/13.
//
//

#include "ActionGainTemplate.h"
#include "Statuses.h"
#include "CardSprite.h"
#include "CardTargets.h"

void ActionGainTemplate::addAugmentationStatus(){
    
}

void ActionGainTemplate::addAdditionalCost(){
    
}

void ActionGainTemplate::addMainStatus(){
    CardTargets *cardTargets = new CardTargets();
    cardTargets->init();
    cardTargets->targetingType = PlayArea;
    cardTargets->isTargetRequired = false;
    createdCard->cardTargets = cardTargets;
    
    cardPower += arc4random()%3;
    cardPower -= arc4random()%((int)cardPower/2);
    cardPower += arc4random()%((int)cardPower/2);
    actionGain = 2;
    GainActionStatus *status = new GainActionStatus();
    status->initWithActionGain(2);
    createdCard->cardTargets->statuses->addObject(status);
    mainDescription = CCString::createWithFormat("Gain %i Actions", actionGain);
}

int ActionGainTemplate::calculateSoul(){
    int cost = (int)cardPower;
    cost -= arc4random()%(cost/2);
    cost += arc4random()%(cost/4);
    return cost;
}

