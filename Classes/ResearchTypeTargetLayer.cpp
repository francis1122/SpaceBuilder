//
//  ResearchTypeTargetLayer.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 7/15/14.
//
//

#include "ResearchTypeTargetLayer.h"



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
bool ResearchTypeTargetLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCLayerColor *bg = CCLayerColor::create(ccc4(50, 50, 50, 100));
    //     bg->setPosition(ccp( bg->getContentSize().width/2, bg->getContentSize().height/2 + 310));
    this->addChild(bg);
 
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    //have icons for the four techs
    militaryIcon = CCSprite::createWithSpriteFrameName("icons_production");
    militaryIcon->setPosition(ccp(visibleSize.width/4 - 150, visibleSize.height/2));
    this->addChild(militaryIcon);
    
    industryIcon = CCSprite::createWithSpriteFrameName("icons_money");
    industryIcon->setPosition(ccp(visibleSize.width/2 - 150, visibleSize.height/2));
    this->addChild(industryIcon);
    
    expansionIcon = CCSprite::createWithSpriteFrameName("icons_food");
    expansionIcon->setPosition(ccp(visibleSize.width/2 + 150, visibleSize.height/2));
    this->addChild(expansionIcon);
    
    scienceIcon = CCSprite::createWithSpriteFrameName("icons_science");
    scienceIcon->setPosition(ccp(visibleSize.width - 150, visibleSize.height/2));
    this->addChild(scienceIcon);
    
    
    return true;
}


void ResearchTypeTargetLayer::updateInterface()
{
    
    
}

