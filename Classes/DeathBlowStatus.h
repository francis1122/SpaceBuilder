//
//  DeathBlowStatus.h
//  RogueDeck
//
//  Created by Hunter Francis on 12/6/13.
//
//

#ifndef __RogueDeck__DeathBlowStatus__
#define __RogueDeck__DeathBlowStatus__

#include "Status.h"

USING_NS_CC;

class MonsterSprite;

class DeathBlowStatus : public Status
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(int powerLevel);
    virtual bool initWithStatus(Status *status);
    virtual void addStatusToGameObject(MonsterSprite *monster);
    
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
    
    //specific status variables
    Status *deathStatus;
    
    
};

#endif /* defined(__RogueDeck__DeathBlowStatus__) */
