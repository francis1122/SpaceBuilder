//
//  ComboStatus.h
//  RogueDeck
//
//  Created by Hunter Francis on 2/5/14.
//
//

#ifndef __RogueDeck__ComboStatus__
#define __RogueDeck__ComboStatus__


#include "Status.h"

USING_NS_CC;

class MonsterSprite;

class ComboStatus : public Status
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(int powerLevel);
    virtual bool initWithStatus(Status *status);
    virtual void addStatusToGameObject(MonsterSprite *monster);
    virtual void addStatusToCardSprite(CardSprite *card);
    
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
    Status *comboStatus;
    
    
};


#endif /* defined(__RogueDeck__ComboStatus__) */
