//
//  CreateShipStatus.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 7/28/14.
//
//

#include "CreateShipStatus.h"
#include "SolarSystemObject.h"
#include "ShipModel.h"
#include "Ability.h"
#include "AbilityTargets.h"


USING_NS_CC;


// on "init" you need to initialize your instance
bool CreateShipStatus::init()
{
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    className = new CCString();
    className->initWithFormat("CreateShipStatus");
    shipStatuses = new CCArray();
    abilities = new CCArray();
    
    shipStatuses->init();
    abilities->init();
    
    health = 1;
    attack = 1;
    return true;
}


void CreateShipStatus::addStatusToSolarSystem(SolarSystemObject *solarSystemObject)
{
    //create building for planet
    ShipModel *shipModel = new ShipModel();
    shipModel->init();
    shipModel->name = new CCString(shipTitle->getCString());
    shipModel->description = new CCString(shipDescription->getCString());
    shipModel->statusArray->addObjectsFromArray(shipStatuses);
    shipModel->shipSpriteName = new CCString(shipSpriteName->getCString());
    shipModel->health = health;
    shipModel->attack = attack;
    
//    shipModel->abilitiesArray->addObjectsFromArray(abilities);
    for(int i = 0; i < abilities->count(); i++){
        AbilityTargets *abilityTarget = (AbilityTargets*)abilities->objectAtIndex(i);
        Ability *ability = new Ability();
        ability->init();
        ability->shipModel = shipModel;
        ability->targets = abilityTarget;
        shipModel->abilitiesArray->addObject(ability);

    }
    
    //add building to planet
    solarSystemObject->addShip(shipModel);
    
}
