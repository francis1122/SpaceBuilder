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
#include "Action.h"
#include "CardGenerator.h"
#include "LLMath.h"


const std::string DirectDamageTemplate::CLASS_NAME = "DirectDamageTemplate";




#pragma mark - augmentation


void DirectDamageTemplate::addNeutralAugmentationStatus(){
    
}

void DirectDamageTemplate::addRedAugmentationStatus(){
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

void DirectDamageTemplate::addBlueAugmentationStatus(){
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

void DirectDamageTemplate::addYellowAugmentationStatus(){
    int rand = arc4random()%3;
    if(rand == 0){
        //killing blow augmentation
        DeathBlowStatus *deathStatus = new DeathBlowStatus();
        //choose status
            DrawCardStatus *status = new DrawCardStatus();
            status->initWithDrawAmount(2);
            powerLevel -= 2;
            cardCostOffset += 2;
            
            augmentationDescription = CCString::createWithFormat("\nKilling Blow: Draw 2 Cards");
        
        deathStatus->initWithStatus(status);
        createdCard->cardTargets->statuses->addObject(deathStatus);
    }
}

void DirectDamageTemplate::addPurpleAugmentationStatus(){
    cardPower += 6;
    cardCostOffset -= 3;
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

void DirectDamageTemplate::addPurpleAdditionalCost(){
}


#pragma mark - main status

void DirectDamageTemplate::addNeutralMainStatus(){
    
    createdCard->cardTargets->targetingType = Monsters;
    
    cardPower = (int)cardPower/2 + LLMath::diceRoll((int)cardPower/3, 3);
    int attack = (int)cardPower/2 + LLMath::diceRoll((int)cardPower/4, 3);
    MonsterHealthOffsetStatus *status = new MonsterHealthOffsetStatus();
    status->initWithHealthOffset(-attack/2);
    createdCard->cardTargets->statuses->addObject(status);
    createdCard->setupDamageCard(attack/2);
}

void DirectDamageTemplate::addRedMainStatus(){
    addNeutralMainStatus();
}

void DirectDamageTemplate::addBlueMainStatus(){
    addNeutralMainStatus();
}

void DirectDamageTemplate::addYellowMainStatus(){
    addNeutralMainStatus();
}

void DirectDamageTemplate::addPurpleMainStatus(){
    addNeutralMainStatus();
}

#pragma mark -







