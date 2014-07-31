//
//  MoveShipStatus.h
//  RogueDeck
//
//  Created by Hunter Francis on 7/29/14.
//
//

#ifndef __RogueDeck__MoveShipStatus__
#define __RogueDeck__MoveShipStatus__

#include "cocos2d.h"
#include "Status.h"
USING_NS_CC;

class MonsterSprite;
class CardSprite;
class Player;
class SolarSystemObject;
class Ability;
class ShipModel;

class MoveShipStatus : public Status
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static node()" method manually
    CREATE_FUNC(MoveShipStatus);
    
    virtual void addStatusToSolarSystemWithShip(SolarSystemObject *solarsystemObject, ShipModel *ship);
    
    
};

#endif /* defined(__RogueDeck__MoveShipStatus__) */
