//
//  IRDSCardTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 12/20/13.
//
//

#include "IRDSCardTemplate.h"


IRDSCardTemplate::IRDSCardTemplate(std::string chosenClassName, double odds, float _minLevelRequired){
    rdsProbability = odds;
    className = chosenClassName;
    rdsEnabled = true;
    minLevelRequired = _minLevelRequired;
}

void IRDSCardTemplate::checkIfUsable(float powerLevel){
    
    if(powerLevel < minLevelRequired){
        rdsEnabled = false;
    }
}
