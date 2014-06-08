//
//  SolarSystemObject.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 6/7/14.
//
//

#include "SolarSystemObject.h"
#include "CardSprite.h"
#include "CardTargets.h"
#include "GameManager.h"
#include "GameLayer.h"
#include "Constants.h"
#include "HandLayer.h"
#include "Utility.h"

USING_NS_CC;


// on "init" you need to initialize your instance
bool SolarSystemObject::initWithSpriteFrameName(const char *pszSpriteFrameName)
{
    //////////////////////////////
    // 1. super init first
    if ( !CCSprite::initWithSpriteFrameName(pszSpriteFrameName) )
    {
        return false;
    }
    
    BaseObject::initDefaultState();
    owner = NULL;
    cardSlots = 3;
    //array for actual cards
    //CCArray
    incomeGeneration = 3;
    population = 0;
    populationLimit = 6;
    
    
    return true;
}

void SolarSystemObject::update()
{
    //only increase population if planet is owned
    if(owner){
        populationFraction++;
        if(populationFraction > 4){
            population++;
            populationFraction = 0;
        }
    }
}

