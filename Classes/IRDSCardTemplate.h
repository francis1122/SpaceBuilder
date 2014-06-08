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

class IRDSCardTemplate : public IRDSObject
{
    
public:
    IRDSCardTemplate(std::string chosenClassName, double odds, float _minLevelRequired);
    IRDSCardTemplate(std::string chosenClassName, double odds, float _minLevelRequired, float _maxLevelRequired);
    float minLevelRequired;
    float maxLevelRequired;
    std::string className;
    virtual void checkIfUsable(float powerLevel);
};


#endif /* defined(__RogueDeck__IRDSCardTemplate__) */
