//
//  DamageActionTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 2/21/14.
//
//

#include "DamageActionTemplate.h"
#include "Statuses.h"
#include "CardSprite.h"
#include "Targets.h"
#include "Action.h"
#include "CardGenerator.h"
#include "LLMath.h"


const std::string DamageActionTemplate::CLASS_NAME = "DamageActionTemplate";



void DamageActionTemplate::createCardTargets(CardSprite *card)
{
    CardTargets *cardTargets = new MonsterTargets();
    cardTargets->initWithCardSprite(card);
    createdCard->cardTargets = cardTargets;
}

#pragma mark - augmentation


void DamageActionTemplate::addNeutralAugmentationStatus(){
    
}

void DamageActionTemplate::addRedAugmentationStatus(){
    //killing blow augmentation
    GainActionStatus *status = new GainActionStatus();
    Action *actionOne = new Action();
    actionOne->init(Yellow);
    actionsGained->addObject(actionOne);
    status->initWithActionGain(actionsGained);
    createdCard->cardTargets->statuses->addObject(status);
}

void DamageActionTemplate::addBlueAugmentationStatus(){
    GainActionStatus *status = new GainActionStatus();
    Action *actionOne = new Action();
    actionOne->init(Blue);
    actionsGained->addObject(actionOne);
    status->initWithActionGain(actionsGained);
    createdCard->cardTargets->statuses->addObject(status);
}

void DamageActionTemplate::addYellowAugmentationStatus(){
    // combo
    GainActionStatus *status = new GainActionStatus();
    Action *actionOne = new Action();
    actionOne->init(Yellow);
    actionsGained->addObject(actionOne);
    status->initWithActionGain(actionsGained);
    createdCard->cardTargets->statuses->addObject(status);
}

void DamageActionTemplate::addGreenAugmentationStatus(){
    GainActionStatus *status = new GainActionStatus();
    Action *actionOne = new Action();
    actionOne->init(Green);
    actionsGained->addObject(actionOne);
    status->initWithActionGain(actionsGained);
    createdCard->cardTargets->statuses->addObject(status);
}

#pragma mark - additional cost


void DamageActionTemplate::addNeutralAdditionalCost(){
}

void DamageActionTemplate::addRedAdditionalCost(){
}

void DamageActionTemplate::addBlueAdditionalCost(){
}

void DamageActionTemplate::addYellowAdditionalCost(){
}

void DamageActionTemplate::addGreenAdditionalCost(){
}


#pragma mark - main status

void DamageActionTemplate::addNeutralMainStatus(){
    int attack = (int)cardPower/6 + LLMath::diceRoll((int)cardPower/8, 1);
    MonsterHealthOffsetStatus *status = new MonsterHealthOffsetStatus();
    status->initWithHealthOffset(-attack);
    createdCard->cardTargets->statuses->addObject(status);
    createdCard->setupDamageCard(attack);
}

void DamageActionTemplate::addRedMainStatus(){
    addNeutralMainStatus();
}

void DamageActionTemplate::addBlueMainStatus(){
    addNeutralMainStatus();
}

void DamageActionTemplate::addYellowMainStatus(){
    addNeutralMainStatus();
}

void DamageActionTemplate::addGreenMainStatus(){
    addNeutralMainStatus();
}

#pragma mark -







