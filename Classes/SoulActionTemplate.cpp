//
//  SoulActionTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 2/21/14.
//
//

#include "SoulActionTemplate.h"
#include "Statuses.h"
#include "CardSprite.h"
#include "Targets.h"
#include "Targets.h"
const std::string SoulActionTemplate::CLASS_NAME = "SoulActionTemplate";


void SoulActionTemplate::createCardTargets(CardSprite *card){
    CardTargets *cardTargets = new PlayAreaTargets();
    cardTargets->initWithCardSprite(card);
    createdCard->cardTargets = cardTargets;
    preemptiveBounus = 0;
}

#pragma mark - augmentation

void SoulActionTemplate::addNeutralAugmentationStatus(){
    
}

void SoulActionTemplate::addRedAugmentationStatus(){
    GainActionStatus *status = new GainActionStatus();
    Action *actionOne = new Action();
    actionOne->init(Red);
    actionsGained->addObject(actionOne);
    status->initWithActionGain(actionsGained);
    createdCard->cardTargets->statuses->addObject(status);

}

void SoulActionTemplate::addBlueAugmentationStatus(){
    GainActionStatus *status = new GainActionStatus();
    Action *actionOne = new Action();
    actionOne->init(Blue);
    actionsGained->addObject(actionOne);
    status->initWithActionGain(actionsGained);
    createdCard->cardTargets->statuses->addObject(status);

}

void SoulActionTemplate::addYellowAugmentationStatus(){
    GainActionStatus *status = new GainActionStatus();
    Action *actionOne = new Action();
    actionOne->init(Yellow);
    actionsGained->addObject(actionOne);
    status->initWithActionGain(actionsGained);
    createdCard->cardTargets->statuses->addObject(status);
    
}

void SoulActionTemplate::addGreenAugmentationStatus(){
    GainActionStatus *status = new GainActionStatus();
    Action *actionOne = new Action();
    actionOne->init(Green);
    actionsGained->addObject(actionOne);
    status->initWithActionGain(actionsGained);
    createdCard->cardTargets->statuses->addObject(status);
}

#pragma mark - additional cost


void SoulActionTemplate::addNeutralAdditionalCost(){
    
}

void SoulActionTemplate::addRedAdditionalCost(){
    
}

void SoulActionTemplate::addBlueAdditionalCost(){
    
}

void SoulActionTemplate::addYellowAdditionalCost(){
    
}

void SoulActionTemplate::addGreenAdditionalCost(){
    
}


#pragma mark - main status

void SoulActionTemplate::addNeutralMainStatus(){
    int soulGain = (int)cardPower/6 + LLMath::diceRoll((int)cardPower/8, 1);
    GainSoulStatus *status = new GainSoulStatus();
    status->initWithSoulGain(soulGain);
    createdCard->cardTargets->statuses->addObject(status);
    createdCard->setupSoulGainCard(soulGain);
}

void SoulActionTemplate::addRedMainStatus(){
    addNeutralMainStatus();
}

void SoulActionTemplate::addBlueMainStatus(){
    addNeutralMainStatus();
}

void SoulActionTemplate::addYellowMainStatus(){
    addNeutralMainStatus();
}

void SoulActionTemplate::addGreenMainStatus(){
    addNeutralMainStatus();
}

#pragma mark -