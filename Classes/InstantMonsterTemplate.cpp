//
//  InstantMonsterTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/18/14.
//
//

#include "InstantMonsterTemplate.h"
#include "Statuses.h"
#include "CardSprite.h"
#include "Targets.h"
#include "Action.h"
#include "CardGenerator.h"
#include "LLMath.h"


const std::string InstantMonsterTemplate::CLASS_NAME = "InstantMonsterTemplate";



void InstantMonsterTemplate::createCardTargets(CardSprite *card){
    CardTargets *cardTargets = new MonsterTargets();
    cardTargets->initWithCardSprite(card);
    createdCard->cardTargets = cardTargets;
    createdCard->setCardPicture("PictureCard");
}

#pragma mark - augmentation


void InstantMonsterTemplate::addNeutralAugmentationStatus(){
    
}

void InstantMonsterTemplate::addRedAugmentationStatus(){

}

void InstantMonsterTemplate::addBlueAugmentationStatus(){

}

void InstantMonsterTemplate::addYellowAugmentationStatus(){

}

void InstantMonsterTemplate::addGreenAugmentationStatus(){

}

#pragma mark - additional cost


void InstantMonsterTemplate::addNeutralAdditionalCost(){
}

void InstantMonsterTemplate::addRedAdditionalCost(){
}

void InstantMonsterTemplate::addBlueAdditionalCost(){
}

void InstantMonsterTemplate::addYellowAdditionalCost(){
}

void InstantMonsterTemplate::addGreenAdditionalCost(){
}


#pragma mark - main status

void InstantMonsterTemplate::addNeutralMainStatus(){
    
    int attack = (int)cardPower/4 + LLMath::diceRoll((int)cardPower/4, 1);
    createdCard->cardTargets->maxMonsterLife = attack;
    InstantKillMonsterStatus *status = new InstantKillMonsterStatus();
    status->init();
    createdCard->cardTargets->statuses->addObject(status);
    
    createdCard->setCardType(Spell);
    mainDescription = CCString::createWithFormat("Destroy monster with %i or less life", (attack));
}

void InstantMonsterTemplate::addRedMainStatus(){
    addNeutralMainStatus();
}

void InstantMonsterTemplate::addBlueMainStatus(){
    addNeutralMainStatus();
}

void InstantMonsterTemplate::addYellowMainStatus(){
    addNeutralMainStatus();
}

void InstantMonsterTemplate::addGreenMainStatus(){
    addNeutralMainStatus();
}

#pragma mark -







