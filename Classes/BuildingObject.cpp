//
//  BuildingObject.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 7/15/14.
//
//

#include "BuildingObject.h"
#include "BuildingObject.h"
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

USING_NS_CC;


// on "init" you need to initialize your instance
bool BuildingObject::init()
{

    updateInterface();
    statusArray = new CCArray();
    statusArray->init();
    return true;
}

void BuildingObject::onAddingToSystem(SolarSystemObject* solarSystem){
    for(int i = 0; i < statusArray->count(); i++){
        Status *status = (Status*)statusArray->objectAtIndex(i);
        status->applyStatus(solarSystem);
    }
}

void BuildingObject::onRemovalFromSystem(SolarSystemObject* solarSystem){
    for(int i = 0; i < statusArray->count(); i++){
        Status *status = (Status*)statusArray->objectAtIndex(i);
        status->applyEndStatus(solarSystem);
    }
}

void BuildingObject::update(SolarSystemObject *solarSystem)
{
    //cycle though statuses
    for(int i = 0; i < statusArray->count(); i++){
        Status *status = (Status*)statusArray->objectAtIndex(i);
        status->updateStatus(solarSystem);
    }
    
    updateInterface();
}

void BuildingObject::updateInterface()
{

}

