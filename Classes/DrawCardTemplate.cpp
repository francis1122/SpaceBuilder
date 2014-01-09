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
#include "CardTargets.h"


const std::string DrawCardTemplate::CLASS_NAME = "DrawCardTemplate";



#pragma mark - augmentation


void DrawCardTemplate::addNeutralAugmentationStatus(){
    
}

void DrawCardTemplate::addRedAugmentationStatus(){
    
}

void DrawCardTemplate::addBlueAugmentationStatus(){
    
}

void DrawCardTemplate::addYellowAugmentationStatus(){
    
}

void DrawCardTemplate::addPurpleAugmentationStatus(){
    
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

void DrawCardTemplate::addPurpleAdditionalCost(){
}


#pragma mark - main status



void DrawCardTemplate::addNeutralMainStatus(){
    createdCard->cardTargets->targetingType = PlayArea;
    
    drawCardAmount = 2;
    DrawCardStatus *status = new DrawCardStatus();
    status->initWithDrawAmount(2);
    createdCard->cardTargets->statuses->addObject(status);
    mainDescription =CCString::createWithFormat("Draw %i Cards", drawCardAmount);
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

void DrawCardTemplate::addPurpleMainStatus(){
    addNeutralMainStatus();
}

#pragma mark -

int DrawCardTemplate::calculateSoul(){
    int cost = (int)cardPower/4;
    cost += cardCostOffset;
    cost += LLMath::diceRoll((int)cardPower/2, 3);
    return cost;
}



