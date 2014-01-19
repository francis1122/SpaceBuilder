//
//  InstantKillMonsterStatus.h
//  RogueDeck
//
//  Created by Hunter Francis on 1/18/14.
//
//

#ifndef __RogueDeck__InstantKillMonsterStatus__
#define __RogueDeck__InstantKillMonsterStatus__

#include "cocos2d.h"
#include "Status.h"

USING_NS_CC;

class MonsterSprite;

class InstantKillMonsterStatus : public Status
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
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

    
};

#endif /* defined(__RogueDeck__InstantKillMonsterStatus__) */
