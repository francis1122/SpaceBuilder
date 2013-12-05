//
//  CardSprite.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/17/13.
//
//

#include "CardSprite.h"
#include "CardTargets.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool CardSprite::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCSprite::initWithSpriteFrameName("card") )
    {
        return false;
    }
//    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
//   CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    turnsLeftInMarket = 0;
    cardTargets = new CardTargets();
    cardTargets->init();
    this->setScale(.25);
    
    
    
    //details of card
    CCSize detailSize = CCSizeMake(330, 290);
    detailsLabel = CCLabelTTF::create("", "Arial", 48, detailSize, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    detailsLabel->setColor(ccBLACK);
    detailsLabel->setPosition(ccp(240,155));
    this->addChild(detailsLabel);
    
    CCSize costSize = CCSizeMake(100, 100);
    costLabel = CCLabelTTF::create("0", "Arial", 64, costSize, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    costLabel->setColor(ccBLACK);
    costLabel->setPosition(ccp(95,555));
    this->addChild(costLabel);
    
    setSoulCostOfCard(2);
    
    return true;
}

void CardSprite::setSoulCostOfCard(int newSoulCost){
    CCString *newString = CCString::createWithFormat("%i", newSoulCost);
    costLabel->setString(newString->getCString());
    soulCost = newSoulCost;
}
