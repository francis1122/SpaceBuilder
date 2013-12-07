//
//  GainActionStatus.h
//  RogueDeck
//
//  Created by Hunter Francis on 12/4/13.
//
//

#ifndef __RogueDeck__GainActionStatus__
#define __RogueDeck__GainActionStatus__

#include "cocos2d.h"
#include "Status.h"

USING_NS_CC;

class MonsterSprite;
class GainActionStatus : public Status
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(int powerLevel);
    
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
    int actionGainAmount;
    
    
};

#endif /* defined(__RogueDeck__GainActionStatus__) */
