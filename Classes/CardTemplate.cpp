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
#include "DirectDamageTemplate.h"


bool CardTemplate::init(float powerLevel, ActionType color ){
    cardPower = powerLevel;
    cardColor = color;
    this->powerLevel = powerLevel;
    costDescription = NULL;
    mainDescription = NULL;
    augmentationDescription = NULL;
    actionsGained = new CCArray();
    return true;
}

CardSprite* CardTemplate::createCard(){
    CCLog("CardTemplate::createCard");
    cardCostOffset = 0;
    createdCard = new CardSprite();
    createdCard->init();
    
    this->createCardTargets();
    
    //chance of additional cost
    
    
    //chance of augmentation
    addAugmentationStatus();
    
    //add main status
    addMainStatus();
    
    //calculate cost
    int cost = calculateSoul();
    if(cost < 1){
        cost = 1;
    }
    
    createdCard->setSoulCostOfCard(cost);
    
    //add text to card
    this->addDescriptionText();
    
    return createdCard;
}

void CardTemplate::createCardTargets(){
    CardTargets *cardTargets = new CardTargets();
    cardTargets->init();
    createdCard->cardTargets = cardTargets;
}

#pragma mark - augmentation

void CardTemplate::addAugmentationStatus(){
    if(cardColor == Neutral){
        addNeutralAugmentationStatus();
    }else if(cardColor == Red){
        addRedAugmentationStatus();
    }else if(cardColor == Blue){
        addBlueAugmentationStatus();
    }else if(cardColor == Yellow){
        addYellowAugmentationStatus();
    }else if(cardColor == Green){
        addGreenAugmentationStatus();
    }
}

void CardTemplate::addNeutralAugmentationStatus(){
    
}

void CardTemplate::addRedAugmentationStatus(){
    
}

void CardTemplate::addBlueAugmentationStatus(){
    
}

void CardTemplate::addYellowAugmentationStatus(){
    
}

void CardTemplate::addGreenAugmentationStatus(){
    
}

#pragma mark - additional cost

void CardTemplate::addAdditionalCost(){
    if(cardColor == Neutral){
        addNeutralAdditionalCost();
    }else if(cardColor == Red){
        addRedAdditionalCost();
    }else if(cardColor == Blue){
        addBlueAdditionalCost();
    }else if(cardColor == Yellow){
        addYellowAdditionalCost();
    }else if(cardColor == Green){
        addGreenAdditionalCost();
    }
}

void CardTemplate::addNeutralAdditionalCost(){
}

void CardTemplate::addRedAdditionalCost(){
}

void CardTemplate::addBlueAdditionalCost(){
}

void CardTemplate::addYellowAdditionalCost(){
}

void CardTemplate::addGreenAdditionalCost(){
}


#pragma mark - main status

void CardTemplate::addMainStatus(){
    if(cardColor == Neutral){
        addNeutralMainStatus();
    }else if(cardColor == Red){
        addRedMainStatus();
    }else if(cardColor == Blue){
        addBlueMainStatus();
    }else if(cardColor == Yellow){
        addYellowMainStatus();
    }else if(cardColor == Green){
        addGreenMainStatus();
    }
}

void CardTemplate::addNeutralMainStatus(){

}

void CardTemplate::addRedMainStatus(){
    
}

void CardTemplate::addBlueMainStatus(){
    
}

void CardTemplate::addYellowMainStatus(){
    
}

void CardTemplate::addGreenMainStatus(){
    
}

#pragma mark -

int CardTemplate::calculateSoul(){
    int cost = (int)cardPower/2;
    cost += cardCostOffset;
    cost += LLMath::diceRoll((int)cardPower/3, 1);
    return cost;
}

void CardTemplate::addDescriptionText(){
    //add text to card
    if(actionsGained->count() > 0){
        // add arrows to card
        createdCard->addActionGain(actionsGained);
        //move description down    detailsLabel->setPosition(ccp(240,155));
        createdCard->detailsLabel->setPosition(ccp(240,90));
    }
    
    const char* main = "";
    if(mainDescription) main = mainDescription->getCString();
    const char* cost = "";
    if(costDescription) cost= costDescription->getCString();
    const char* augmentation = "";
    if(augmentationDescription) augmentation = augmentationDescription->getCString();
    CCString *detailsString =CCString::createWithFormat("%s%s%s", cost, main, augmentation );
    createdCard->detailsLabel->setString(detailsString->getCString());
}


