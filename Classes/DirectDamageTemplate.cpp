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
#include "Targets.h"
#include "Action.h"
#include "CardGenerator.h"
#include "LLMath.h"


const std::string DirectDamageTemplate::CLASS_NAME = "DirectDamageTemplate";



void DirectDamageTemplate::createCardTargets(CardSprite *card)
{
    CardTargets *cardTargets = new MonsterTargets();
    cardTargets->initWithCardSprite(card);
    createdCard->cardTargets = cardTargets;

}

#pragma mark - augmentation


void DirectDamageTemplate::addNeutralAugmentationStatus(){
    
}

void DirectDamageTemplate::addRedAugmentationStatus(){
        //killing blow augmentation
        DeathBlowStatus *deathStatus = new DeathBlowStatus();
        //choose status
        Status *killStatus;
//        int soulGain = (int)cardPower/4 + LLMath::diceRoll((int)cardPower/8, 1);
        int soulGain = 1;
        GainSoulStatus *status = new GainSoulStatus();
        status->initWithSoulGain(soulGain);
        killStatus = status;
        powerLevel -= cardPower/4;
        cardCostOffset += cardPower/4;
        augmentationDescription = CCString::createWithFormat("Killing Blow: Gain 1 soul");
        
        deathStatus->initWithStatus(killStatus);
        createdCard->cardTargets->statuses->addObject(deathStatus);
}

void DirectDamageTemplate::addBlueAugmentationStatus(){
        //killing blow augmentation
        DeathBlowStatus *deathStatus = new DeathBlowStatus();
        //choose status
        DrawCardStatus *status = new DrawCardStatus();
        status->initWithDrawAmount(2);
        powerLevel -= cardPower/6;
        cardCostOffset += cardPower/4;
        
        augmentationDescription = CCString::createWithFormat("Killing Blow: Draw 2 Cards");
        deathStatus->initWithStatus(status);
        createdCard->cardTargets->statuses->addObject(deathStatus);
}

void DirectDamageTemplate::addYellowAugmentationStatus(){
        // combo
        //killing blow augmentation
        DeathBlowStatus *deathStatus = new DeathBlowStatus();
        //choose status
        DrawCardStatus *status = new DrawCardStatus();
        status->initWithDrawAmount(2);
        powerLevel -= cardPower/6;
        cardCostOffset += cardPower/4;
        
        augmentationDescription = CCString::createWithFormat("Killing Blow: Draw 2 Cards");
        deathStatus->initWithStatus(status);
        createdCard->cardTargets->statuses->addObject(deathStatus);
}

void DirectDamageTemplate::addGreenAugmentationStatus(){
        //killing blow augmentation
        DeathBlowStatus *deathStatus = new DeathBlowStatus();
        //choose status
        PlayerHealthOffsetStatus *status = new PlayerHealthOffsetStatus();
        int healthGain = (int)cardPower/4 + LLMath::diceRoll((int)cardPower/8, 1);
        status->initWithHealthOffset(healthGain);
        powerLevel -= cardPower/6;
        cardCostOffset += cardPower/4;
        
        augmentationDescription = CCString::createWithFormat("Killing blow: Gain %i health", healthGain);
        deathStatus->initWithStatus(status);
        createdCard->cardTargets->statuses->addObject(deathStatus);
}

#pragma mark - additional cost


void DirectDamageTemplate::addNeutralAdditionalCost(){
}

void DirectDamageTemplate::addRedAdditionalCost(){
}

void DirectDamageTemplate::addBlueAdditionalCost(){
}

void DirectDamageTemplate::addYellowAdditionalCost(){
}

void DirectDamageTemplate::addGreenAdditionalCost(){
}


#pragma mark - main status

void DirectDamageTemplate::addNeutralMainStatus(){
    int attack = (int)cardPower/4 + LLMath::diceRoll((int)cardPower/7, 1);
    MonsterHealthOffsetStatus *status = new MonsterHealthOffsetStatus();
    status->initWithHealthOffset(-attack);
    createdCard->cardTargets->statuses->addObject(status);
    createdCard->setupDamageCard(attack);
}

void DirectDamageTemplate::addRedMainStatus(){
    addNeutralMainStatus();
}

void DirectDamageTemplate::addBlueMainStatus(){
    cardPower -= cardPower/4;
    addNeutralMainStatus();
}

void DirectDamageTemplate::addYellowMainStatus(){
    addNeutralMainStatus();
}

void DirectDamageTemplate::addGreenMainStatus(){
    addNeutralMainStatus();
}

#pragma mark -







