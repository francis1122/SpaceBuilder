//
//  ResourceCardInfoLayer.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 7/22/14.
//
//

#include "ResourceCardInfoLayer.h"


#include "GameManager.h"
#include "UIState.h"
#include "GameLayer.h"
#include "Constants.h"
#include "SolarSystemObject.h"
#include "UIState.h"
#include "Utility.h"
#include "Player.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool ResourceCardInfoLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCLayerColor *bg = CCLayerColor::create(ccc4(150, 150, 150, 100));
    //     bg->setPosition(ccp( bg->getContentSize().width/2, bg->getContentSize().height/2 + 310));
    this->addChild(bg);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    productionSprite = CCSprite::createWithSpriteFrameName("icons_production");
    moneySprite = CCSprite::createWithSpriteFrameName("icons_money");
    foodSprite = CCSprite::createWithSpriteFrameName("icons_food");
    
    productionSprite->setPosition(ccp(visibleSize.width/4 - 150, visibleSize.height/2));
    moneySprite->setPosition(ccp(visibleSize.width/4 - 150, visibleSize.height/2));
    foodSprite->setPosition(ccp(visibleSize.width/4 - 150, visibleSize.height/2));
    
    this->addChild(productionSprite);
    this->addChild(moneySprite);
    this->addChild(foodSprite);
    
    description = CCLabelTTF::create("", Main_Font, 72);
    description->setPosition(ccp(700, visibleSize.height/2 + 80));
    this->addChild(description, 1003);

    
    return true;
}

void ResourceCardInfoLayer::setupInterface(ResourceCardSprite *resourceCard)
{
    ResourceTypes type = resourceCard->resourceType;
    if(type == FoodResource){
        productionSprite->setVisible(false);
        foodSprite->setVisible(true);
        moneySprite->setVisible(false);
        int increase = resourceCard->tier;
        int population = resourceCard->homeSolarSystem->population;
        int populationFrag = resourceCard->homeSolarSystem->populationFraction + increase;
        description->setString(CCString::createWithFormat("%s\npopulation increased by %i\n%i - %i", resourceCard->homeSolarSystem->nameLabel->getString() , increase, population, populationFrag)->getCString());
        
    }else if(type == ProductionResource){
        productionSprite->setVisible(true);
        foodSprite->setVisible(false);
        moneySprite->setVisible(false);
        int generate = GM->player->calculateProductionGeneartion();
        int currentProduction = GM->player->production;
        description->setString(CCString::createWithFormat("%i\n+%i\n%i",currentProduction, generate, currentProduction + generate)->getCString());
    }else if(type == MoneyResource){
        productionSprite->setVisible(false);
        foodSprite->setVisible(false);
        moneySprite->setVisible(true);
        int generate = GM->player->calculateMoneyGeneration();
        int currentMoney = GM->player->money;
        
        description->setString(CCString::createWithFormat("%i\n+%i\n%i",currentMoney, generate, currentMoney + generate)->getCString());
    }else if(type == WasteResource){
        productionSprite->setVisible(false);
        foodSprite->setVisible(false);
        moneySprite->setVisible(false);
        description->setString(CCString::createWithFormat("Waste")->getCString());
    }
}

void ResourceCardInfoLayer::updateInterface()
{
    
    
}
