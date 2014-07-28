//
//  CreateBuildingStatus.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 7/22/14.
//
//

#include "CreateBuildingStatus.h"
#include "SolarSystemObject.h"
#include "BuildingObject.h"



USING_NS_CC;


// on "init" you need to initialize your instance
bool CreateBuildingStatus::init()
{
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    className = new CCString();
    className->initWithFormat("CreateBuildingStatus");
    buildingStatuses = new CCArray();
    buildingStatuses->init();
    return true;
}


void CreateBuildingStatus::addStatusToSolarSystem(SolarSystemObject *solarSystemObject)
{
    //create building for planet
    BuildingObject *buildingObject = new BuildingObject();
    buildingObject->init();
    buildingObject->name = new CCString(buildingTitle->getCString());
    buildingObject->description = new CCString(buildingDescription->getCString());
    buildingObject->statusArray->addObjectsFromArray(buildingStatuses);
    buildingObject->buildingSpriteName = new CCString(buildingSpriteName->getCString());
    
    //add building to planet
    solarSystemObject->addBuilding(buildingObject);
    
}
