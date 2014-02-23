//
//  DrawCardTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 12/10/13.
//
//

#include "DrawCardTemplate.h"
#include "Statuses.h"
#include "CardSprite.h"
#include "Targets.h"


const std::string DrawCardTemplate::CLASS_NAME = "DrawCardTemplate";

void DrawCardTemplate::createCardTargets(CardSprite *card)
{
    CardTargets *cardTargets = new PlayAreaTargets();
    cardTargets->initWithCardSprite(card);
    createdCard->cardTargets = cardTargets;
}


#pragma mark - augmentation


void DrawCardTemplate::addNeutralAugmentationStatus(){
    
}

void DrawCardTemplate::addRedAugmentationStatus(){
    
}

void DrawCardTemplate::addBlueAugmentationStatus(){
    
}

void DrawCardTemplate::addYellowAugmentationStatus(){
    
}

void DrawCardTemplate::addGreenAugmentationStatus(){
    
}

#pragma mark - additional cost


void DrawCardTemplate::addNeutralAdditionalCost(){
}

void DrawCardTemplate::addRedAdditionalCost(){
}

void DrawCardTemplate::addBlueAdditionalCost(){
}

void DrawCardTemplate::addYellowAdditionalCost(){
}

void DrawCardTemplate::addGreenAdditionalCost(){
}


#pragma mark - main status



void DrawCardTemplate::addNeutralMainStatus(){
    drawCardAmount = 1 + cardPower/20;
    DrawCardStatus *status = new DrawCardStatus();
    status->initWithDrawAmount(drawCardAmount);
    createdCard->cardTargets->statuses->addObject(status);
    mainDescription = CCString::createWithFormat("Draw %i Cards", drawCardAmount);
    createdCard->setCardType(Spell);
}

void DrawCardTemplate::addRedMainStatus(){
    addNeutralMainStatus();
}

void DrawCardTemplate::addBlueMainStatus(){
    
    //gain an action
    GainActionStatus *statusGainAction = new GainActionStatus();
    Action *actionTwo = new Action();
    actionTwo->init(Blue);
    actionsGained->addObject(actionTwo);
    statusGainAction->initWithActionGain(actionsGained);
    createdCard->cardTargets->statuses->addObject(statusGainAction);
    
    //draw some cards
    drawCardAmount = 1 + cardPower/20;
    DrawCardStatus *status = new DrawCardStatus();
    status->initWithDrawAmount(drawCardAmount);
    createdCard->cardTargets->statuses->addObject(status);
    mainDescription = CCString::createWithFormat("Draw %i Cards", drawCardAmount);
    createdCard->setCardType(Spell);
}

void DrawCardTemplate::addYellowMainStatus(){
    addNeutralMainStatus();
}

void DrawCardTemplate::addGreenMainStatus(){
    addNeutralMainStatus();
}

#pragma mark -



