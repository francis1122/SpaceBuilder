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
#include "Action.h"


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
    deckCardSprite->setPosition(ccp(190, 85));
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
    healthLabel = CCLabelTTF::create("10\r10", Main_Font, 32);
    soulLabel = CCLabelTTF::create("0\r10", Main_Font, 32);
    
    libraryCountLabel->setPosition(ccp(160, 75));
    discardCountLabel->setPosition(ccp(visibleSize.width - 60, 75));
    healthLabel->setPosition(ccp(40, 60));
    soulLabel->setPosition(ccp(95, 60));
    
    this->addChild(libraryCountLabel, 3);
    this->addChild(discardCountLabel, 3);
    this->addChild(healthLabel, 3);
    this->addChild(soulLabel, 3);
    
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
    healthIndicator = CCLayerColor::create(ccc4(0, 100, 0, 255), 30, 290);;
    
    healthBG->setPosition( 25,20);
    healthIndicator->setPosition(30, 20);
    
    healthIndicator->setAnchorPoint(ccp(.5, 0));
    
    this->addChild(healthBG, 1);
    this->addChild(healthIndicator, 2);
    
    //soul meter setup
    soulBG = CCLayerColor::create(ccc4(0, 0, 0, 255), 40, 300);
    soulIndicator = CCLayerColor::create(ccc4(75, 20, 150, 255), 30, 290);
    
    soulBG->setPosition( 75,20);
    soulIndicator->setPosition(80, 20);
    
    soulIndicator->setAnchorPoint(ccp(.5, 0));
    
    this->addChild(soulBG, 1);
    this->addChild(soulIndicator, 2);
    
    
    //action holder
    CCLayerColor *actionHolder = CCLayerColor::create(ccc4(40, 40, 40, 255), 300, 40);
    actionHolder->setPosition(ccp(450, 150));
    actionHolder->setOpacity(220);
    this->addChild(actionHolder, ZORDERING_ACTIONHOLDER);
    
    actionArray = new CCArray();
    actionArray->init();
    
    
    voidAreaSprite = CCSprite::createWithSpriteFrameName("cardBack");
    voidAreaGlowSprite = CCSprite::createWithSpriteFrameName("cardGlow");;
    voidAreaSprite->setScale(.2);
    voidAreaGlowSprite->setScale(.2);
    voidAreaSprite->setPosition(ccp(visibleSize.width - 65, visibleSize.height - 75));
    voidAreaGlowSprite->setColor(ccGREEN);
    voidAreaGlowSprite->setVisible(false);
    voidAreaGlowSprite->setPosition(voidAreaSprite->getPosition());
    this->addChild(voidAreaGlowSprite, 101);
    this->addChild(voidAreaSprite, 102);
    
    
    return true;
}



void HandLayer::updateInterface(){
//    CCString::create("%i",GM->libraryCards->count()
//    ccs("%i",);
    CCString *libraryCountString = CCString::createWithFormat("%i", GM->player->libraryCards->count());
    libraryCountLabel->setString(libraryCountString->getCString());
    CCString *discardCountString =CCString::createWithFormat("%i", GM->player->discardCards->count());
    discardCountLabel->setString(discardCountString->getCString());
    CCString *healthString =CCString::createWithFormat("%i\r%i", GM->player->health, GM->player->maxHealth);
    healthLabel->setString(healthString->getCString());
    CCString *soulString =CCString::createWithFormat("%i\r%i", GM->player->soul, GM->player->maxSoul);
    soulLabel->setString(soulString->getCString());
    
    //setHealth
    int health = GM->player->health;
    int maxHealth = GM->player->maxHealth;
    float percentHealth = (float)health/(float)maxHealth;
    if(percentHealth > 1.0) percentHealth = 1.0;
  healthIndicator->setScale(1, percentHealth);
    
    //setSoul
    int soul = GM->player->soul;
    int maxSoul = GM->player->maxSoul;
    float percentSoul = (float)soul/(float)maxSoul;
    if(percentSoul > 1.0) percentSoul = 1.0;
    soulIndicator->setScale(1,percentSoul);
    
    // actions
    //clear old actions
    for(int i = 0; i < actionArray->count(); i++){
        CCSprite *sprite = (CCSprite*)(actionArray->objectAtIndex(i));
        sprite->removeFromParent();
    }
    actionArray->removeAllObjects();
    
    for (int i = 0; i < GM->player->actionsLeftArray->count(); i++) {
        CCSprite *sprite = CCSprite::createWithSpriteFrameName("Card_Action");
        Action *action = (Action*)GM->player->actionsLeftArray->objectAtIndex(i);
        sprite->setColor(action->getActionColor());
        sprite->setScale(.5);
        sprite->setPosition(ccp(500 + i * 50, 170));
        //change color depending on action
        
        addChild(sprite, ZORDERING_ACTIONSPRITE);
        actionArray->addObject(sprite);
    }
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

void HandLayer::enableVoidAreaInteractive()
{
    voidAreaGlowSprite->setVisible(true);
}

void HandLayer::disableVoidAreaInteractive()
{
    voidAreaGlowSprite->setVisible(false);
}
