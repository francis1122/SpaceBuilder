//
//  CreateBuildingStatus.h
//  RogueDeck
//
//  Created by Hunter Francis on 7/22/14.
//
//

#ifndef __RogueDeck__CreateBuildingStatus__
#define __RogueDeck__CreateBuildingStatus__

#include "cocos2d.h"
#include "Status.h"
USING_NS_CC;

class MonsterSprite;
class CardSprite;
class Player;
class SolarSystemObject;
class CreateBuildingStatus : public Status
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static node()" method manually
    CREATE_FUNC(CreateBuildingStatus);
    
    CCString *buildingTitle;
    CCString *buildingDescription;
    CCString *buildingSpriteName;
    CCArray *buildingStatuses;
    
    virtual void addStatusToSolarSystem(SolarSystemObject *solarSystemObject);
    
    CCString *className;
    
};

#endif /* defined(__RogueDeck__CreateBuildingStatus__) */
