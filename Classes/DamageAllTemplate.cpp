//
//  DamageAllTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 2/17/14.
//
//

#include "DamageAllTemplate.h"

#include "DirectDamageTemplate.h"
#include "Statuses.h"
#include "CardSprite.h"
#include "Targets.h"
#include "Action.h"
#include "CardGenerator.h"
#include "LLMath.h"


const std::string DamageAllTemplate::CLASS_NAME = "DamageAllTemplate";

void DamageAllTemplate::createCardTargets(CardSprite *card){
    CardTargets *cardTargets = new PlayAreaTargets();
    cardTargets->initWithCardSprite(card);
    createdCard->cardTargets = cardTargets;
}


#pragma mark - augmentation


void DamageAllTemplate::addNeutralAugmentationStatus(){
    
}

void DamageAllTemplate::addRedAugmentationStatus(){
    /*  int rand = arc4random()%3;
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
     
     }*/
}

void DamageAllTemplate::addBlueAugmentationStatus(){
    /* int rand = arc4random()%3;
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
     */
}

void DamageAllTemplate::addYellowAugmentationStatus(){
    
}

void DamageAllTemplate::addGreenAugmentationStatus(){
    //  cardPower += 6;
    //    cardCostOffset -= 3;
}

#pragma mark - additional cost


void DamageAllTemplate::addNeutralAdditionalCost(){
}

void DamageAllTemplate::addRedAdditionalCost(){
}

void DamageAllTemplate::addBlueAdditionalCost(){
}

void DamageAllTemplate::addYellowAdditionalCost(){
}

void DamageAllTemplate::addGreenAdditionalCost(){
}


#pragma mark - main status

void DamageAllTemplate::addNeutralMainStatus(){
    int attack = (int)cardPower/12 + LLMath::diceRoll((int)cardPower/12, 1);
    if(attack < 1){
        attack = 1;
    }
    
    MonsterHealthOffsetStatus *status = new MonsterHealthOffsetStatus();
    status->initWithHealthOffset(-attack);
    
    AllMonsterStatus *allStatus = new AllMonsterStatus();
    allStatus->initWithStatus(status);
    
    createdCard->cardTargets->statuses->addObject(allStatus);
    createdCard->setupDamageCard(attack);
    mainDescription = CCString::createWithFormat("Attack all monsters");
}

void DamageAllTemplate::addRedMainStatus(){
    addNeutralMainStatus();
}

void DamageAllTemplate::addBlueMainStatus(){
    addNeutralMainStatus();
}

void DamageAllTemplate::addYellowMainStatus(){
    addNeutralMainStatus();
}

void DamageAllTemplate::addGreenMainStatus(){
    addNeutralMainStatus();
}

#pragma mark -