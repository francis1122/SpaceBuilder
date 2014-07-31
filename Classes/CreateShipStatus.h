//
//  CreateShipStatus.h
//  RogueDeck
//
//  Created by Hunter Francis on 7/28/14.
//
//

#ifndef __RogueDeck__CreateShipStatus__
#define __RogueDeck__CreateShipStatus__

#include "cocos2d.h"
#include "Status.h"
USING_NS_CC;

class MonsterSprite;
class CardSprite;
class Player;
class SolarSystemObject;
class AbilityTargets;

class CreateShipStatus : public Status
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static node()" method manually
    CREATE_FUNC(CreateShipStatus);
    
    CCString *shipTitle;
    CCString *shipDescription;
    CCString *shipSpriteName;
    CCArray *shipStatuses;
    
    
    int health;
    int attack;
    
    //holds abilityTargets, Ability instance is made later
    CCArray *abilities;
    
    virtual void addStatusToSolarSystem(SolarSystemObject *solarSystemObject);
    
    CCString *className;
    
};

#endif /* defined(__RogueDeck__CreateShipStatus__) */
