//
//  HugeLifeGainTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 2/27/14.
//
//

#include "HugeLifeGainTemplate.h"
#include "Statuses.h"
#include "CardSprite.h"
#include "Targets.h"

const std::string HugeLifeGainTemplate::CLASS_NAME = "HugeLifeGainTemplate";


void HugeLifeGainTemplate::createCardTargets(CardSprite *card){
    CardTargets *cardTargets = new PlayAreaTargets();
    cardTargets->initWithCardSprite(card);
    createdCard->cardTargets = cardTargets;
    cardTargets->timesCardCanBePlayed = 1;
}

#pragma mark - augmentation

void HugeLifeGainTemplate::addNeutralAugmentationStatus(){
    
}

void HugeLifeGainTemplate::addRedAugmentationStatus(){
    
}

void HugeLifeGainTemplate::addBlueAugmentationStatus(){
    
}

void HugeLifeGainTemplate::addYellowAugmentationStatus(){
    
}

void HugeLifeGainTemplate::addGreenAugmentationStatus(){
    
}

#pragma mark - additional cost


void HugeLifeGainTemplate::addNeutralAdditionalCost(){
    
}

void HugeLifeGainTemplate::addRedAdditionalCost(){
    
}

void HugeLifeGainTemplate::addBlueAdditionalCost(){
    
}

void HugeLifeGainTemplate::addYellowAdditionalCost(){
    
}

void HugeLifeGainTemplate::addGreenAdditionalCost(){
    
}

#pragma mark - main status

void HugeLifeGainTemplate::addNeutralMainStatus(){
    int healthGain = 40;
    PlayerHealthOffsetStatus  *status = new PlayerHealthOffsetStatus();
    status->initWithHealthOffset(healthGain);
    createdCard->cardTargets->statuses->addObject(status);
    
//    createdCard->setupSoulGainCard(soulGain);
    mainDescription = CCString::createWithFormat("One Use\r Gain %i life", healthGain);
}

void HugeLifeGainTemplate::addRedMainStatus(){
    addNeutralMainStatus();
}

void HugeLifeGainTemplate::addBlueMainStatus(){
    addNeutralMainStatus();
}

void HugeLifeGainTemplate::addYellowMainStatus(){
    addNeutralMainStatus();
}

void HugeLifeGainTemplate::addGreenMainStatus(){
    addNeutralMainStatus();
}
