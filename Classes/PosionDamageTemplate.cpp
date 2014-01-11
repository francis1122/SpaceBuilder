//
//  PosionDamageTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/4/14.
//
//

#include "PosionDamageTemplate.h"

#include "Statuses.h"
#include "CardSprite.h"
#include "Targets.h"


const std::string PosionDamageTemplate::CLASS_NAME = "PosionDamageTemplate";

void PosionDamageTemplate::createCardTargets(){
    CardTargets *cardTargets = new MonsterTargets();
    //DrawCard_DiscardCard
    
    cardTargets->init();
    createdCard->cardTargets = cardTargets;
}

#pragma mark - augmentation


void PosionDamageTemplate::addNeutralAugmentationStatus(){
    
}

void PosionDamageTemplate::addRedAugmentationStatus(){
    
}

void PosionDamageTemplate::addBlueAugmentationStatus(){
    
}

void PosionDamageTemplate::addYellowAugmentationStatus(){
    
}

void PosionDamageTemplate::addPurpleAugmentationStatus(){
    
}

#pragma mark - additional cost


void PosionDamageTemplate::addNeutralAdditionalCost(){
}

void PosionDamageTemplate::addRedAdditionalCost(){
}

void PosionDamageTemplate::addBlueAdditionalCost(){
}

void PosionDamageTemplate::addYellowAdditionalCost(){
}

void PosionDamageTemplate::addPurpleAdditionalCost(){
}

#pragma mark - main status

void PosionDamageTemplate::addNeutralMainStatus(){
    int attack = (int)cardPower/2 + LLMath::diceRoll((int)cardPower/4, 3);
    
    MonsterHealthOffsetDurationStatus *status = new MonsterHealthOffsetDurationStatus();
    status->initWithHealthOffset(-attack, 999);
    createdCard->cardTargets->statuses->addObject(status);
    createdCard->setupDamageCard(attack);
    
    mainDescription = CCString::createWithFormat("Burn");
    
}

void PosionDamageTemplate::addRedMainStatus(){
    addNeutralMainStatus();
}

void PosionDamageTemplate::addBlueMainStatus(){
    addNeutralMainStatus();
}

void PosionDamageTemplate::addYellowMainStatus(){
    addNeutralMainStatus();
}

void PosionDamageTemplate::addPurpleMainStatus(){
    addNeutralMainStatus();
}

#pragma mark -