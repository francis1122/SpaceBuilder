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
#include "Targets.h"
#include "Targets.h"
const std::string SoulGainTemplate::CLASS_NAME = "SoulGainTemplate";


void SoulGainTemplate::createCardTargets(){
    CardTargets *cardTargets = new PlayAreaTargets();
    cardTargets->init();
    createdCard->cardTargets = cardTargets;
}

#pragma mark - augmentation

void SoulGainTemplate::addNeutralAugmentationStatus(){
    
}

void SoulGainTemplate::addRedAugmentationStatus(){
    
}

void SoulGainTemplate::addBlueAugmentationStatus(){
    
}

void SoulGainTemplate::addYellowAugmentationStatus(){
    
}

void SoulGainTemplate::addGreenAugmentationStatus(){
    
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

void SoulGainTemplate::addGreenAdditionalCost(){
    
}


#pragma mark - main status

void SoulGainTemplate::addNeutralMainStatus(){
    
//    cardPower -= LLMath::getIntValue(cardPower/3);
    int soulGain = (int)cardPower/6 + LLMath::diceRoll((int)cardPower/3, 1);
    GainSoulStatus *status = new GainSoulStatus();
    status->initWithSoulGain(soulGain);
    createdCard->cardTargets->statuses->addObject(status);
    createdCard->setupSoulGainCard(soulGain);
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

void SoulGainTemplate::addGreenMainStatus(){
    addNeutralMainStatus();
}

#pragma mark -


