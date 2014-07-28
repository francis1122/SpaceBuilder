//
//  MoneyOffsetStatus.h
//  RogueDeck
//
//  Created by Hunter Francis on 6/8/14.
//
//

#ifndef __RogueDeck__MoneyOffsetStatus__
#define __RogueDeck__MoneyOffsetStatus__

#include "cocos2d.h"
#include "Status.h"
USING_NS_CC;

class Player;
class CardSprite;
class MoneyOffsetStatus : public Status
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool initWithMoneyOffset(int _moneyOffset);
    
    int moneyOffset;
    
    // implement the "static node()" method manually
    CREATE_FUNC(MoneyOffsetStatus);
    
    virtual void addStatusToPlayer(Player *player);
    
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
    
    virtual void updateStatus(SolarSystemObject *solarSystem);
    
    CCString *className;
    
    
};


#endif /* defined(__RogueDeck__MoneyOffsetStatus__) */
