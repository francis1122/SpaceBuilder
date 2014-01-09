//
//  SoulGainTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 12/10/13.
//
//

#include "SoulGainTemplate.h"
#include "Statuses.h"
#include "CardSprite.h"
#include "CardTargets.h"

const std::string SoulGainTemplate::CLASS_NAME = "SoulGainTemplate";

#pragma mark - augmentation

void SoulGainTemplate::addNeutralAugmentationStatus(){
    
}

void SoulGainTemplate::addRedAugmentationStatus(){
    
}

void SoulGainTemplate::addBlueAugmentationStatus(){
    
}

void SoulGainTemplate::addYellowAugmentationStatus(){
    
}

void SoulGainTemplate::addPurpleAugmentationStatus(){
    
}

#pragma mark - additional cost


void SoulGainTemplate::addNeutralAdditionalCost(){
}

void SoulGainTemplate::addRedAdditionalCost(){
}

void SoulGainTemplate::addBlueAdditionalCost(){
}

void SoulGainTemplate::addYellowAdditionalCost(){
}

void SoulGainTemplate::addPurpleAdditionalCost(){
}


#pragma mark - main status

void SoulGainTemplate::addNeutralMainStatus(){
    createdCard->cardTargets->targetingType = PlayArea;
    
//    cardPower -= LLMath::getIntValue(cardPower/3);
    soulGain = (int)cardPower/2 + LLMath::diceRoll((int)cardPower/3, 3);
    GainSoulStatus *status = new GainSoulStatus();
    status->initWithSoulGain(cardPower);
    createdCard->cardTargets->statuses->addObject(status);
    createdCard->setupSoulGainCard(cardPower);
}

void SoulGainTemplate::addRedMainStatus(){
    addNeutralMainStatus();
}

void SoulGainTemplate::addBlueMainStatus(){
    addNeutralMainStatus();
}

void SoulGainTemplate::addYellowMainStatus(){
    addNeutralMainStatus();
}

void SoulGainTemplate::addPurpleMainStatus(){
    addNeutralMainStatus();
}

#pragma mark -


