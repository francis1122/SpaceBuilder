//
//  HugeHugeSoulGainTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 2/25/14.
//
//

#include "HugeSoulGainTemplate.h"
#include "Statuses.h"
#include "CardSprite.h"
#include "Targets.h"

const std::string HugeSoulGainTemplate::CLASS_NAME = "HugeSoulGainTemplate";


void HugeSoulGainTemplate::createCardTargets(CardSprite *card){
    CardTargets *cardTargets = new PlayAreaTargets();
    cardTargets->initWithCardSprite(card);
    createdCard->cardTargets = cardTargets;
    cardTargets->timesCardCanBePlayed = 1;
}

#pragma mark - augmentation

void HugeSoulGainTemplate::addNeutralAugmentationStatus(){
    
}

void HugeSoulGainTemplate::addRedAugmentationStatus(){
    
}

void HugeSoulGainTemplate::addBlueAugmentationStatus(){
    
}

void HugeSoulGainTemplate::addYellowAugmentationStatus(){
    
}

void HugeSoulGainTemplate::addGreenAugmentationStatus(){

}

#pragma mark - additional cost


void HugeSoulGainTemplate::addNeutralAdditionalCost(){
    
}

void HugeSoulGainTemplate::addRedAdditionalCost(){
    
}

void HugeSoulGainTemplate::addBlueAdditionalCost(){
    
}

void HugeSoulGainTemplate::addYellowAdditionalCost(){
    
}

void HugeSoulGainTemplate::addGreenAdditionalCost(){
    
}

#pragma mark - main status

void HugeSoulGainTemplate::addNeutralMainStatus(){
    int soulGain = 40;
    GainSoulStatus *status = new GainSoulStatus();
    status->initWithSoulGain(soulGain);
    createdCard->cardTargets->statuses->addObject(status);
    createdCard->setupSoulGainCard(soulGain);
    mainDescription = CCString::createWithFormat("One Use");
}

void HugeSoulGainTemplate::addRedMainStatus(){
    addNeutralMainStatus();
}

void HugeSoulGainTemplate::addBlueMainStatus(){
    addNeutralMainStatus();
}

void HugeSoulGainTemplate::addYellowMainStatus(){
    addNeutralMainStatus();
}

void HugeSoulGainTemplate::addGreenMainStatus(){
    addNeutralMainStatus();
}

#pragma mark -