//
//  ProductionOffsetStatus.h
//  RogueDeck
//
//  Created by Hunter Francis on 7/23/14.
//
//

#ifndef __RogueDeck__ProductionOffsetStatus__
#define __RogueDeck__ProductionOffsetStatus__

#include "cocos2d.h"
#include "Status.h"
USING_NS_CC;

class Player;
class CardSprite;
class SolarSystemObject;
class ProductionOffsetStatus : public Status
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool initWithProductionOffset(int _productionOffset);
    
    int productionOffset;
    
    // implement the "static node()" method manually
    CREATE_FUNC(ProductionOffsetStatus);
    
    virtual void addStatusToPlayer(Player *player);
    
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
    
    virtual void updateStatus(Player *player);
    
    virtual void updateStatus(SolarSystemObject *solarSystem);
    
    CCString *className;
    
    
};

#endif /* defined(__RogueDeck__ProductionOffsetStatus__) */
