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
    createdCard->cardTargets->targetingType = PlayArea;
    
    drawCardAmount = 2;
    DrawCardStatus *status = new DrawCardStatus();
    status->initWithDrawAmount(2);
    createdCard->cardTargets->statuses->addObject(status);
    mainDescription = CCString::createWithFormat("Draw %i Cards", drawCardAmount);
    createdCard->setCardType(Spell);
}

void DrawCardTemplate::addRedMainStatus(){
    addNeutralMainStatus();
}

void DrawCardTemplate::addBlueMainStatus(){
    addNeutralMainStatus();
}

void DrawCardTemplate::addYellowMainStatus(){
    addNeutralMainStatus();
}

void DrawCardTemplate::addGreenMainStatus(){
    addNeutralMainStatus();
}

#pragma mark -



