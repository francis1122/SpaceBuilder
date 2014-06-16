//
//  PopulationOffsetStatus.h
//  RogueDeck
//
//  Created by Hunter Francis on 6/9/14.
//
//

#ifndef __RogueDeck__PopulationOffsetStatus__
#define __RogueDeck__PopulationOffsetStatus__

#include "cocos2d.h"
#include "Status.h"
USING_NS_CC;

class Player;
class CardSprite;
class SolarSystemObject;
class PopulationOffsetStatus : public Status
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool initWithPopulationOffset(int _populationOffset, int _populationFractionOffset);
    
    int populationOffset;
    int populationFractionOffset;
    
    // implement the "static node()" method manually
    CREATE_FUNC(PopulationOffsetStatus);
    
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


#endif /* defined(__RogueDeck__PopulationOffsetStatus__) */
