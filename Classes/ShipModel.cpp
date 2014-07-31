//
//  ShipModel.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 7/28/14.
//
//

#include "ShipModel.h"
#include "ShipModel.h"
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
#include "ShipSprite.h"
#include "SolarSystemObject.h"

USING_NS_CC;


// on "init" you need to initialize your instance
bool ShipModel::init()
{
    statusArray = new CCArray();
    abilitiesArray = new CCArray();
    
    statusArray->init();
    abilitiesArray->init();
    shipSpriteName = CCString::create("MartianRocket_Logo_Big");
    return true;
}


void ShipModel::update()
{
    //needs more thought
    /*
    //cycle though statuses
    for(int i = 0; i < statusArray->count(); i++){
        Status *status = (Status*)statusArray->objectAtIndex(i);
        status->updateStatus(solarSystem);
    }
    */
    fuel = 1;
    if(worldShipSprite){
        worldShipSprite->updateInterface();
    }
    
}

void ShipModel::destroyShip()
{
    if(location){
        location->removeShipModel(this);
    }
}