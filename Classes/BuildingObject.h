//
//  BuildingObject.h
//  RogueDeck
//
//  Created by Hunter Francis on 7/15/14.
//
//

#ifndef __RogueDeck__BuildingObject__
#define __RogueDeck__BuildingObject__

#include "cocos2d.h"
#include "BaseModel.h"
USING_NS_CC;

class SolarSystemObject;
class BuildingObject : public BaseModel
{
public:
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static node()" method manually
    CREATE_FUNC(BuildingObject);
    
    CCArray *statusArray;
    
    CCString *name;
    CCString *description;
    CCString *buildingSpriteName;
    
    void onAddingToSystem(SolarSystemObject* solarSystem);
    void onRemovalFromSystem(SolarSystemObject* solarSystem);
    void update(SolarSystemObject *solarSystem);
    void updateInterface();
    
};

#endif /* defined(__RogueDeck__BuildingObject__) */
