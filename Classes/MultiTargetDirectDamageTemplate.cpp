//
//  MultiTargetDirectDamageTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/2/14.
//
//

#include "MultiTargetDirectDamageTemplate.h"
#include "Statuses.h"
#include "CardSprite.h"
#include "Targets.h"
#include "Action.h"
#include "CardGenerator.h"
#include "LLMath.h"


const std::string MultiTargetDirectDamageTemplate::CLASS_NAME = "MultiTargetDirectDamageTemplate";

void MultiTargetDirectDamageTemplate::createCardTargets(){
    CardTargets *cardTargets = new PlayAreaToTargetMonstersTargets();
    cardTargets->init();
    createdCard->cardTargets = cardTargets;
}


#pragma mark - augmentation


void MultiTargetDirectDamageTemplate::addNeutralAugmentationStatus(){
    
}

void MultiTargetDirectDamageTemplate::addRedAugmentationStatus(){
    int rand = arc4random()%3;
    if(rand == 0){
        DeathBlowStatus *deathStatus = new DeathBlowStatus();
        //choose status
        Status *killStatus;
        int soulGain = (int)cardPower/6 + LLMath::diceRoll((int)cardPower/8, 1);
        GainSoulStatus *status = new GainSoulStatus();
        status->initWithSoulGain(soulGain);
        killStatus = status;
        powerLevel -= cardPower/4;
        cardCostOffset += cardPower/4;
        augmentationDescription = CCString::createWithFormat("Killing Blow: Gain %i soul", soulGain);
        
        deathStatus->initWithStatus(killStatus);
        createdCard->cardTargets->statuses->addObject(deathStatus);
    }
}

void MultiTargetDirectDamageTemplate::addBlueAugmentationStatus(){
    int rand = arc4random()%3;
    if(rand == 0){
        //killing blow augmentation
        DeathBlowStatus *deathStatus = new DeathBlowStatus();
        //choose status
        Status *killStatus;
        GainActionStatus *status = new GainActionStatus();
        CCArray *actions = new CCArray();
        actions->init();
        Action *action = new Action();
        action->init(Neutral);
        actions->addObject(action);
        status->initWithActionGain(actions);
        killStatus = status;
        powerLevel -= powerLevel/6;
        cardCostOffset += powerLevel/6;
        augmentationDescription = CCString::createWithFormat("Killing Blow: Gain a Neutral Action");
        deathStatus->initWithStatus(killStatus);
        createdCard->cardTargets->statuses->addObject(deathStatus);
        
    }
}

void MultiTargetDirectDamageTemplate::addYellowAugmentationStatus(){
    int rand = arc4random()%3;
    if(rand == 0){
        //killing blow augmentation
        DeathBlowStatus *deathStatus = new DeathBlowStatus();
        //choose status
        Status *killStatus;
        DrawCardStatus *status = new DrawCardStatus();
        status->initWithDrawAmount(2);
        killStatus = status;
        powerLevel -= powerLevel/6;
        cardCostOffset += powerLevel/6;
        
        augmentationDescription = CCString::createWithFormat("Killing Blow: Draw 2 Cards");
        
        deathStatus->initWithStatus(killStatus);
        createdCard->cardTargets->statuses->addObject(status);
    }
}

void MultiTargetDirectDamageTemplate::addGreenAugmentationStatus(){
    cardPower += 6;
    cardCostOffset -= 3;
}

#pragma mark - additional cost


void MultiTargetDirectDamageTemplate::addNeutralAdditionalCost(){
}

void MultiTargetDirectDamageTemplate::addRedAdditionalCost(){
}

void MultiTargetDirectDamageTemplate::addBlueAdditionalCost(){
}

void MultiTargetDirectDamageTemplate::addYellowAdditionalCost(){
}

void MultiTargetDirectDamageTemplate::addGreenAdditionalCost(){
}


#pragma mark - main status

void MultiTargetDirectDamageTemplate::addNeutralMainStatus(){
    
    createdCard->cardTargets->targetingType = Monsters;
    createdCard->cardTargets->targetAmount = 2;
    
    int attack = (int)cardPower/6 + LLMath::diceRoll((int)cardPower/4, 1);
    MonsterHealthOffsetStatus *status = new MonsterHealthOffsetStatus();
    status->initWithHealthOffset(-attack);
    createdCard->cardTargets->statuses->addObject(status);
    createdCard->setupDamageCard(attack);
    mainDescription = CCString::createWithFormat("Multi Shot 2");
}

void MultiTargetDirectDamageTemplate::addRedMainStatus(){
    addNeutralMainStatus();
}

void MultiTargetDirectDamageTemplate::addBlueMainStatus(){
    addNeutralMainStatus();
}

void MultiTargetDirectDamageTemplate::addYellowMainStatus(){
    addNeutralMainStatus();
}

void MultiTargetDirectDamageTemplate::addGreenMainStatus(){
    addNeutralMainStatus();
}

#pragma mark -

