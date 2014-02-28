//
//  DamageForHealthTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 2/25/14.
//
//

#include "DamageForHealthTemplate.h"
#include "Statuses.h"
#include "CardSprite.h"
#include "Targets.h"
#include "Action.h"
#include "CardGenerator.h"
#include "LLMath.h"


const std::string DamageForHealthTemplate::CLASS_NAME = "DamageForHealthTemplate";



void DamageForHealthTemplate::createCardTargets(CardSprite *card)
{
    CardTargets *cardTargets = new MonsterTargets();
    cardTargets->initWithCardSprite(card);
    createdCard->cardTargets = cardTargets;
}

#pragma mark - augmentation


void DamageForHealthTemplate::addNeutralAugmentationStatus(){
    
}

void DamageForHealthTemplate::addRedAugmentationStatus(){
    
}

void DamageForHealthTemplate::addBlueAugmentationStatus(){
    
}

void DamageForHealthTemplate::addYellowAugmentationStatus(){
    
}

void DamageForHealthTemplate::addGreenAugmentationStatus(){
    
}

#pragma mark - additional cost


void DamageForHealthTemplate::addNeutralAdditionalCost()
{
}

void DamageForHealthTemplate::addRedAdditionalCost()
{
}

void DamageForHealthTemplate::addBlueAdditionalCost()
{
}

void DamageForHealthTemplate::addYellowAdditionalCost()
{
}

void DamageForHealthTemplate::addGreenAdditionalCost()
{
}

#pragma mark - main status
void DamageForHealthTemplate::addNeutralMainStatus()
{
    int attack = 1 + (int)cardPower/3 + LLMath::diceRoll((int)cardPower/7, 1);
    //set limit on basic attack
    MonsterHealthOffsetStatus *status = new MonsterHealthOffsetStatus();
    status->initWithHealthOffset(-attack);
    createdCard->cardTargets->statuses->addObject(status);
    createdCard->setupDamageCard(attack);
    
    int playerDamage = 1 + (int)cardPower/10 + LLMath::diceRoll((int)cardPower/10, 1);
    PlayerHealthOffsetStatus *playerStatus = new PlayerHealthOffsetStatus();
    playerStatus->initWithHealthOffset(-playerDamage);
    createdCard->cardTargets->statuses->addObject(playerStatus);

    mainDescription = CCString::createWithFormat("Take %i damage", playerDamage);
}

void DamageForHealthTemplate::addRedMainStatus()
{
    addNeutralMainStatus();
}

void DamageForHealthTemplate::addBlueMainStatus()
{
    addNeutralMainStatus();
}

void DamageForHealthTemplate::addYellowMainStatus(){
    addNeutralMainStatus();
}

void DamageForHealthTemplate::addGreenMainStatus(){
    addNeutralMainStatus();
}

#pragma mark -

int DamageForHealthTemplate::calculateSoul(){
    int cost = (int)powerLevel/3;
    cost += cardCostOffset;
    cost += LLMath::diceRoll((int)cardPower/6, 1);
    return cost;
}

