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

void DrawDiscardTemplate::addGreenAugmentationStatus(){
    
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

void DrawDiscardTemplate::addGreenAdditionalCost(){
}

#pragma mark - main status

void DrawDiscardTemplate::addNeutralMainStatus(){
    
    int drawCardAmount = (int)(cardPower/10);
    int discardAmount = drawCardAmount;
    createdCard->cardTargets->targetAmount = drawCardAmount;
    DrawCardStatus *status = new DrawCardStatus();
    status->initWithDrawAmount(drawCardAmount);
    createdCard->cardTargets->initialStatuses->addObject(status);
    mainDescription = CCString::createWithFormat("Draw %i Cards, discard %i Card", drawCardAmount, discardAmount);
    createdCard->setCardType(Spell);
    
    GainActionStatus *statusAction = new GainActionStatus();
    Action *actionTwo = new Action();
    actionTwo->init(Neutral);
    actionsGained->addObject(actionTwo);
    statusAction->initWithActionGain(actionsGained);
    createdCard->cardTargets->initialStatuses->addObject(statusAction);
    
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

void DrawDiscardTemplate::addGreenMainStatus(){
    addNeutralMainStatus();
}

#pragma mark -

