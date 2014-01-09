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
    deckCardSprite->setScale(.25);
    discardCardSprite->setScale(.25);
    deckCardSprite->setPosition(ccp(220, 100));
    discardCardSprite->setPosition(ccp(visibleSize.width - 80, 100));
    
    this->addChild(deckCardSprite, 2);
    this->addChild(discardCardSprite,2);
    deckGlowCardSprite = CCSprite::createWithSpriteFrameName("cardGlow");
    discardGlowCardSprite  = CCSprite::createWithSpriteFrameName("cardGlow");
    deckGlowCardSprite->setScale(.25);
    discardGlowCardSprite->setScale(.25);
    deckGlowCardSprite->setPosition(ccp(220, 100));
    discardGlowCardSprite->setPosition(ccp(visibleSize.width - 80, 100));
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
    
    libraryCountLabel = CCLabelTTF::create("10", "Arial", 48);
    discardCountLabel = CCLabelTTF::create("0", "Arial", 48);
    healthLabel = CCLabelTTF::create("10\n10", "Arial", 32);
    soulLabel = CCLabelTTF::create("0\n10", "Arial", 32);
    actionLabel = CCLabelTTF::create("A:2", "Arial", 32);
    
    libraryCountLabel->setPosition(CCPointMake(220, 80));
    discardCountLabel->setPosition(CCPointMake(visibleSize.width - 80, 80));
    healthLabel->setPosition(CCPointMake(68, 80));
    soulLabel->setPosition(CCPointMake(125, 80));
    actionLabel->setPosition(ccp(200,160));
    
    this->addChild(libraryCountLabel, 3);
    this->addChild(discardCountLabel, 3);
    this->addChild(healthLabel, 3);
    this->addChild(soulLabel, 3);
    this->addChild(actionLabel, 3);
    
//    GameManager *GM = GameManager::sharedGameManager();
    //health meter setup
    
    healthBG = CCLayerColor::create(ccc4(0, 0, 0, 255), 50, 300);
    healthIndicator = CCLayerColor::create(ccc4(0, 100, 0, 255), 40, 290);;
    
    healthBG->setPosition( 40,20);
    healthIndicator->setPosition(45, 20);
    
    healthIndicator->setAnchorPoint(ccp(.5, 0));
    
    this->addChild(healthBG, 1);
    this->addChild(healthIndicator, 2);
    
    //soul meter setup
    soulBG = CCLayerColor::create(ccc4(0, 0, 0, 255), 50, 300);
    soulIndicator = CCLayerColor::create(ccc4(75, 20, 150, 255), 40, 290);
    
    soulBG->setPosition( 100,20);
    soulIndicator->setPosition(105, 20);
    
    soulIndicator->setAnchorPoint(ccp(.5, 0));
    
    this->addChild(soulBG, 1);
    this->addChild(soulIndicator, 2);
    
    
    //action holder
    CCLayerColor *actionHolder = CCLayerColor::create(ccc4(90, 90, 90, 255), 300, 70);
    actionHolder->setPosition(ccp(500, 150));
    this->addChild(actionHolder, ZORDERING_ACTIONHOLDER);
    
    actionArray = new CCArray();
    actionArray->init();
    
    return true;
}



void HandLayer::updateInterface(){
//    CCString::create("%i",GM->libraryCards->count()
//    ccs("%i",);
    CCString *libraryCountString = CCString::createWithFormat("%i", GM->player->libraryCards->count());
    libraryCountLabel->setString(libraryCountString->getCString());
    CCString *discardCountString =CCString::createWithFormat("%i", GM->player->discardCards->count());
    discardCountLabel->setString(discardCountString->getCString());
    CCString *healthString =CCString::createWithFormat("%i\n%i", GM->player->health, GM->player->maxHealth);
    healthLabel->setString(healthString->getCString());
    CCString *soulString =CCString::createWithFormat("%i\n%i", GM->player->soul, GM->player->maxSoul);
    soulLabel->setString(soulString->getCString());
    CCString *actionString = CCString::createWithFormat("A:%i", GM->player->actionsLeftArray->count());
    actionLabel->setString(actionString->getCString());
    
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
        sprite->setPosition(ccp(540 + i * 60, 185));
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
