//
//  PreemptiveDamageTemplate.m
//  RogueDeck
//
//  Created by Hunter Francis on 1/26/14.
//
//

#include "PreemptiveDamageTemplate.h"
#include "cocos2d.h"
#include "Statuses.h"
#include "CardSprite.h"
#include "Targets.h"
#include "Action.h"
#include "CardGenerator.h"
#include "LLMath.h"
USING_NS_CC;

const std::string PreemptiveDamageTemplate::CLASS_NAME = "PreemptiveDamageTemplate";



void PreemptiveDamageTemplate::createCardTargets(){
    CardTargets *cardTargets = new MonsterTargets();
    cardTargets->init();
    createdCard->cardTargets = cardTargets;
}

#pragma mark - augmentation


void PreemptiveDamageTemplate::addNeutralAugmentationStatus(){
    
}

void PreemptiveDamageTemplate::addRedAugmentationStatus(){

}

void PreemptiveDamageTemplate::addBlueAugmentationStatus(){
 
}

void PreemptiveDamageTemplate::addYellowAugmentationStatus(){

}

void PreemptiveDamageTemplate::addGreenAugmentationStatus(){

}

#pragma mark - additional cost


void PreemptiveDamageTemplate::addNeutralAdditionalCost(){
}

void PreemptiveDamageTemplate::addRedAdditionalCost(){
}

void PreemptiveDamageTemplate::addBlueAdditionalCost(){
}

void PreemptiveDamageTemplate::addYellowAdditionalCost(){
}

void PreemptiveDamageTemplate::addGreenAdditionalCost(){
}


#pragma mark - main status

void PreemptiveDamageTemplate::addNeutralMainStatus(){
    
    int attack = (int)cardPower/6 + LLMath::diceRoll((int)cardPower/3, 1);
    MonsterHealthOffsetStatus *status = new MonsterHealthOffsetStatus();
    status->initWithHealthOffset(-attack);
    createdCard->cardTargets->statuses->addObject(status);
    createdCard->setupDamageCard(attack);
}

void PreemptiveDamageTemplate::addRedMainStatus(){
    addNeutralMainStatus();
}

void PreemptiveDamageTemplate::addBlueMainStatus(){
    addNeutralMainStatus();
}

void PreemptiveDamageTemplate::addYellowMainStatus(){
    addNeutralMainStatus();
}

void PreemptiveDamageTemplate::addGreenMainStatus(){
    addNeutralMainStatus();
}

