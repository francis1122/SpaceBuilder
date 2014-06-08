//
//  HandLayer.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/19/13.
//
//

#include "HandLayer.h"
#include "GameManager.h"
#include "CardSprite.h"
#include "Constants.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool HandLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
//    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    deckCardSprite = CCSprite::createWithSpriteFrameName("cardBack");
    discardCardSprite  = CCSprite::createWithSpriteFrameName("cardBack");
    deckCardSprite->setScale(.20);
    discardCardSprite->setScale(.20);
    deckCardSprite->setPosition(ccp(50, 85));
    discardCardSprite->setPosition(ccp(visibleSize.width - 50, 90));
    
    this->addChild(deckCardSprite, 2);
    this->addChild(discardCardSprite, 2);
    deckGlowCardSprite = CCSprite::createWithSpriteFrameName("cardGlow");
    discardGlowCardSprite  = CCSprite::createWithSpriteFrameName("cardGlow");
    deckGlowCardSprite->setScale(.20);
    discardGlowCardSprite->setScale(.23);
    discardGlowCardSprite->setColor(ccGREEN);
    deckGlowCardSprite->setPosition(deckCardSprite->getPosition());
    discardGlowCardSprite->setPosition(discardCardSprite->getPosition());
    deckGlowCardSprite->setVisible(false);
    discardGlowCardSprite->setVisible(false);
    this->addChild(deckGlowCardSprite, 1);
    this->addChild(discardGlowCardSprite,1);
    

    
    handGlow  = CCSprite::createWithSpriteFrameName("HandGlow");
    handGlow->setPosition(ccp(630, 100));
    handGlow->setVisible(false);
    this->addChild(handGlow, 10);
    
    
/*    CCLayerColor *playArea = CCLayerColor::create(ccc4(255, 0, 0, 255), visibleSize.width, 160);
    playArea->setPosition(CCPointMake(0, 180));
    addChild(playArea);
    */
  /*  CCLayerColor *discardArea = CCLayerColor::create(ccc4(0, 255, 255, 255), 200, 200);
    discardArea->setPosition(CCPointMake(950, 0));
    addChild(discardArea);
    */
    
    libraryCountLabel = CCLabelTTF::create("10", Main_Font, 48);
    discardCountLabel = CCLabelTTF::create("0", Main_Font, 48);
    moneyLabel = CCLabelTTF::create("10\r10", Main_Font, 32);
    commandPointsLabel = CCLabelTTF::create("0\r10", Main_Font, 32);
    
    libraryCountLabel->setPosition(ccp(160, 75));
    discardCountLabel->setPosition(ccp(visibleSize.width - 60, 75));
    moneyLabel->setPosition(ccp(90, visibleSize.height - 50));
    commandPointsLabel->setPosition(ccp(355, visibleSize.height - 50));
    
    this->addChild(libraryCountLabel, 3);
    this->addChild(discardCountLabel, 3);
    this->addChild(moneyLabel, 3);
    this->addChild(commandPointsLabel, 3);
    
    /*
    healthHolder = CCSprite::createWithSpriteFrameName("statsholder");
    soulHolder = CCSprite::createWithSpriteFrameName("statsholder");
    healthHolder->setColor(ccRED);
    soulHolder->setColor(ccMAGENTA);
    healthHolder->setPosition(ccp(180, 121));
    soulHolder->setPosition(ccp(180, 40));
    this->addChild(healthHolder, 2);
    this->addChild(soulHolder, 2);
    */
    
//    GameManager *GM = GameManager::sharedGameManager();
    //health meter setup
    
    healthBG = CCLayerColor::create(ccc4(0, 0, 0, 255), 40, 300);
    healthBG->setPosition(25, 20);
    
    
   // this->addChild(healthBG, 1);
    
    //soul meter setup
    soulBG = CCLayerColor::create(ccc4(0, 0, 0, 255), 40, 300);
    
    soulBG->setPosition(75,20);
    
    //this->addChild(soulBG, 1);
    //action holder    

    return true;
}



void HandLayer::updateInterface(){
//    CCString::create("%i",GM->libraryCards->count()
//    ccs("%i",);
    CCString *libraryCountString = CCString::createWithFormat("%i", GM->player->libraryCards->count());
    libraryCountLabel->setString(libraryCountString->getCString());
    CCString *discardCountString =CCString::createWithFormat("%i", GM->player->discardCards->count());
    discardCountLabel->setString(discardCountString->getCString());
    CCString *moneyString =CCString::createWithFormat("money:%i", GM->player->money);
    moneyLabel->setString(moneyString->getCString());
    CCString *commandPointsString =CCString::createWithFormat("command:%i-%i", GM->player->commandPoints, GM->player->commandPointsMax);
    commandPointsLabel->setString(commandPointsString->getCString());
    
}

void HandLayer::enableDeckInteractive(){
    deckGlowCardSprite->setVisible(true);
}

void HandLayer::disableDeckInteractive(){
    deckGlowCardSprite->setVisible(false);
}

void HandLayer::enableDiscardInteractive(){
    discardGlowCardSprite->setVisible(true);
}

void HandLayer::disableDiscardInterative(){
    discardGlowCardSprite->setVisible(false);
}

void HandLayer::enableHandInteractive(){
    handGlow->setVisible(true);
}

void HandLayer::disableHandInteractive(){
    handGlow->setVisible(false);
}

