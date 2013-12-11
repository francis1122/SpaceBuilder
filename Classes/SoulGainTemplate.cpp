//
//  SoulGainTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 12/10/13.
//
//

#include "SoulGainTemplate.h"
#include "Statuses.h"
#include "CardSprite.h"
#include "CardTargets.h"

void SoulGainTemplate::addAugmentationStatus(){
    
}

void SoulGainTemplate::addAdditionalCost(){
    
}

void SoulGainTemplate::addMainStatus(){
    CardTargets *cardTargets = new CardTargets();
    cardTargets->init();
    cardTargets->targetingType = PlayArea;
    cardTargets->isTargetRequired = false;
    createdCard->cardTargets = cardTargets;
    
    cardPower += arc4random()%3;
    cardPower -= arc4random()%((int)cardPower/2);
    cardPower += arc4random()%((int)cardPower/2);
    soulGain = cardPower;
    GainSoulStatus *status = new GainSoulStatus();
    status->initWithSoulGain(cardPower);
    createdCard->cardTargets->statuses->addObject(status);
    mainDescription =CCString::createWithFormat("Gain %i Soul", soulGain);
}

int SoulGainTemplate::calculateSoul(){
    int cost = (int)cardPower;
    cost -= 2;
    cost += arc4random()%(cost/3);
    return cost;
}

