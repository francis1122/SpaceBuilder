//
//  CardSprite.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/17/13.
//
//

#include "CardSprite.h"
#include "CardTargets.h"
#include "GameManager.h"
#include "GameLayer.h"
#include "Constants.h"
#include "HandLayer.h"
#include "Utility.h"
#include "SolarSystemObject.h"

USING_NS_CC;



// on "init" you need to initialize your instance
bool CardSprite::initWithSpriteFrameName(const char *pszSpriteFrameName)
{
    //////////////////////////////
    // 1. super init first
    if ( !CCSprite::initWithSpriteFrameName(pszSpriteFrameName) )
    {
        return false;
    }
    
    cardType = Utility;
    
    BaseObject::initDefaultState();
    homeSolarSystem = NULL;
//    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
//   CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    costToBuy = 50;
    costToPlay = 0;
    productionToPlay = 0;
    researchSlot = 0;
    isPassive = false;
    this->setScale(DEFAULT_CARD_SCALE);
    researchType = MilitaryTech;
    
//    textBox = CCSprite::createWithSpriteFrameName("CardTextBox");
//    textBox->setPosition(ccp(240, 180));
//    this->addChild(textBox, 1);
    
    //details of card
    CCSize detailSize = CCSizeMake(350, 330);
    detailsLabel = CCLabelTTF::create("", Main_Font, 42, detailSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    detailsLabel->setColor(ccBLACK);
    detailsLabel->setPosition(ccp(260,180));
    this->addChild(detailsLabel, 100);
//    textBox->addChild(detailsLabel, 2);
    
    
//    costBox = CCSprite::createWithSpriteFrameName("floaty");
//    costBox->setPosition(ccp(95, 640));
//    costBox->setColor(ccBLACK);
//    this->addChild(costBox, 2);
    
//    playCostBox = CCSprite::createWithSpriteFrameName("floaty");
//    playCostBox->setPosition(ccp(405, 640));
    //    costBox->setColor(ccBLACK);
//    this->addChild(playCostBox, 2);
    
//    CCSize costSize = CCSizeMake(200, 150);
//    costLabel = CCLabelTTF::create("0", LARGE_NUMBER_FONT, 42, costSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentTop);
//    costLabel->setColor(ccBLACK);
  //  costLabel->setPosition(ccp(260, 310));
//    this->addChild(costLabel, 2);
    
    CCSize playCostSize = CCSizeMake(200, 100);
    playCostLabel = CCLabelTTF::create("", LARGE_NUMBER_FONT, 52, playCostSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentTop);
    playCostLabel->setColor(ccBLACK);
    playCostLabel->setPosition(ccp(260, 281));
    this->addChild(playCostLabel, 2);
    
    homeLabel = CCLabelTTF::create("", Main_Font, 52, detailSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    homeLabel->setColor(ccBLACK);
    homeLabel->setPosition(ccp(220, 89));
    this->addChild(homeLabel, 101);
    
    cardNameLabel = CCLabelTTF::create("Title", Main_Font, 36, detailSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    cardNameLabel->setColor(ccBLACK);
    cardNameLabel->setPosition(ccp(260,591));
    this->addChild(cardNameLabel, 101);
    
    

    
    glowSprite = CCSprite::createWithSpriteFrameName("NeutralCard");
    glowSprite->setPosition(ccp(glowSprite->getContentSize().width/2 + 15 ,glowSprite->getContentSize().height/2 - 9));
    glowSprite->setColor(ccGREEN);
    glowSprite->setScale(1.05);
    glowSprite->setVisible(false);
    this->addChild(glowSprite, -1);

//    CCString *newString = CCString::createWithFormat("%i", costToBuy);
//    costLabel->setString(newString->getCString());
    
    detailsLabel->setString("no description");
    
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

}

void CardSprite::enableInteractive(){
    glowSprite->setVisible(true);
    isInteractive = true;
}

void CardSprite::disableInteractive(){
    glowSprite->setVisible(false);
    isInteractive = false;
}

void CardSprite::updateInterface(){
//    CCString *commandPointsString =CCString::createWithFormat("command:%i-%i", GM->player->commandPoints, GM->player->commandPointsMax);
//    commandPointsLabel->setString(commandPointsString->getCString());
    
    //card costs
/*    CCString *costString =CCString::createWithFormat("%i", this->costToBuy);
    costLabel->setString(costString->getCString());
    */
    //to play costs
    CCString *playCostString = CCString::createWithFormat("%i %i", this->costToPlay, productionToPlay);
    playCostLabel->setString(playCostString->getCString());
  
    //home planet
/*    if(homeSolarSystem){
        homeLabel->setString(homeSolarSystem->nameLabel->getString());
    }
    */
}

#pragma mark - card creation
/*void CardSprite::setSoulCostOfCard(int newSoulCost){
    CCString *newString = CCString::createWithFormat("%i", newSoulCost);
    costLabel->setString(newString->getCString());
    soulCost = newSoulCost;
    //    CCRenderTexture *damageShadow = Utility::createTTFStroke(costLabel, 7, ccBLACK, 255);
    //    costBox->addChild(damageShadow, 1);
}
*/

void CardSprite::setHomeSolarSystem(SolarSystemObject* newHome)
{
    homeSolarSystem = newHome;
    updateInterface();
}

void CardSprite::setCardPicture(const char* pictureName)
{
    //setup card basics
    this->cardImage = CCSprite::createWithSpriteFrameName(pictureName);
    this->cardImage->setPosition(ccp(260, 446));
    this->addChild(this->cardImage, 100);
}

/*
void CardSprite::setupDamageCard(int damage){
    setCardType(Attack);
    CCSprite *cardImage = CCSprite::createWithSpriteFrameName("Card_Image_Attack2");
    cardImage->setPosition(ccp(256, 455));
    this->addChild(cardImage, 1);
    
    CCSize costSize = CCSizeMake(300, 150);
    CCString *string =CCString::createWithFormat("%i", damage);
    CCLabelTTF *damageLabel = CCLabelTTF::create(string->getCString(), LARGE_NUMBER_FONT, 200, costSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentTop);
    damageLabel->setColor(ccWHITE);
    damageLabel->setPosition(ccp(253,450));
    this->addChild(damageLabel, 2);
    CCRenderTexture *damageShadow = Utility::createTTFStroke(damageLabel, 9, ccBLACK, 255);
    this->addChild(damageShadow, 1);
}

void CardSprite::setupSoulGainCard(int soulGain){
    setCardType(Soul);
    CCSprite *cardImage = CCSprite::createWithSpriteFrameName("CardGainSoul");
    cardImage->setPosition(ccp(250, 465));
    this->addChild(cardImage, 1);
    
    CCSize costSize = CCSizeMake(300, 150);
    CCString *string =CCString::createWithFormat("%i", soulGain);
    CCLabelTTF *damageLabel = CCLabelTTF::create(string->getCString(), LARGE_NUMBER_FONT, 200, costSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentTop);
    damageLabel->setColor(ccWHITE);
    damageLabel->setPosition(ccp(253,450));
    this->addChild(damageLabel, 2);
    
    CCRenderTexture *damageShadow = Utility::createTTFStroke(damageLabel, 9, ccBLACK, 255);
    this->addChild(damageShadow, 1);
}

*/
