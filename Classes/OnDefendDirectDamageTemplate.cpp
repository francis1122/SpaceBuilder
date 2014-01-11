//
//  OnDefendDirectDamageTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/9/14.
//
//

#include "OnDefendDirectDamageTemplate.h"

#include "Statuses.h"
#include "CardSprite.h"
#include "Targets.h"


const std::string OnDefendDirectDamageTemplate::CLASS_NAME = "OnDefendDirectDamageTemplate";

void OnDefendDirectDamageTemplate::createCardTargets(){
    CardTargets *cardTargets = new MonsterTargets();
    //DrawCard_DiscardCard
    
    cardTargets->init();
    createdCard->cardTargets = cardTargets;
}

#pragma mark - augmentation


void OnDefendDirectDamageTemplate::addNeutralAugmentationStatus(){
    
}

void OnDefendDirectDamageTemplate::addRedAugmentationStatus(){
    
}

void OnDefendDirectDamageTemplate::addBlueAugmentationStatus(){
    
}

void OnDefendDirectDamageTemplate::addYellowAugmentationStatus(){
    
}

void OnDefendDirectDamageTemplate::addPurpleAugmentationStatus(){
    
}

#pragma mark - additional cost


void OnDefendDirectDamageTemplate::addNeutralAdditionalCost(){
}

void OnDefendDirectDamageTemplate::addRedAdditionalCost(){
}

void OnDefendDirectDamageTemplate::addBlueAdditionalCost(){
}

void OnDefendDirectDamageTemplate::addYellowAdditionalCost(){
}

void OnDefendDirectDamageTemplate::addPurpleAdditionalCost(){
}

#pragma mark - main status

void OnDefendDirectDamageTemplate::addNeutralMainStatus(){
    int attack = (int)cardPower/4 + LLMath::diceRoll((int)cardPower/3, 3);
    
    MonsterHealthOffsetStatus *status = new MonsterHealthOffsetStatus();
    status->initWithHealthOffset(-attack);
    createdCard->cardTargets->statuses->addObject(status);
    createdCard->setupDamageCard(attack);
    
    
    mainDescription = CCString::createWithFormat("On Defend");
}

void OnDefendDirectDamageTemplate::addRedMainStatus(){
    addNeutralMainStatus();
}

void OnDefendDirectDamageTemplate::addBlueMainStatus(){
    addNeutralMainStatus();
}

void OnDefendDirectDamageTemplate::addYellowMainStatus(){
    addNeutralMainStatus();
}

void OnDefendDirectDamageTemplate::addPurpleMainStatus(){
    addNeutralMainStatus();
}

#pragma mark -