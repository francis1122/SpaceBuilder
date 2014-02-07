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

void PosionDamageTemplate::createCardTargets(CardSprite *card){
    CardTargets *cardTargets = new MonsterTargets();
    //DrawCard_DiscardCard
    
    cardTargets->initWithCardSprite(card);
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

void PosionDamageTemplate::addGreenAugmentationStatus(){
    
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

void PosionDamageTemplate::addGreenAdditionalCost(){
}

#pragma mark - main status

void PosionDamageTemplate::addNeutralMainStatus(){
    int attack = (int)cardPower/8 + LLMath::diceRoll((int)cardPower/8, 1);
    
    MonsterHealthOffsetDurationStatus *status = new MonsterHealthOffsetDurationStatus();
    status->initWithHealthOffset(-attack, 999);
    createdCard->cardTargets->statuses->addObject(status);
    createdCard->setupDamageCard(attack);
    
    mainDescription = CCString::createWithFormat("Posion");
    
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

void PosionDamageTemplate::addGreenMainStatus(){
    addNeutralMainStatus();
}

#pragma mark -