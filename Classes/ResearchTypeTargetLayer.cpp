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
    militaryIcon = CCSprite::createWithSpriteFrameName("tech_military");
    militaryIcon->setPosition(ccp(visibleSize.width/4 - 150, visibleSize.height/2));
    this->addChild(militaryIcon);
    
    industryIcon = CCSprite::createWithSpriteFrameName("tech_industry");
    industryIcon->setPosition(ccp(visibleSize.width/2 - 150, visibleSize.height/2));
    this->addChild(industryIcon);
    
    expansionIcon = CCSprite::createWithSpriteFrameName("tech_expansion");
    expansionIcon->setPosition(ccp(visibleSize.width/2 + 150, visibleSize.height/2));
    this->addChild(expansionIcon);
    
    scienceIcon = CCSprite::createWithSpriteFrameName("tech_science");
    scienceIcon->setPosition(ccp(visibleSize.width - 150, visibleSize.height/2));
    this->addChild(scienceIcon);
    
    description = CCLabelTTF::create("", Main_Font, 72);
    description->setPosition(ccp(600, visibleSize.height - 100));
    this->addChild(description, 1003);
    
    
    return true;
}


void ResearchTypeTargetLayer::setupInterface(ResearchTypes type)
{
    if(type == MilitaryTech){
        militaryIcon->setColor(ccc3(255,255,255));
        industryIcon->setColor(ccc3(50,50,50));
        expansionIcon->setColor(ccc3(50,50,50));
        scienceIcon->setColor(ccc3(50,50,50));
        
        int currentTech = GM->player->militaryTech;
        int generate = GM->player->calculateTechGeneration();
        description->setString(CCString::createWithFormat("military: %i + %i = %i", currentTech, generate, currentTech + generate)->getCString());
    }else if(type == IndustryTech){
        militaryIcon->setColor(ccc3(50,50,50));
        industryIcon->setColor(ccc3(255,255,255));
        expansionIcon->setColor(ccc3(50,50,50));
        scienceIcon->setColor(ccc3(50,50,50));
        
        int currentTech = GM->player->industryTech;
        int generate = GM->player->calculateTechGeneration();
        description->setString(CCString::createWithFormat("industry: %i + %i = %i", currentTech, generate, currentTech + generate)->getCString());
    }else if(type == ExpansionTech){
        militaryIcon->setColor(ccc3(50,50,50));
        industryIcon->setColor(ccc3(50,50,50));
        expansionIcon->setColor(ccc3(255,255,255));
        scienceIcon->setColor(ccc3(50,50,50));
        
        int currentTech = GM->player->expansionTech;
        int generate = GM->player->calculateTechGeneration();
        description->setString(CCString::createWithFormat("expansion: %i + %i = %i", currentTech, generate, currentTech + generate)->getCString());
    }else if(type == ScienceTech){
        militaryIcon->setColor(ccc3(50,50,50));
        industryIcon->setColor(ccc3(50,50,50));
        expansionIcon->setColor(ccc3(50,50,50));
        scienceIcon->setColor(ccc3(255,255,255));
        
        int currentTech = GM->player->scienceTech;
        int generate = GM->player->calculateTechGeneration();
        description->setString(CCString::createWithFormat("science: %i + %i = %i", currentTech, generate, currentTech + generate)->getCString());
    }

}

void ResearchTypeTargetLayer::updateInterface()
{
    
    
}

