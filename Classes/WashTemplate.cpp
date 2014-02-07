//
//  WashTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/17/14.
//
//

#include "WashTemplate.h"
#include "Statuses.h"
#include "CardSprite.h"
#include "Targets.h"
#include "Action.h"


const std::string WashTemplate::CLASS_NAME = "WashTemplate";

void WashTemplate::createCardTargets(CardSprite *card){
    CardTargets *cardTargets = new PlayAreaTargets();
    cardTargets->initWithCardSprite(card);
    createdCard->cardTargets = cardTargets;
}

#pragma mark - augmentation


void WashTemplate::addNeutralAugmentationStatus(){
    
}

void WashTemplate::addRedAugmentationStatus(){
    
}

void WashTemplate::addBlueAugmentationStatus(){
    
}

void WashTemplate::addYellowAugmentationStatus(){
    
}

void WashTemplate::addGreenAugmentationStatus(){
    
}

#pragma mark - additional cost


void WashTemplate::addNeutralAdditionalCost(){
}

void WashTemplate::addRedAdditionalCost(){
}

void WashTemplate::addBlueAdditionalCost(){
}

void WashTemplate::addYellowAdditionalCost(){
}

void WashTemplate::addGreenAdditionalCost(){
}


#pragma mark - main status



void WashTemplate::addNeutralMainStatus(){
    GainActionStatus *status = new GainActionStatus();
    Action *actionOne = new Action();
    actionOne->init(Neutral);
    actionsGained->addObject(actionOne);
    status->initWithActionGain(actionsGained);
    
    createdCard->cardTargets->statuses->addObject(status);
    createdCard->setCardType(Spell);
}

void WashTemplate::addRedMainStatus(){
    addNeutralMainStatus();
}

void WashTemplate::addBlueMainStatus(){
    addNeutralMainStatus();
}

void WashTemplate::addYellowMainStatus(){
    addNeutralMainStatus();
}

void WashTemplate::addGreenMainStatus(){
    addNeutralMainStatus();
}

int WashTemplate::calculateSoul(){
    int cost = (int)cardPower/2;
    cost += cardCostOffset;
    cost += LLMath::diceRoll((int)cardPower/3, 1);
    return cost;
}
