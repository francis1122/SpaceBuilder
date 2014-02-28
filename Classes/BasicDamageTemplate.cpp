//
//  BasicDamageTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 2/11/14.
//
//

#include "BasicDamageTemplate.h"
#include "Statuses.h"
#include "CardSprite.h"
#include "Targets.h"
#include "Action.h"
#include "CardGenerator.h"
#include "LLMath.h"


const std::string BasicDamageTemplate::CLASS_NAME = "BasicDamageTemplate";



void BasicDamageTemplate::createCardTargets(CardSprite *card)
{
    CardTargets *cardTargets = new MonsterTargets();
    cardTargets->initWithCardSprite(card);
    createdCard->cardTargets = cardTargets;
}

#pragma mark - augmentation


void BasicDamageTemplate::addNeutralAugmentationStatus(){
    
}

void BasicDamageTemplate::addRedAugmentationStatus(){

}

void BasicDamageTemplate::addBlueAugmentationStatus(){

}

void BasicDamageTemplate::addYellowAugmentationStatus(){

}

void BasicDamageTemplate::addGreenAugmentationStatus(){

}

#pragma mark - additional cost


void BasicDamageTemplate::addNeutralAdditionalCost()
{
}

void BasicDamageTemplate::addRedAdditionalCost()
{
}

void BasicDamageTemplate::addBlueAdditionalCost()
{
}

void BasicDamageTemplate::addYellowAdditionalCost()
{
}

void BasicDamageTemplate::addGreenAdditionalCost()
{
}

#pragma mark - main status
void BasicDamageTemplate::addNeutralMainStatus()
{
    int attack = 1 + (int)cardPower/7 + LLMath::diceRoll((int)cardPower/7, 1);
    //set limit on basic attack
    if(attack > 7){
        attack = 7;
    }
    MonsterHealthOffsetStatus *status = new MonsterHealthOffsetStatus();
    status->initWithHealthOffset(-attack);
    createdCard->cardTargets->statuses->addObject(status);
    createdCard->setupDamageCard(attack);
}

void BasicDamageTemplate::addRedMainStatus()
{
    addNeutralMainStatus();
}

void BasicDamageTemplate::addBlueMainStatus()
{
    addNeutralMainStatus();
}

void BasicDamageTemplate::addYellowMainStatus(){
    addNeutralMainStatus();
}

void BasicDamageTemplate::addGreenMainStatus(){
    addNeutralMainStatus();
}

#pragma mark -

int BasicDamageTemplate::calculateSoul(){
    int cost = (int)powerLevel/3;
    cost += cardCostOffset;
    cost += LLMath::diceRoll((int)cardPower/6, 1);
    return cost;
}


