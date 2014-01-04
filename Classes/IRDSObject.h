//
//  RDSObject.h
//  RogueDeck
//
//  Created by Hunter Francis on 12/19/13.
//
//

#ifndef __RogueDeck__IRDSObject__
#define __RogueDeck__IRDSObject__

#include "cocos2d.h"
USING_NS_CC;

class IRDSObject : public CCObject
{
    
public:
    double rdsProbability; // The chance for this item to drop
    bool rdsUnique;        // Only drops once per query
    bool rdsAlways;        // Drops always
    bool rdsEnabled;       // Can it drop now?
    
    virtual void checkIfUsable(float powerLevel);
};

#endif /* defined(__RogueDeck__IRDSObject__) */
