//
//  DrawDiscardTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/3/14.
//
//

#include "DrawDiscardTemplate.h"


#include "Statuses.h"
#include "CardSprite.h"
#include "Targets.h"


const std::string DrawDiscardTemplate::CLASS_NAME = "DrawDiscardTemplate";

void DrawDiscardTemplate::createCardTargets(){
    CardTargets *cardTargets = new DrawDiscardTargets();
    
    cardTargets->init();
    createdCard->cardTargets = cardTargets;
}

#pragma mark - augmentation


void DrawDiscardTemplate::addNeutralAugmentationStatus(){
    
}

void DrawDiscardTemplate::addRedAugmentationStatus(){
    
}

void DrawDiscardTemplate::addBlueAugmentationStatus(){
    
}

void DrawDiscardTemplate::addYellowAugmentationStatus(){
    
}

void DrawDiscardTemplate::addPurpleAugmentationStatus(){
    
}

#pragma mark - additional cost


void DrawDiscardTemplate::addNeutralAdditionalCost(){
}

void DrawDiscardTemplate::addRedAdditionalCost(){
}

void DrawDiscardTemplate::addBlueAdditionalCost(){
}

void DrawDiscardTemplate::addYellowAdditionalCost(){
}

void DrawDiscardTemplate::addPurpleAdditionalCost(){
}

#pragma mark - main status

void DrawDiscardTemplate::addNeutralMainStatus(){
    
    int drawCardAmount = 2;
    int discardAmount = 1;
    createdCard->cardTargets->targetAmount = 1;
    DrawCardStatus *status = new DrawCardStatus();
    status->initWithDrawAmount(2);
    createdCard->cardTargets->initialStatuses->addObject(status);
    mainDescription = CCString::createWithFormat("Draw %i Cards, discard %i Card", drawCardAmount, discardAmount);
    createdCard->setCardType(Spell);
    
    GainActionStatus *statusAction = new GainActionStatus();
    Action *actionTwo = new Action();
    actionTwo->init(Neutral);
    actionsGained->addObject(actionTwo);
    statusAction->initWithActionGain(actionsGained);
    createdCard->cardTargets->initialStatuses->addObject(statusAction);
    
    
    cardCostOffset = -2.0;
}

void DrawDiscardTemplate::addRedMainStatus(){
    addNeutralMainStatus();
}

void DrawDiscardTemplate::addBlueMainStatus(){
    addNeutralMainStatus();
}

void DrawDiscardTemplate::addYellowMainStatus(){
    addNeutralMainStatus();
}

void DrawDiscardTemplate::addPurpleMainStatus(){
    addNeutralMainStatus();
}

#pragma mark -

