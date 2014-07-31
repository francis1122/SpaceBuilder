//
//  ShipModel.h
//  RogueDeck
//
//  Created by Hunter Francis on 7/28/14.
//
//

#ifndef __RogueDeck__ShipModel__
#define __RogueDeck__ShipModel__

#include "cocos2d.h"
#include "BaseModel.h"
USING_NS_CC;

class SolarSystemObject;
class ShipSprite;
class ShipModel : public BaseModel
{
public:
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static node()" method manually
    CREATE_FUNC(ShipModel);
    
    CCArray *statusArray;
    ShipSprite *worldShipSprite;
    
    CCArray *abilitiesArray;
    
    CCString *name;
    CCString *description;
    //used to render ships
    CCString *shipSpriteName;
    
    SolarSystemObject *location;
    int health;
    int attack;
    //used to move and is replentished each turn
    int fuel;
    
    void update();
    
    void destroyShip();
    
};

#endif /* defined(__RogueDeck__ShipModel__) */
