//
//  IRDSMonsterTemplate.h
//  RogueDeck
//
//  Created by Hunter Francis on 1/9/14.
//
//

#ifndef __RogueDeck__IRDSMonsterTemplate__
#define __RogueDeck__IRDSMonsterTemplate__

#include "Action.h"
#include "IRDSObject.h"

class IRDSMonsterTemplate : public IRDSObject
{
    
public:
    IRDSMonsterTemplate(std::string chosenClassName, double odds, float _minLevelRequired);
    float minLevelRequired;
    std::string className;
    virtual void checkIfUsable(float powerLevel);
};



#endif /* defined(__RogueDeck__IRDSMonsterTemplate__) */
