//
//  MonsterHealthOffsetStatus.h
//  RogueDeck
//
//  Created by Hunter Francis on 11/21/13.
//
//

#ifndef __RogueDeck__MonsterHealthOffsetStatus__
#define __RogueDeck__MonsterHealthOffsetStatus__

#include "cocos2d.h"
#include "Status.h"

USING_NS_CC;

class MonsterSprite;

class MonsterHealthOffsetStatus : public Status
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(int powerLevel);
    virtual bool initWithHealthOffset(int healthOffset);
    
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
    int monsterHealthOffsetAmount;
    
};

#endif /* defined(__RogueDeck__MonsterHealthOffsetStatus__) */
