//
//  ShipSprite.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 7/28/14.
//
//

#include "ShipSprite.h"
#include "ShipSprite.h"
#include "CardSprite.h"
#include "CardTargets.h"
#include "GameManager.h"
#include "GameLayer.h"
#include "Constants.h"
#include "HandLayer.h"
#include "Utility.h"
#include "Statuses.h"
#include "CardTargets.h"
#include "CardSprite.h"
#include "Targets.h"
#include "CardFactory.h"
#include "BuildingObject.h"
#include "ShipModel.h"
#include "SolarSystemObject.h"
#include "Player.h"

USING_NS_CC;


// on "init" you need to initialize your instance
bool ShipSprite::initWithSpriteFrameName(const char *pszSpriteFrameName)
{
    //////////////////////////////
    // 1. super init first
    if ( !CCSprite::initWithSpriteFrameName(pszSpriteFrameName) )
    {
        return false;
    }
    
    BaseObject::initDefaultState();
    setScale(.35);
    updateInterface();
    return true;
}


void ShipSprite::updateInterface()
{
    //set position
    if(shipModel){
        SolarSystemObject *solarSystem = shipModel->location;
        if(solarSystem){
            int index = solarSystem->shipsArray->indexOfObject(shipModel);
            CCPoint solarPos = solarSystem->getPosition();
            this->setPosition(ccp(-100 + solarPos.x + index * 110, solarPos.y + 100));
        }else{
            CCLog("ShipSprite::updateInterface - no location assigned");
        }
    }
    
}





