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
#include "Targets.h"
#include "Action.h"


const std::string ActionGainTemplate::CLASS_NAME = "ActionGainTemplate";

void ActionGainTemplate::createCardTargets(){
    CardTargets *cardTargets = new PlayAreaTargets();
    cardTargets->init();
    createdCard->cardTargets = cardTargets;
}

#pragma mark - augmentation


void ActionGainTemplate::addNeutralAugmentationStatus(){
    
}

void ActionGainTemplate::addRedAugmentationStatus(){
    
}

void ActionGainTemplate::addBlueAugmentationStatus(){
    
}

void ActionGainTemplate::addYellowAugmentationStatus(){
    
}

void ActionGainTemplate::addGreenAugmentationStatus(){
    
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

void ActionGainTemplate::addGreenAdditionalCost(){
}


#pragma mark - main status



void ActionGainTemplate::addNeutralMainStatus(){
    
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

void ActionGainTemplate::addGreenMainStatus(){
    createdCard->cardTargets->targetingType = PlayArea;
    

    GainActionStatus *status = new GainActionStatus();
    Action *actionOne = new Action();
    actionOne->init(Neutral);
    actionsGained->addObject(actionOne);
    Action *actionTwo = new Action();
    actionTwo->init(Green);
    actionsGained->addObject(actionTwo);
    status->initWithActionGain(actionsGained);
    createdCard->cardTargets->statuses->addObject(status);
    createdCard->setCardType(Spell);
}

#pragma mark -



