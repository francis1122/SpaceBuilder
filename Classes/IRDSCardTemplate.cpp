//
//  IRDSCardTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 12/20/13.
//
//

#include "IRDSCardTemplate.h"


IRDSCardTemplate::IRDSCardTemplate(std::string chosenClassName, double odds, float _minLevelRequired)
{
    rdsProbability = odds;
    className = chosenClassName;
    rdsEnabled = true;
    minLevelRequired = _minLevelRequired;
    maxLevelRequired = 10000000;
}

IRDSCardTemplate::IRDSCardTemplate(std::string chosenClassName, double odds, float _minLevelRequired, float _maxLevelRequired)
{
    rdsProbability = odds;
    className = chosenClassName;
    rdsEnabled = true;
    minLevelRequired = _minLevelRequired;
    maxLevelRequired = _maxLevelRequired;
}

void IRDSCardTemplate::checkIfUsable(float powerLevel){
    
    if(powerLevel < minLevelRequired && powerLevel < maxLevelRequired){
        rdsEnabled = false;
    }
}
