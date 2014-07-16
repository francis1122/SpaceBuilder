//
//  ResearchOffsetStatus.h
//  RogueDeck
//
//  Created by Hunter Francis on 6/29/14.
//
//

#ifndef __RogueDeck__ResearchOffsetStatus__
#define __RogueDeck__ResearchOffsetStatus__


#include "cocos2d.h"
#include "Status.h"
#include "Constants.h"
USING_NS_CC;

class Player;
class CardSprite;
class ResearchOffsetStatus : public Status
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool initWithResearchOffset(int _researchOffset, ResearchTypes _researchType);
    
    int researchOffset;
    ResearchTypes researchType;
    
    // implement the "static node()" method manually
    CREATE_FUNC(ResearchOffsetStatus);
    
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
    
    CCString *className;
    
    
};


#endif /* defined(__RogueDeck__ResearchOffsetStatus__) */
