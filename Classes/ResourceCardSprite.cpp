//
//  ResourceResourceCardSprite.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 7/10/14.
//
//

#include "ResourceCardSprite.h"
#include "CardTargets.h"
#include "GameManager.h"
#include "GameLayer.h"
#include "Constants.h"
#include "HandLayer.h"
#include "Utility.h"
#include "SolarSystemObject.h"

USING_NS_CC;



// on "init" you need to initialize your instance
bool ResourceCardSprite::initWithSpriteFrameName(const char *pszSpriteFrameName)
{
    //////////////////////////////
    // 1. super init first
    if ( !CardSprite::initWithSpriteFrameName(pszSpriteFrameName) )
    {
        return false;
    }
    
    resourceType = FoodResource;
    tier = 1;
    
    cardType = Resource;
    
    //detailsLabel = CCLabelTTF::create("", Main_Font, 42, detailSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    
    detailsLabel->setFontSize(52);
    detailsLabel->setFontName(LARGE_NUMBER_FONT);
    detailsLabel->setPosition(ccp(260, 280));
    
    return true;
}


void ResourceCardSprite::updateInterface(){
    //    CCString *commandPointsString =CCString::createWithFormat("command:%i-%i", GM->player->commandPoints, GM->player->commandPointsMax);
    //    commandPointsLabel->setString(commandPointsString->getCString());
    

    //to play costs
//    CCString *playCostString = CCString::createWithFormat("");
//    playCostLabel->setString(playCostString->getCString());
    
    
    CCString *resourceString;
    if(owner){
        if(resourceType == FoodResource){
            resourceString = CCString::createWithFormat("food %i", tier);
        }else if(resourceType == ProductionResource){
            resourceString = CCString::createWithFormat("prod %i\n%i", tier, owner->calculateProductionGeneartion());
        }else if(resourceType == MoneyResource){
            resourceString = CCString::createWithFormat("money %i\n%i", tier, owner->calculateMoneyGeneration());
        }else if(resourceType == TechResource){
            resourceString = CCString::createWithFormat("tech %i\n%i", tier, owner->calculateTechGeneration());
        }else if(resourceType == WasteResource){
            resourceString = CCString::createWithFormat("Waste");
        }
    }else{
        if(resourceType == FoodResource){
            resourceString = CCString::createWithFormat("food %i", tier);
        }else if(resourceType == ProductionResource){
            resourceString = CCString::createWithFormat("prod %i", tier);
        }else if(resourceType == MoneyResource){
            resourceString = CCString::createWithFormat("money %i", tier);
        }else if(resourceType == TechResource){
            resourceString = CCString::createWithFormat("tech %i", tier);
        }else if(resourceType == WasteResource){
            resourceString = CCString::createWithFormat("Waste");
        }
    }

    detailsLabel->setString(resourceString->getCString());
    
    //home planet
    if(homeSolarSystem){
        homeLabel->setString(homeSolarSystem->nameLabel->getString());
    }
    
    
}

void ResourceCardSprite::generateResources()
{
    this->owner->resourceGeneration(this);
    updateInterface();

}
