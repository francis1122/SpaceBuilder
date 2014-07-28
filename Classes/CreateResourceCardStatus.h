//
//  CreateResourceCardStatus.h
//  RogueDeck
//
//  Created by Hunter Francis on 7/24/14.
//
//

#ifndef __RogueDeck__CreateResourceCardStatus__
#define __RogueDeck__CreateResourceCardStatus__

#include "cocos2d.h"
#include "Status.h"
#include "Constants.h"
USING_NS_CC;

class Player;
class CardSprite;
class SolarSystemObject;
class CreateResourceCardStatus : public Status
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool initWithResourceCard(ResourceTypes _type, int _tier);
    
    ResourceTypes type;
    int tier;
    
    // implement the "static node()" method manually
    CREATE_FUNC(CreateResourceCardStatus);
    
    virtual void addStatusToSolarSystem(SolarSystemObject *solarSystemObject);
    
    //checks whether the status can be used
    virtual bool checkStart();
    
    //called when status is given to object
    virtual void applyStatus();
    
    //called when the status ends
    virtual void applyEndStatus();
    
    //checks whether the status should be destroyed
    virtual bool checkEnd();
    
    //called at end of turn
    virtual void updateStatus();
    
    virtual void updateStatus(Player *player);
    
    CCString *className;
    
};


#endif /* defined(__RogueDeck__CreateResourceCardStatus__) */
