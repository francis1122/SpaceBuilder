//
//  HandLayer.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/19/13.
//
//

#include "HandLayer.h"
#include "GameManager.h"



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
    
    
/*    CCLayerColor *playArea = CCLayerColor::create(ccc4(255, 0, 0, 255), visibleSize.width, 160);
    playArea->setPosition(CCPointMake(0, 180));
    addChild(playArea);
    */
  /*  CCLayerColor *discardArea = CCLayerColor::create(ccc4(0, 255, 255, 255), 200, 200);
    discardArea->setPosition(CCPointMake(950, 0));
    addChild(discardArea);
    */
    
    libraryCountLabel = CCLabelTTF::create("14", "Arial", 32);
    discardCountLabel = CCLabelTTF::create("0", "Arial", 32);
    healthLabel = CCLabelTTF::create("health:10", "Arial", 32);
    soulLabel = CCLabelTTF::create("soul:0", "Arial", 32);
    actionLabel = CCLabelTTF::create("action:2", "Arial", 32);
    
    libraryCountLabel->setPosition(CCPointMake(30, 40));
    discardCountLabel->setPosition(CCPointMake(visibleSize.width - 40, 40));
    healthLabel->setPosition(CCPointMake(80, 120));
    soulLabel->setPosition(CCPointMake(80, 80));
    actionLabel->setPosition(ccp(80,160));
    
    this->addChild(libraryCountLabel);
    this->addChild(discardCountLabel);
    this->addChild(healthLabel);
    this->addChild(soulLabel);
    this->addChild(actionLabel);
    
//    GameManager *GM = GameManager::sharedGameManager();
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(HandLayer::endTurn));
    
	pCloseItem->setPosition(ccp(visibleSize.width - 50,
                                150));
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    
    
    return true;
}

void HandLayer::endTurn(){
    GameManager *GM = GameManager::sharedGameManager();
    GM->endTurn();
}

void HandLayer::updateInterface(){
    GameManager *GM = GameManager::sharedGameManager();
//    CCString::create("%i",GM->libraryCards->count()
//    ccs("%i",);
    CCString *libraryCountString = CCString::createWithFormat("%i", GM->player->libraryCards->count());
    libraryCountLabel->setString(libraryCountString->getCString());
    CCString *discardCountString =CCString::createWithFormat("%i", GM->player->discardCards->count());
    discardCountLabel->setString(discardCountString->getCString());
    CCString *healthString =CCString::createWithFormat("health: %i", GM->player->health);
    healthLabel->setString(healthString->getCString());
    CCString *soulString =CCString::createWithFormat("soul: %i", GM->player->soul);
    soulLabel->setString(soulString->getCString());
    CCString *actionString =CCString::createWithFormat("actions: %i", GM->player->actionsLeft);
    actionLabel->setString(actionString->getCString());
    
}
