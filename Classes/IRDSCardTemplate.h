//
//  IRDSCardTemplate.h
//  RogueDeck
//
//  Created by Hunter Francis on 12/20/13.
//
//

#ifndef __RogueDeck__IRDSCardTemplate__
#define __RogueDeck__IRDSCardTemplate__

#include "IRDSObject.h"
#include "Action.h"

class IRDSCardTemplate : public IRDSObject
{
    
public:
    IRDSCardTemplate(std::string chosenClassName, double odds, float _minLevelRequired);
    float minLevelRequired;
    std::string className;
    virtual void checkIfUsable(float powerLevel);
};


#endif /* defined(__RogueDeck__IRDSCardTemplate__) */
