//
//  OffsetMonsterLocation.h
//  RogueDeck
//
//  Created by Hunter Francis on 2/21/14.
//
//

#ifndef __RogueDeck__OffsetMonsterLocationStatus__
#define __RogueDeck__OffsetMonsterLocationStatus__

#include "cocos2d.h"
#include "Status.h"

USING_NS_CC;

class MonsterSprite;

class OffsetMonsterLocationStatus : public Status
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(int powerLevel);
    virtual bool initWithLocationOffset(int healthOffset);
    
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
    int locationOffset;
    
};


#endif /* defined(__RogueDeck__OffsetMonsterLocationStatus__) */
