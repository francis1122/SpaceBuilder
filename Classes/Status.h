//
//  Status.h
//  RogueDeck
//
//  Created by Hunter Francis on 11/21/13.
//
//

#ifndef __RogueDeck__Status__
#define __RogueDeck__Status__

#include "cocos2d.h"

USING_NS_CC;

class MonsterSprite;
class CardSprite;
class Player;
class SolarSystemObject;
class Ability;
class ShipModel;

class Status : public CCObject
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static node()" method manually
    CREATE_FUNC(Status);
    
    virtual void addStatusToPlayer(Player *player);
    virtual void addStatusToSolarSystem(SolarSystemObject *solarSystemObject);
    virtual void addStatusToSolarSystemWithShip(SolarSystemObject *solarsystemObject, ShipModel *ship);
    virtual void addStatusToCardSprite(CardSprite *card);
    
    //checks whether the status can be used
    virtual bool checkStart();
    
    //called when status is given to object
    virtual void applyStatus();
    
    virtual void applyStatus(SolarSystemObject *solarSystem);
    
    //called when the status ends
    virtual void applyEndStatus();
    
    virtual void applyEndStatus(SolarSystemObject *solarSystem);
    
    //checks whether the status should be destroyed
    virtual bool checkEnd();
    
    //called at end of turn
    virtual void updateStatus();
    
    //if status is used by monster, monster must be passed with it
    virtual void updateStatus(MonsterSprite *monster);
    
    virtual void updateStatus(SolarSystemObject *solarSystem);
    
    virtual void updateStatus(Player *player);
    
    CCString *className;
    
};

#endif /* defined(__RogueDeck__Status__) */
