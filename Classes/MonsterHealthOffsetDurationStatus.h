//
//  MonsterHealthOffsetDurationStatus.h
//  RogueDeck
//
//  Created by Hunter Francis on 1/4/14.
//
//

#ifndef __RogueDeck__MonsterHealthOffsetDurationStatus__
#define __RogueDeck__MonsterHealthOffsetDurationStatus__

#include "cocos2d.h"
#include "Status.h"

USING_NS_CC;

class MonsterSprite;

class MonsterHealthOffsetDurationStatus : public Status
{
public:
    virtual bool initWithHealthOffset(int healthOffset, int duration);
    
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
    virtual void updateStatus(MonsterSprite *monster);
    
    //specific status variables
    int monsterHealthOffsetAmount;
    int duration;
    
    int isPreemptive;
    
    
};

#endif /* defined(__RogueDeck__MonsterHealthOffsetDurationStatus__) */
