//
//  DirectDamageTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 12/6/13.
//
//

#include "DirectDamageTemplate.h"
#include "Statuses.h"
#include "CardSprite.h"
#include "CardTargets.h"


void DirectDamageTemplate::addAugmentationStatus(){
    int rand = arc4random()%4;
    if(rand == 0){
        //killing blow augmentation
        DeathBlowStatus *status = new DeathBlowStatus();
        //choose status
        int rand2 = arc4random()%3;
        Status *killStatus;
        if(rand2 == 0){
            GainSoulStatus *status = new GainSoulStatus();
            status->initWithSoulGain(cardPower/2);
            killStatus = status;
            powerLevel -= 2;
            augmentationDescription = CCString::createWithFormat("\nKilling Blow: Gain %i Soul", (int)(cardPower/2));
        }else if(rand2 == 1){
            GainActionStatus *status = new GainActionStatus();
            status->initWithActionGain(1);
            killStatus = status;
            powerLevel -= 2;
            augmentationDescription = CCString::createWithFormat("\nKilling Blow: Gain an Action");
        }else if(rand2 == 2){
            DrawCardStatus *status = new DrawCardStatus();
            status->initWithDrawAmount(1);
            killStatus = status;
            powerLevel -= 2;
            augmentationDescription = CCString::createWithFormat("\nKilling Blow: Draw a Card");
        }
        
        status->initWithStatus(killStatus);
    }

}

void DirectDamageTemplate::addAdditionalCost(){
    
}

void DirectDamageTemplate::addMainStatus(){
    //status
    CardTargets *cardTargets = new CardTargets();
    cardTargets->init();
    cardTargets->targetingType = Monsters;
    cardTargets->isTargetRequired = true;
    createdCard->cardTargets = cardTargets;
    
    
    cardPower -= arc4random()%((int)cardPower/2);
    cardPower += arc4random()%((int)cardPower/2);

    MonsterHealthOffsetStatus *status = new MonsterHealthOffsetStatus();
    status->initWithHealthOffset(-(int)cardPower);
    createdCard->cardTargets->statuses->addObject(status);
    mainDescription =CCString::createWithFormat("Attack Monster for %i", (int)cardPower);
}

int DirectDamageTemplate::calculateSoul(){
    int cost = (int)cardPower;
    cost += 2;
    cost -= arc4random()%(cost/4);
    cost += arc4random()%(cost/3);
    return cost;
}






