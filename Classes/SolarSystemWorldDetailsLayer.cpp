//
//  SolarSystemWorldDetailsLayer.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 7/28/14.
//
//

#include "SolarSystemWorldDetailsLayer.h"
#include "GameManager.h"
#include "CardSprite.h"
#include "Constants.h"
#include "SolarSystemObject.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool SolarSystemWorldDetailsLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::createWithSpriteFrameName("PlayerHolder");
    pSprite->setColor(ccYELLOW);
    //    pSprite->initWithSpriteFrameName("background");
    
    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 300));
    
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    //labels
    solarSystemNameLabel = CCLabelTTF::create("10\r10", Main_Font, 48);
    resourcesLabel = CCLabelTTF::create("10\r10", Main_Font, 32);
    
    solarSystemNameLabel->setPosition(ccp(150, 100));
    resourcesLabel->setPosition(ccp(400, 100));
/*    discardCountLabel->setPosition(ccp(80, 35));
    moneyLabel->setPosition(ccp(visibleSize.width - 160, 90));
    commandPointsLabel->setPosition(ccp(visibleSize.width - 160, 30));
  */
    
    this->addChild(solarSystemNameLabel, 100);
    this->addChild(resourcesLabel, 100);
    return true;
}


void SolarSystemWorldDetailsLayer::updateInterface(SolarSystemObject *solarSystem){
    //    CCString::create("%i",GM->libraryCards->count()
    //    ccs("%i",);
    CCString *solarSystemNameString = CCString::createWithFormat("%s", solarSystem->nameLabel->getString());
    solarSystemNameLabel->setString(solarSystemNameString->getCString());
    
    if(solarSystem->owner){
        //RESOURCE GENERATION
        int foodTier = solarSystem->getSystemsResourceTier(FoodResource);
        int moneyTier = solarSystem->getSystemsResourceTier(MoneyResource);
        int productionTier = solarSystem->getSystemsResourceTier(ProductionResource);
        int scienceTier = solarSystem->getSystemsResourceTier(TechResource);
        resourcesLabel->setString(CCString::createWithFormat("%i %i %i %i", foodTier, moneyTier * solarSystem->population, productionTier * solarSystem->population, scienceTier * solarSystem->population)->getCString() );
        
    }else{
        //RESOURCE GENERATION
        int foodTier = solarSystem->getSystemsResourceTier(FoodResource);
        int moneyTier = solarSystem->getSystemsResourceTier(MoneyResource);
        int productionTier = solarSystem->getSystemsResourceTier(ProductionResource);
        int scienceTier = solarSystem->getSystemsResourceTier(TechResource);
        resourcesLabel->setString(CCString::createWithFormat("%i %i %i %i", foodTier, moneyTier, productionTier, scienceTier)->getCString() );
        
    }
    
/*    CCString *discardCountString =CCString::createWithFormat("%i", GM->player->discardCards->count());
    discardCountLabel->setString(discardCountString->getCString());
    CCString *moneyString =CCString::createWithFormat("money:%i", GM->player->money);
    moneyLabel->setString(moneyString->getCString());
    CCString *commandPointsString =CCString::createWithFormat("production:%i", GM->player->production);
    commandPointsLabel->setString(commandPointsString->getCString());
    
    */
}


