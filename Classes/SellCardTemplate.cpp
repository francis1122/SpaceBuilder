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


void SellCardTemplate::createCardTargets(CardSprite *card){
    CardTargets *cardTargets = new SellCardTargets();
    cardTargets->initWithCardSprite(card);
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
    int soulGain = (int)cardPower/4 + LLMath::diceRoll((int)cardPower/6, 1);
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
    GainActionStatus *status = new GainActionStatus();
    Action *actionOne = new Action();
    actionOne->init(Neutral);
    actionsGained->addObject(actionOne);
    status->initWithActionGain(actionsGained);
    createdCard->cardTargets->statuses->addObject(status);
    createdCard->setCardType(Spell);
    mainDescription = CCString::createWithFormat("Destroy Card a Card");
}

void SellCardTemplate::addYellowMainStatus(){
    int soulGain = (int)cardPower/4 + LLMath::diceRoll((int)cardPower/6, 1);
    GainSoulStatus *status = new GainSoulStatus();
    status->initWithSoulGain(soulGain);
    createdCard->cardTargets->statuses->addObject(status);
    mainDescription = CCString::createWithFormat("Destroy Card For %i Soul", soulGain);
    createdCard->setCardType(Spell);
}

void SellCardTemplate::addGreenMainStatus(){
    int healthGain = (int)cardPower/4 + LLMath::diceRoll((int)cardPower/6, 1);
    PlayerHealthOffsetStatus *status = new PlayerHealthOffsetStatus();
    status->initWithHealthOffset(healthGain);
    createdCard->cardTargets->statuses->addObject(status);
    mainDescription = CCString::createWithFormat("Destroy Card For %i Health", healthGain);
    createdCard->setCardType(Spell);
}

#pragma mark -