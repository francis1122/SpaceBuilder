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


void SoulGainTemplate::createCardTargets(CardSprite *card){
    CardTargets *cardTargets = new PlayAreaTargets();
    cardTargets->initWithCardSprite(card);
    createdCard->cardTargets = cardTargets;
    preemptiveBounus = 0;
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
    int rand = arc4random()%2;
    if(rand == 0){
        //killing blow augmentation
        
        int soul = cardPower/3;
        powerLevel -= cardPower/2;
        cardCostOffset += cardPower/4;
        preemptiveBounus = soul;
        augmentationDescription = CCString::createWithFormat("Preemptive %i", soul);
    }
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
    int soulGain = (int)cardPower/4 + LLMath::diceRoll((int)cardPower/6, 1);
    GainSoulStatus *status = new GainSoulStatus();
    status->initWithSoulGain(soulGain);
    status->preemptiveBonus = preemptiveBounus;
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


