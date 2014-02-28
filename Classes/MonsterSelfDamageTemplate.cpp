//
//  MonsterSelfDamageTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 2/25/14.
//
//

#include "MonsterSelfDamageTemplate.h"
#include "Statuses.h"
#include "CardSprite.h"
#include "Targets.h"
#include "Action.h"
#include "CardGenerator.h"
#include "LLMath.h"


const std::string MonsterSelfDamageTemplate::CLASS_NAME = "MonsterSelfDamageTemplate";

void MonsterSelfDamageTemplate::createCardTargets(CardSprite *card)
{
    CardTargets *cardTargets = new MonsterTargets();
    cardTargets->initWithCardSprite(card);
    createdCard->cardTargets = cardTargets;
    createdCard->setCardPicture("PictureCard");
}

#pragma mark - augmentation


void MonsterSelfDamageTemplate::addNeutralAugmentationStatus(){
    
}

void MonsterSelfDamageTemplate::addRedAugmentationStatus(){
    
}

void MonsterSelfDamageTemplate::addBlueAugmentationStatus(){
    
}

void MonsterSelfDamageTemplate::addYellowAugmentationStatus(){
    
}

void MonsterSelfDamageTemplate::addGreenAugmentationStatus(){
    
}

#pragma mark - additional cost


void MonsterSelfDamageTemplate::addNeutralAdditionalCost()
{
}

void MonsterSelfDamageTemplate::addRedAdditionalCost()
{
}

void MonsterSelfDamageTemplate::addBlueAdditionalCost()
{
}

void MonsterSelfDamageTemplate::addYellowAdditionalCost()
{
}

void MonsterSelfDamageTemplate::addGreenAdditionalCost()
{
}

#pragma mark - main status
void MonsterSelfDamageTemplate::addNeutralMainStatus()
{
    //set limit on basic attack
    MonsterSelfDamageStatus *status = new MonsterSelfDamageStatus();
    status->init();
    createdCard->cardTargets->statuses->addObject(status);
    
    mainDescription = CCString::createWithFormat("Target monster deals damage to himself");
}

void MonsterSelfDamageTemplate::addRedMainStatus()
{
    addNeutralMainStatus();
}

void MonsterSelfDamageTemplate::addBlueMainStatus()
{
    addNeutralMainStatus();
}

void MonsterSelfDamageTemplate::addYellowMainStatus(){
    addNeutralMainStatus();
}

void MonsterSelfDamageTemplate::addGreenMainStatus(){
    addNeutralMainStatus();
}
