//
//  AllMonsterStatus.h
//  RogueDeck
//
//  Created by Hunter Francis on 2/17/14.
//
//

#ifndef __RogueDeck__AllMonsterStatus__
#define __RogueDeck__AllMonsterStatus__

#include "cocos2d.h"
#include "Status.h"

USING_NS_CC;

class MonsterSprite;

class AllMonsterStatus : public Status
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool initWithStatus(Status *_status);
    
    //status must require a monster target
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
    Status *status;
    
    
};

#endif /* defined(__RogueDeck__AllMonsterStatus__) */
