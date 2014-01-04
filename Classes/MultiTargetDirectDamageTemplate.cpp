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
#include "CardTargets.h"
#include "Action.h"
#include "CardGenerator.h"
#include "LLMath.h"


const std::string MultiTargetDirectDamageTemplate::CLASS_NAME = "MultiTargetDirectDamageTemplate";




#pragma mark - augmentation


void MultiTargetDirectDamageTemplate::addNeutralAugmentationStatus(){
    
}

void MultiTargetDirectDamageTemplate::addRedAugmentationStatus(){
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
        action->init(Red);
        actions->addObject(action);
        status->initWithActionGain(actions);
        killStatus = status;
        powerLevel -= 2;
        cardCostOffset += 2;
        augmentationDescription = CCString::createWithFormat("\nKilling Blow: Gain a Red Action");
        
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
        powerLevel -= 2;
        cardCostOffset += 2;
        augmentationDescription = CCString::createWithFormat("\nKilling Blow: Gain a Neutral Action");
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
        powerLevel -= 2;
        cardCostOffset += 2;
        
        augmentationDescription = CCString::createWithFormat("\nKilling Blow: Draw 2 Cards");
        
        deathStatus->initWithStatus(killStatus);
        createdCard->cardTargets->statuses->addObject(status);
    }
}

void MultiTargetDirectDamageTemplate::addPurpleAugmentationStatus(){
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

void MultiTargetDirectDamageTemplate::addPurpleAdditionalCost(){
}


#pragma mark - main status

void MultiTargetDirectDamageTemplate::addNeutralMainStatus(){
    
    createdCard->cardTargets->targetingType = Monsters;
    createdCard->cardTargets->isTargetRequired = true;
    createdCard->cardTargets->targetAmount = 2;
    
    cardPower = (int)cardPower/2 + LLMath::diceRoll((int)cardPower/3, 3);
    
    MonsterHealthOffsetStatus *status = new MonsterHealthOffsetStatus();
    status->initWithHealthOffset(-(int)cardPower/2);
    createdCard->cardTargets->statuses->addObject(status);
    createdCard->setupDamageCard((int)cardPower/2);
    mainDescription = CCString::createWithFormat("\nMulti Shot 2");
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

void MultiTargetDirectDamageTemplate::addPurpleMainStatus(){
    addNeutralMainStatus();
}

#pragma mark -

