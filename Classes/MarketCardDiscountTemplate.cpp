//
//  MarketCardDiscountTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 2/18/14.
//
//

#include "MarketCardDiscountTemplate.h"
#include "Statuses.h"
#include "CardSprite.h"
#include "Targets.h"
#include "Action.h"
#include "CardGenerator.h"
#include "LLMath.h"


const std::string MarketCardDiscountTemplate::CLASS_NAME = "MarketCardDiscountTemplate";



void MarketCardDiscountTemplate::createCardTargets(CardSprite *card)
{
    CardTargets *cardTargets = new MarketCardTarget();
    cardTargets->initWithCardSprite(card);
    createdCard->cardTargets = cardTargets;
    createdCard->setCardPicture("PictureCard");
}

#pragma mark - augmentation


void MarketCardDiscountTemplate::addNeutralAugmentationStatus(){
    
}

void MarketCardDiscountTemplate::addRedAugmentationStatus(){
    
}

void MarketCardDiscountTemplate::addBlueAugmentationStatus(){
    
}

void MarketCardDiscountTemplate::addYellowAugmentationStatus(){
    
}

void MarketCardDiscountTemplate::addGreenAugmentationStatus(){
    
}

#pragma mark - additional cost


void MarketCardDiscountTemplate::addNeutralAdditionalCost(){
}

void MarketCardDiscountTemplate::addRedAdditionalCost(){
}

void MarketCardDiscountTemplate::addBlueAdditionalCost(){
}

void MarketCardDiscountTemplate::addYellowAdditionalCost(){
}

void MarketCardDiscountTemplate::addGreenAdditionalCost(){
}


#pragma mark - main status

void MarketCardDiscountTemplate::addNeutralMainStatus(){
    int priceOffset = (int)cardPower/4 + LLMath::diceRoll((int)cardPower/7, 1);
    MarketCardPriceOffsetStatus *status = new MarketCardPriceOffsetStatus();
    status->init();
    status->priceOffset = -priceOffset;
    createdCard->cardTargets->statuses->addObject(status);
    mainDescription = CCString::createWithFormat("Reduce the cost of a card by %i", priceOffset);
    createdCard->setCardType(Spell);
}

void MarketCardDiscountTemplate::addRedMainStatus(){
    addNeutralMainStatus();
}

void MarketCardDiscountTemplate::addBlueMainStatus(){
    addNeutralMainStatus();
}

void MarketCardDiscountTemplate::addYellowMainStatus(){
    addNeutralMainStatus();
}

void MarketCardDiscountTemplate::addGreenMainStatus(){
    addNeutralMainStatus();
}
