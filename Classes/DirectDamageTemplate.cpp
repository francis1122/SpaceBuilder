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



void DirectDamageTemplate::createCardTargets(){
    CardTargets *cardTargets = new MonsterTargets();
    cardTargets->init();
    createdCard->cardTargets = cardTargets;
}

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
            powerLevel -= cardPower/6;
            cardCostOffset += cardPower/6;
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
            powerLevel -= cardPower/6;
            cardCostOffset += cardPower/6;
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
            powerLevel -= cardPower/6;
            cardCostOffset += cardPower/6;
            
            augmentationDescription = CCString::createWithFormat("\nKilling Blow: Draw 2 Cards");
        
        deathStatus->initWithStatus(status);
        createdCard->cardTargets->statuses->addObject(deathStatus);
    }
}

void DirectDamageTemplate::addGreenAugmentationStatus(){
    cardPower += cardPower/6;
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
    
    int attack = (int)cardPower/6 + LLMath::diceRoll((int)cardPower/3, 1);
    MonsterHealthOffsetStatus *status = new MonsterHealthOffsetStatus();
    status->initWithHealthOffset(-attack);
    createdCard->cardTargets->statuses->addObject(status);
    createdCard->setupDamageCard(attack);
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

void DirectDamageTemplate::addGreenMainStatus(){
    addNeutralMainStatus();
}

#pragma mark -







