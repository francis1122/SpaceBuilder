//
//  DiscardForActionsTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 2/20/14.
//
//

#include "DiscardForActionsTemplate.h"


#include "Statuses.h"
#include "CardSprite.h"
#include "Targets.h"


const std::string DiscardForActionsTemplate::CLASS_NAME = "DiscardForActionsTemplate";

void DiscardForActionsTemplate::createCardTargets(CardSprite *card){
    CardTargets *cardTargets = new DrawDiscardTargets();
    
    cardTargets->initWithCardSprite(card);
    createdCard->cardTargets = cardTargets;
}

#pragma mark - augmentation


void DiscardForActionsTemplate::addNeutralAugmentationStatus(){
    
}

void DiscardForActionsTemplate::addRedAugmentationStatus(){
    
}

void DiscardForActionsTemplate::addBlueAugmentationStatus(){
    
}

void DiscardForActionsTemplate::addYellowAugmentationStatus(){
    
}

void DiscardForActionsTemplate::addGreenAugmentationStatus(){
    
}

#pragma mark - additional cost


void DiscardForActionsTemplate::addNeutralAdditionalCost(){
}

void DiscardForActionsTemplate::addRedAdditionalCost(){
}

void DiscardForActionsTemplate::addBlueAdditionalCost(){
}

void DiscardForActionsTemplate::addYellowAdditionalCost(){
}

void DiscardForActionsTemplate::addGreenAdditionalCost(){
}

#pragma mark - main status

void DiscardForActionsTemplate::addNeutralMainStatus(){
    
    int discardAmount = 2;
    createdCard->cardTargets->targetAmount = discardAmount;
    mainDescription = CCString::createWithFormat("Discard %i cards", discardAmount);
    createdCard->setCardType(Spell);
    
    GainActionStatus *statusAction = new GainActionStatus();
    Action *actionTwo = new Action();
    actionTwo->init(Neutral);
    actionsGained->addObject(actionTwo);
    Action *action = new Action();
    action->init(Neutral);
    actionsGained->addObject(action);
    statusAction->initWithActionGain(actionsGained);
    createdCard->cardTargets->statuses->addObject(statusAction);
    
}

void DiscardForActionsTemplate::addRedMainStatus(){
    addNeutralMainStatus();
}

void DiscardForActionsTemplate::addBlueMainStatus(){
    addNeutralMainStatus();
}

void DiscardForActionsTemplate::addYellowMainStatus(){
    addNeutralMainStatus();
}

void DiscardForActionsTemplate::addGreenMainStatus(){
    addNeutralMainStatus();
}

#pragma mark -
