//
//  CardTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 12/6/13.
//
//

#include "CardTemplate.h"

#include "Statuses.h"
#include "CardSprite.h"
#include "CardTargets.h"

bool CardTemplate::init(float powerLevel){
    cardPower = powerLevel;
    this->powerLevel = powerLevel;
    costDescription = NULL;
    mainDescription = NULL;
    augmentationDescription = NULL;
    return true;
}

CardSprite* CardTemplate::createCard(){
    CCLog("CardTemplate::createCard");
    
    createdCard = new CardSprite();
    createdCard->init();
    
    //chance of additional cost
    
    
    //chance of augmentation
    
    
    //add main status
    addMainStatus();
    
    //calculate cost
    createdCard->setSoulCostOfCard(calculateSoul());
    
    //add text to card
    this->addDescriptionText();
    
    return createdCard;
}

void CardTemplate::addAugmentationStatus(){
    CCLog("CardTemplate::addAugmentationStatus");
}

void CardTemplate::addAdditionalCost(){
    CCLog("CardTemplate::addAdditionalCost");
}

void CardTemplate::addMainStatus(){
    CCLog("CardTemplate::addMainStatus");
}

int CardTemplate::calculateSoul(){
    return 1;
}

void CardTemplate::addDescriptionText(){
    //add text to card
    const char* main = "";
    if(mainDescription) main = mainDescription->getCString();
    const char* cost = "";
    if(costDescription) cost= costDescription->getCString();
    const char* augmentation = "";
    if(augmentationDescription) augmentation = augmentationDescription->getCString();
    CCString *detailsString =CCString::createWithFormat("%s%s%s", cost, main, augmentation );
    createdCard->detailsLabel->setString(detailsString->getCString());
}

