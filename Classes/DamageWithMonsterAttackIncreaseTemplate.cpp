//
//  DamageWithMonsterAttackIncreaseTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 2/25/14.
//
//

#include "DamageWithMonsterAttackIncreaseTemplate.h"
#include "Statuses.h"
#include "CardSprite.h"
#include "Targets.h"
#include "Action.h"
#include "CardGenerator.h"
#include "LLMath.h"


const std::string DamageWithMonsterAttackIncreaseTemplate::CLASS_NAME = "DamageWithMonsterAttackIncreaseTemplate";



void DamageWithMonsterAttackIncreaseTemplate::createCardTargets(CardSprite *card)
{
    CardTargets *cardTargets = new MonsterTargets();
    cardTargets->initWithCardSprite(card);
    createdCard->cardTargets = cardTargets;
}

#pragma mark - augmentation


void DamageWithMonsterAttackIncreaseTemplate::addNeutralAugmentationStatus(){
    
}

void DamageWithMonsterAttackIncreaseTemplate::addRedAugmentationStatus(){
    
}

void DamageWithMonsterAttackIncreaseTemplate::addBlueAugmentationStatus(){
    
}

void DamageWithMonsterAttackIncreaseTemplate::addYellowAugmentationStatus(){
    
}

void DamageWithMonsterAttackIncreaseTemplate::addGreenAugmentationStatus(){
    
}

#pragma mark - additional cost


void DamageWithMonsterAttackIncreaseTemplate::addNeutralAdditionalCost()
{
}

void DamageWithMonsterAttackIncreaseTemplate::addRedAdditionalCost()
{
}

void DamageWithMonsterAttackIncreaseTemplate::addBlueAdditionalCost()
{
}

void DamageWithMonsterAttackIncreaseTemplate::addYellowAdditionalCost()
{
}

void DamageWithMonsterAttackIncreaseTemplate::addGreenAdditionalCost()
{
}

#pragma mark - main status
void DamageWithMonsterAttackIncreaseTemplate::addNeutralMainStatus()
{
    int attack = (int)cardPower/3 + LLMath::diceRoll((int)cardPower/6, 1);
    MonsterHealthOffsetStatus *status = new MonsterHealthOffsetStatus();
    status->initWithHealthOffset(-attack);
    createdCard->cardTargets->statuses->addObject(status);
    createdCard->setupDamageCard(attack);
    
    MonsterAttackOffsetStatus *attackOffsetStatus = new MonsterAttackOffsetStatus();
    int monsterAttackOffset = (int)cardPower/11 + LLMath::diceRoll((int)cardPower/20, 1);
    attackOffsetStatus->initWithAttackOffset(monsterAttackOffset);
    createdCard->cardTargets->statuses->addObject(attackOffsetStatus);
    
    mainDescription = CCString::createWithFormat("Increase monster's attack by %i", monsterAttackOffset);
}

void DamageWithMonsterAttackIncreaseTemplate::addRedMainStatus()
{
    addNeutralMainStatus();
}

void DamageWithMonsterAttackIncreaseTemplate::addBlueMainStatus()
{
    addNeutralMainStatus();
}

void DamageWithMonsterAttackIncreaseTemplate::addYellowMainStatus(){
    addNeutralMainStatus();
}

void DamageWithMonsterAttackIncreaseTemplate::addGreenMainStatus(){
    addNeutralMainStatus();
}



