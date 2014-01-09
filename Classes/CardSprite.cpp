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
#include "GameManager.h"
#include "GameLayer.h"
#include "Constants.h"
#include "HandLayer.h"

USING_NS_CC;



// on "init" you need to initialize your instance
bool CardSprite::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCSprite::initWithSpriteFrameName("CardBase") )
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
    
    textBox = CCSprite::createWithSpriteFrameName("CardTextBox");
    textBox->setPosition(ccp(260, 180));
    this->addChild(textBox, 1);
    
    //details of card
    CCSize detailSize = CCSizeMake(330, 240);
    detailsLabel = CCLabelTTF::create("", "Arial", 48, detailSize, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    detailsLabel->setColor(ccBLACK);
    detailsLabel->setPosition(ccp(212,175));
    textBox->addChild(detailsLabel, 2);
    
    
    costBox = CCSprite::createWithSpriteFrameName("CardCostBox");
    costBox->setPosition(ccp(35, 580));
    this->addChild(costBox, 2);
    
    CCSize costSize = CCSizeMake(150, 150);
    costLabel = CCLabelTTF::create("0", "Arial", 92, costSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentTop);
    costLabel->setColor(ccWHITE);
    costLabel->setPosition(ccp(58,65));
    costBox->addChild(costLabel, 2);
    
    setSoulCostOfCard(3);
    
    
    //setup card basics
    //card text

    
    glowSprite = CCSprite::createWithSpriteFrameName("cardGlow");
    glowSprite->setPosition(ccp(glowSprite->getContentSize().width/2 + 5 ,glowSprite->getContentSize().height/2));
    glowSprite->setVisible(false);
    this->addChild(glowSprite, -1);
    isInteractive = false;
        
    return true;
}


void CardSprite::addCard()
{
    this->setPosition(GM->gameLayer->handLayer->deckCardSprite->getPosition());
    GM->gameLayer->addChild(this, 10000);
}

void CardSprite::removeCard()
{
    this->removeFromParentAndCleanup(true);
}

void CardSprite::setCardType(CardType newCardType){
    cardType = newCardType;
    //set textbox and image of card
    if(cardType == Attack){
        textBox->setPosition(ccp(260, 190));
    }else if(cardType == Soul){
        textBox->setPosition(ccp(260, 190));
    }else if(cardType == Spell){
        textBox->setPosition(ccp(260, 410));
    }else if(cardType == Equipment){
        
    }

}

void CardSprite::setAction(Action* newAction){
    this->action = newAction;
    //set color of card
    this->setColor(newAction->getActionColor());
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



#pragma mark - card creation
void CardSprite::addActionGain(CCArray* actionArray){
    for( int i = 0; i < actionArray->count(); i++){
        //add object to text area
        Action *action = (Action*)actionArray->objectAtIndex(i);
        CCSprite *sprite = CCSprite::createWithSpriteFrameName("Card_Action");
        sprite->setColor(action->getActionColor());
        sprite->setScale(1.0);
        sprite->setPosition(ccpAdd(textBox->getPosition(), ccp(-20 + i * 80, 110)));
        addChild(sprite, 2);
    }
}


void CardSprite::setupDamageCard(int damage){
    setCardType(Attack);
    CCSprite *cardImage = CCSprite::createWithSpriteFrameName("Card_Image_Attack");
    cardImage->setPosition(ccp(260, 470));
    this->addChild(cardImage, 1);
    
    CCSize costSize = CCSizeMake(150, 150);
    CCString *string =CCString::createWithFormat("%i", damage);
    CCLabelTTF *damageLabel = CCLabelTTF::create(string->getCString(), "Arial", 200, costSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentTop);
    damageLabel->setColor(ccWHITE);
    damageLabel->setPosition(ccp(255,460));
    this->addChild(damageLabel, 2);


}

void CardSprite::setupSoulGainCard(int soulGain){
    setCardType(Soul);
    CCSprite *cardImage = CCSprite::createWithSpriteFrameName("CardGainSoul");
    cardImage->setPosition(ccp(260, 470));
    this->addChild(cardImage, 1);
    
    CCSize costSize = CCSizeMake(150, 150);
    CCString *string =CCString::createWithFormat("%i", soulGain);
    CCLabelTTF *damageLabel = CCLabelTTF::create(string->getCString(), "Arial", 200, costSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentTop);
    damageLabel->setColor(ccWHITE);
    damageLabel->setPosition(ccp(255,470));
    this->addChild(damageLabel, 2);

}


