//
//  CardSprite.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/17/13.
//
//

#include "CardSprite.h"
#include "CardTargets.h"
#include "Action.h"

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
//    cardTargets = new CardTargets();
  //  cardTargets->init();
    this->setScale(.25);
    
    
    action = new Action();
    action->init(Neutral);
    
    //details of card
    CCSize detailSize = CCSizeMake(330, 290);
    detailsLabel = CCLabelTTF::create("", "Arial", 48, detailSize, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    detailsLabel->setColor(ccBLACK);
    detailsLabel->setPosition(ccp(240,155));
    this->addChild(detailsLabel);
    
    CCSize costSize = CCSizeMake(150, 150);
    costLabel = CCLabelTTF::create("0", "Arial", 92, costSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentTop);
    costLabel->setColor(ccWHITE);
    costLabel->setPosition(ccp(55,550));
    this->addChild(costLabel);
    
    setSoulCostOfCard(2);
    
    glowSprite = CCSprite::createWithSpriteFrameName("cardGlow");
    glowSprite->setPosition(ccp(glowSprite->getContentSize().width/2 - 26,glowSprite->getContentSize().height/2 - 21));
    glowSprite->setVisible(false);
    this->addChild(glowSprite, -1);
    isInteractive = false;
        
    return true;
}

void CardSprite::enableInteractive(){
    glowSprite->setVisible(true);
    isInteractive = true;
}

void CardSprite::disableInteractive(){
    glowSprite->setVisible(false);
    isInteractive = false;
}

void CardSprite::setSoulCostOfCard(int newSoulCost){
    CCString *newString = CCString::createWithFormat("%i", newSoulCost);
    costLabel->setString(newString->getCString());
    soulCost = newSoulCost;
}
