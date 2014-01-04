//
//  MarketLayer.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/26/13.
//
//

#include "MarketLayer.h"
#include "GameManager.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool MarketLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    //CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
   /*
    CCLayerColor *playArea = CCLayerColor::create(ccc4(255, 0, 0, 255), visibleSize.width, 160);
    playArea->setPosition(CCPointMake(0, 180));
    addChild(playArea);
 */
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    sellCardSprite = CCSprite::createWithSpriteFrameName("cardBack");
    sellCardSprite->setScale(.25);
    sellCardSprite->setPosition(ccp(visibleSize.width - 80, visibleSize.height- 100));
    
    this->addChild(sellCardSprite, 2);
    
    sellGlowCardSprite = CCSprite::createWithSpriteFrameName("cardGlow");
    sellGlowCardSprite->setScale(.25);
    sellGlowCardSprite->setPosition(ccp(visibleSize.width - 80, visibleSize.height- 100));
    sellGlowCardSprite->setVisible(false);
    this->addChild(sellGlowCardSprite, 1);
    

    return true;
}

void MarketLayer::endTurn(){
    //GameManager *GM = GameManager::sharedGameManager();
//    GM->endTurn();
}

void MarketLayer::updateInterface(){
  //  GameManager *GM = GameManager::sharedGameManager();
    //    CCString::create("%i",GM->libraryCards->count()

}

void MarketLayer::enableSellInteractive(){
    sellGlowCardSprite->setVisible(true);
}

void MarketLayer::disableSellInteractive(){
    sellGlowCardSprite->setVisible(false);
}


