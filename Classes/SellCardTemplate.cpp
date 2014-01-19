//
//  SellCardTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/17/14.
//
//

#include "SellCardTemplate.h"
#include "Statuses.h"
#include "CardSprite.h"
#include "Targets.h"
#include "Targets.h"
const std::string SellCardTemplate::CLASS_NAME = "SellCardTemplate";


void SellCardTemplate::createCardTargets(){
    CardTargets *cardTargets = new SellCardTargets();
    cardTargets->init();
    createdCard->cardTargets = cardTargets;
}

#pragma mark - augmentation

void SellCardTemplate::addNeutralAugmentationStatus(){
    
}

void SellCardTemplate::addRedAugmentationStatus(){
    
}

void SellCardTemplate::addBlueAugmentationStatus(){
    
}

void SellCardTemplate::addYellowAugmentationStatus(){
    
}

void SellCardTemplate::addGreenAugmentationStatus(){
    
}

#pragma mark - additional cost


void SellCardTemplate::addNeutralAdditionalCost(){
    
}

void SellCardTemplate::addRedAdditionalCost(){
    
}

void SellCardTemplate::addBlueAdditionalCost(){
    
}

void SellCardTemplate::addYellowAdditionalCost(){
    
}

void SellCardTemplate::addGreenAdditionalCost(){
    
}


#pragma mark - main status

void SellCardTemplate::addNeutralMainStatus(){
    
    //    cardPower -= LLMath::getIntValue(cardPower/3);
    int soulGain = (int)cardPower/8 + LLMath::diceRoll((int)cardPower/3, 1);
    GainSoulStatus *status = new GainSoulStatus();
    status->initWithSoulGain(soulGain);
    createdCard->cardTargets->statuses->addObject(status);
    mainDescription = CCString::createWithFormat("Destroy Card For %i Soul", soulGain);
    createdCard->setCardType(Spell);

}

void SellCardTemplate::addRedMainStatus(){
    addNeutralMainStatus();
}

void SellCardTemplate::addBlueMainStatus(){
    addNeutralMainStatus();
}

void SellCardTemplate::addYellowMainStatus(){
    addNeutralMainStatus();
}

void SellCardTemplate::addGreenMainStatus(){
    addNeutralMainStatus();
}

#pragma mark -