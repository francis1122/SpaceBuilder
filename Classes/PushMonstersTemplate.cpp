//
//  PushMonstersTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 2/21/14.
//
//

#include "PushMonstersTemplate.h"
#include "Statuses.h"
#include "CardSprite.h"
#include "Targets.h"
#include "Targets.h"
const std::string PushMonstersTemplate::CLASS_NAME = "PushMonstersTemplate";


void PushMonstersTemplate::createCardTargets(CardSprite *card){
    CardTargets *cardTargets = new PlayAreaTargets();
    cardTargets->initWithCardSprite(card);
    cardTargets->timesCardCanBePlayed = 1;
    createdCard->cardTargets = cardTargets;
}

#pragma mark - augmentation

void PushMonstersTemplate::addNeutralAugmentationStatus(){
    
}

void PushMonstersTemplate::addRedAugmentationStatus(){
    
}

void PushMonstersTemplate::addBlueAugmentationStatus(){
    
}

void PushMonstersTemplate::addYellowAugmentationStatus(){
    
}

void PushMonstersTemplate::addGreenAugmentationStatus(){

}

#pragma mark - additional cost


void PushMonstersTemplate::addNeutralAdditionalCost(){
    
}

void PushMonstersTemplate::addRedAdditionalCost(){
    
}

void PushMonstersTemplate::addBlueAdditionalCost(){
    
}

void PushMonstersTemplate::addYellowAdditionalCost(){
    
}

void PushMonstersTemplate::addGreenAdditionalCost(){
    
}


#pragma mark - main status

void PushMonstersTemplate::addNeutralMainStatus(){
    
    OffsetMonsterLocationStatus *status = new OffsetMonsterLocationStatus();
    status->initWithLocationOffset(1);
    
    AllMonsterStatus *allStatus = new AllMonsterStatus();
    allStatus->initWithStatus(status);
    
    createdCard->cardTargets->statuses->addObject(allStatus);
    mainDescription = CCString::createWithFormat("One Use\r Push all monsters back a space");
    createdCard->setCardPicture("PictureCard");
}

void PushMonstersTemplate::addRedMainStatus(){
    addNeutralMainStatus();
}

void PushMonstersTemplate::addBlueMainStatus(){
    addNeutralMainStatus();
}

void PushMonstersTemplate::addYellowMainStatus(){
    addNeutralMainStatus();
}

void PushMonstersTemplate::addGreenMainStatus(){
    addNeutralMainStatus();
}

#pragma mark -