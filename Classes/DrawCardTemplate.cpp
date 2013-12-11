//
//  DrawCardTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 12/10/13.
//
//

#include "DrawCardTemplate.h"
#include "Statuses.h"
#include "CardSprite.h"
#include "CardTargets.h"

void DrawCardTemplate::addAugmentationStatus(){
    
}

void DrawCardTemplate::addAdditionalCost(){
    
}

void DrawCardTemplate::addMainStatus(){
    CardTargets *cardTargets = new CardTargets();
    cardTargets->init();
    cardTargets->targetingType = PlayArea;
    cardTargets->isTargetRequired = false;
    createdCard->cardTargets = cardTargets;
    
    cardPower += arc4random()%3;
    cardPower -= arc4random()%((int)cardPower/2);
    cardPower += arc4random()%((int)cardPower/2);
    drawCardAmount = 2;
    DrawCardStatus *status = new DrawCardStatus();
    status->initWithDrawAmount(2);
    createdCard->cardTargets->statuses->addObject(status);
    mainDescription =CCString::createWithFormat("Draw %i Cards", drawCardAmount);
}

int DrawCardTemplate::calculateSoul(){
    int cost = (int)cardPower;
    cost -= arc4random()%(cost/2);
    cost += arc4random()%(cost/4);
    return cost;
}



