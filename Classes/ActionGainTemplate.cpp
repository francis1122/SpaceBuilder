//
//  ActionGainTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 12/10/13.
//
//

#include "ActionGainTemplate.h"
#include "Statuses.h"
#include "CardSprite.h"
#include "CardTargets.h"
#include "Action.h"


const std::string ActionGainTemplate::CLASS_NAME = "ActionGainTemplate";


#pragma mark - augmentation


void ActionGainTemplate::addNeutralAugmentationStatus(){
    
}

void ActionGainTemplate::addRedAugmentationStatus(){
    
}

void ActionGainTemplate::addBlueAugmentationStatus(){
    
}

void ActionGainTemplate::addYellowAugmentationStatus(){
    
}

void ActionGainTemplate::addPurpleAugmentationStatus(){
    
}

#pragma mark - additional cost


void ActionGainTemplate::addNeutralAdditionalCost(){
}

void ActionGainTemplate::addRedAdditionalCost(){
}

void ActionGainTemplate::addBlueAdditionalCost(){
}

void ActionGainTemplate::addYellowAdditionalCost(){
}

void ActionGainTemplate::addPurpleAdditionalCost(){
}


#pragma mark - main status



void ActionGainTemplate::addNeutralMainStatus(){
    createdCard->cardTargets->targetingType = PlayArea;
    createdCard->cardTargets->isTargetRequired = false;
    
    GainActionStatus *status = new GainActionStatus();
    Action *actionOne = new Action();
    actionOne->init(Neutral);
    actionsGained->addObject(actionOne);
    Action *actionTwo = new Action();
    actionTwo->init(Neutral);
    actionsGained->addObject(actionTwo);
    status->initWithActionGain(actionsGained);
    createdCard->cardTargets->statuses->addObject(status);
    createdCard->setCardType(Spell);
}

void ActionGainTemplate::addRedMainStatus(){
    createdCard->cardTargets->targetingType = PlayArea;
    createdCard->cardTargets->isTargetRequired = false;
    
    GainActionStatus *status = new GainActionStatus();
    Action *actionOne = new Action();
    actionOne->init(Red);
    actionsGained->addObject(actionOne);
    Action *actionTwo = new Action();
    actionTwo->init(Red);
    actionsGained->addObject(actionTwo);
    status->initWithActionGain(actionsGained);
    createdCard->cardTargets->statuses->addObject(status);
    createdCard->setCardType(Spell);
}

void ActionGainTemplate::addBlueMainStatus(){
    createdCard->cardTargets->targetingType = PlayArea;
    createdCard->cardTargets->isTargetRequired = false;
    

    GainActionStatus *status = new GainActionStatus();
    Action *actionOne = new Action();
    actionOne->init(Neutral);
    actionsGained->addObject(actionOne);
    Action *actionTwo = new Action();
    actionTwo->init(Neutral);
    actionsGained->addObject(actionTwo);
    status->initWithActionGain(actionsGained);
    createdCard->cardTargets->statuses->addObject(status);
    createdCard->setCardType(Spell);
}

void ActionGainTemplate::addYellowMainStatus(){
    createdCard->cardTargets->targetingType = PlayArea;
    createdCard->cardTargets->isTargetRequired = false;
    

    GainActionStatus *status = new GainActionStatus();
    Action *actionOne = new Action();
    actionOne->init(Neutral);
    actionsGained->addObject(actionOne);
    Action *actionTwo = new Action();
    actionTwo->init(Yellow);
    actionsGained->addObject(actionTwo);
    status->initWithActionGain(actionsGained);
    createdCard->cardTargets->statuses->addObject(status);
    createdCard->setCardType(Spell);
}

void ActionGainTemplate::addPurpleMainStatus(){
    createdCard->cardTargets->targetingType = PlayArea;
    createdCard->cardTargets->isTargetRequired = false;
    

    GainActionStatus *status = new GainActionStatus();
    Action *actionOne = new Action();
    actionOne->init(Neutral);
    actionsGained->addObject(actionOne);
    Action *actionTwo = new Action();
    actionTwo->init(Purple);
    actionsGained->addObject(actionTwo);
    status->initWithActionGain(actionsGained);
    createdCard->cardTargets->statuses->addObject(status);
    createdCard->setCardType(Spell);
}

#pragma mark -


int ActionGainTemplate::calculateSoul(){
    int cost = (int)cardPower/4;
    cost += cardCostOffset;
    cost += LLMath::diceRoll((int)cardPower/2, 3);
    return cost;
}

