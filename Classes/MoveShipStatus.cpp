//
//  MoveShipStatus.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 7/29/14.
//
//

#include "MoveShipStatus.h"
#include "SolarSystemObject.h"
#include "BuildingObject.h"
#include "Ability.h"
#include "ShipModel.h"
#include "ShipSprite.h"


USING_NS_CC;


// on "init" you need to initialize your instance
bool MoveShipStatus::init()
{
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    className = new CCString();
    className->initWithFormat("MoveShipStatus");
    return true;
}


void MoveShipStatus::addStatusToSolarSystemWithShip(SolarSystemObject *solarSystemObject, ShipModel *ship)
{
    SolarSystemObject *previousLocation = ship->location;
    previousLocation->removeShipModel(ship);
    solarSystemObject->addShip(ship);
    ship->fuel--;
}
