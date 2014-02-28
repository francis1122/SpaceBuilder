//
//  LeechMonsterLifeTempalte.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 2/25/14.
//
//

#include "LeechLifeTemplate.h"
#include "Statuses.h"
#include "CardSprite.h"
#include "Targets.h"
#include "Action.h"
#include "CardGenerator.h"
#include "LLMath.h"


const std::string LeechLifeTemplate::CLASS_NAME = "LeechLifeTemplate";



void LeechLifeTemplate::createCardTargets(CardSprite *card)
{
    CardTargets *cardTargets = new MonsterTargets();
    cardTargets->initWithCardSprite(card);
    createdCard->cardTargets = cardTargets;
}

#pragma mark - augmentation


void LeechLifeTemplate::addNeutralAugmentationStatus(){
    
}

void LeechLifeTemplate::addRedAugmentationStatus(){
    
}

void LeechLifeTemplate::addBlueAugmentationStatus(){
    
}

void LeechLifeTemplate::addYellowAugmentationStatus(){
    
}

void LeechLifeTemplate::addGreenAugmentationStatus(){
    
}

#pragma mark - additional cost


void LeechLifeTemplate::addNeutralAdditionalCost()
{
}

void LeechLifeTemplate::addRedAdditionalCost()
{
}

void LeechLifeTemplate::addBlueAdditionalCost()
{
}

void LeechLifeTemplate::addYellowAdditionalCost()
{
}

void LeechLifeTemplate::addGreenAdditionalCost()
{
}

#pragma mark - main status
void LeechLifeTemplate::addNeutralMainStatus()
{
    int attack = 2 + (int)cardPower/8 + LLMath::diceRoll((int)cardPower/12, 1);
    //set limit on basic attack
    LeechMonsterLifeStatus *status = new LeechMonsterLifeStatus();
    status->initWithHealthOffset(-attack);
    createdCard->cardTargets->statuses->addObject(status);
    createdCard->setupDamageCard(attack);
    
    mainDescription = CCString::createWithFormat("Gain life equal to damage done");
}

void LeechLifeTemplate::addRedMainStatus()
{
    addNeutralMainStatus();
}

void LeechLifeTemplate::addBlueMainStatus()
{
    addNeutralMainStatus();
}

void LeechLifeTemplate::addYellowMainStatus(){
    addNeutralMainStatus();
}

void LeechLifeTemplate::addGreenMainStatus(){
    addNeutralMainStatus();
}

