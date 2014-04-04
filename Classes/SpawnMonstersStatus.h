//
//  SpawnMonstersStatus.h
//  RogueDeck
//
//  Created by Hunter Francis on 3/5/14.
//
//

#ifndef __RogueDeck__SpawnMonstersStatus__
#define __RogueDeck__SpawnMonstersStatus__


#include "Status.h"

USING_NS_CC;

class MonsterSprite;

class SpawnMonstersStatus : public Status
{
public:
    
    virtual bool init();
    
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
    
    virtual void updateStatus(MonsterSprite *monster);
    
    
    
};

#endif /* defined(__RogueDeck__SpawnMonstersStatus__) */
