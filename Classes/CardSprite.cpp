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
#include "Utility.h"

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
    
    BaseObject::initDefaultState();

//    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
//   CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    turnsLeftInMarket = 0;
    lane = 0;
    this->setScale(.25);
    
    action = new Action();
    action->init(Neutral);
    
    textBox = CCSprite::createWithSpriteFrameName("CardTextBox");
    textBox->setPosition(ccp(240, 180));
    this->addChild(textBox, 1);
    
    //details of card
    CCSize detailSize = CCSizeMake(300, 330);
    detailsLabel = CCLabelTTF::create("", Main_Font, 42, detailSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    detailsLabel->setColor(ccBLACK);
    detailsLabel->setPosition(ccp(180,175));
    textBox->addChild(detailsLabel, 2);
    
    
    costBox = CCSprite::createWithSpriteFrameName("CardGainSoul");
    costBox->setScale(.45);
    costBox->setPosition(ccp(35, 580));
    costBox->setColor(ccBLACK);
    this->addChild(costBox, 2);
    
    CCSize costSize = CCSizeMake(300, 300);
    costLabel = CCLabelTTF::create("0", LARGE_NUMBER_FONT, 192, costSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentTop);
    costLabel->setColor(ccWHITE);
    costLabel->setPosition(ccp(178,89));
    costBox->addChild(costLabel, 2);
    
    setSoulCostOfCard(3);
    
    
    //setup card basics
    //card text

    
    glowSprite = CCSprite::createWithSpriteFrameName("cardGlow");
    glowSprite->setPosition(ccp(glowSprite->getContentSize().width/2 - 14 ,glowSprite->getContentSize().height/2 - 9));
    glowSprite->setColor(ccGREEN);
    glowSprite->setVisible(false);
    this->addChild(glowSprite, -1);

        
    return true;
}


void CardSprite::addCard()
{
    this->setPosition(GM->gameLayer->handLayer->deckCardSprite->getPosition());
    this->removeFromParentAndCleanup(true);
    GM->gameLayer->handLayer->addChild(this, 10000);
}

void CardSprite::removeCard()
{
    this->removeFromParentAndCleanup(true);
}

void CardSprite::setCardType(CardType newCardType){
    cardType = newCardType;
    //set textbox and image of card
    if(cardType == Attack){
        textBox->setPosition(ccp(240, 200));
    }else if(cardType == Soul){
        textBox->setPosition(ccp(240, 200));
    }else if(cardType == Spell){
        textBox->setPosition(ccp(240, 200));
    }else if(cardType == Equipment){
        textBox->setPosition(ccp(240, 200));
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
    
//    CCRenderTexture *damageShadow = Utility::createTTFStroke(costLabel, 7, ccBLACK, 255);
//    costBox->addChild(damageShadow, 1);
}



#pragma mark - card creation
void CardSprite::addActionGain(CCArray* actionArray){
    for( int i = 0; i < actionArray->count(); i++){
        //add object to text area
        Action *action = (Action*)actionArray->objectAtIndex(i);
        CCSprite *sprite = CCSprite::createWithSpriteFrameName("Card_Action");
        sprite->setColor(action->getActionColor());
        sprite->setScale(1.0);
        sprite->setPosition(ccpAdd(textBox->getPosition(), ccp(-20 + i * 80, textBox->getPosition().y - 100)));
        addChild(sprite, 2);
        
//        CCRenderTexture *damageShadow = Utility::createTTFStroke(sprite, 7, ccBLACK, 255);
  //      this->addChild(damageShadow, 1);
    }
}


void CardSprite::setupDamageCard(int damage){
    setCardType(Attack);
    CCSprite *cardImage = CCSprite::createWithSpriteFrameName("Card_Image_Attack2");
    cardImage->setPosition(ccp(236, 475));
    this->addChild(cardImage, 1);
    
    CCSize costSize = CCSizeMake(300, 150);
    CCString *string =CCString::createWithFormat("%i", damage);
    CCLabelTTF *damageLabel = CCLabelTTF::create(string->getCString(), LARGE_NUMBER_FONT, 200, costSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentTop);
    damageLabel->setColor(ccWHITE);
    damageLabel->setPosition(ccp(243,460));
    this->addChild(damageLabel, 2);
    CCRenderTexture *damageShadow = Utility::createTTFStroke(damageLabel, 9, ccBLACK, 255);
    this->addChild(damageShadow, 1);
}

void CardSprite::setupSoulGainCard(int soulGain){
    setCardType(Soul);
    CCSprite *cardImage = CCSprite::createWithSpriteFrameName("CardGainSoul");
    cardImage->setPosition(ccp(240, 485));
    this->addChild(cardImage, 1);
    
    CCSize costSize = CCSizeMake(300, 150);
    CCString *string =CCString::createWithFormat("%i", soulGain);
    CCLabelTTF *damageLabel = CCLabelTTF::create(string->getCString(), LARGE_NUMBER_FONT, 200, costSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentTop);
    damageLabel->setColor(ccWHITE);
    damageLabel->setPosition(ccp(243,470));
    this->addChild(damageLabel, 2);
    
    CCRenderTexture *damageShadow = Utility::createTTFStroke(damageLabel, 9, ccBLACK, 255);
    this->addChild(damageShadow, 1);

}


