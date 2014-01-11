//
//  IRDSMonsterTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/9/14.
//
//

#include "IRDSMonsterTemplate.h"



IRDSMonsterTemplate::IRDSMonsterTemplate(std::string chosenClassName, double odds, float _minLevelRequired){
    rdsProbability = odds;
    className = chosenClassName;
    rdsEnabled = true;
    minLevelRequired = _minLevelRequired;
}

void IRDSMonsterTemplate::checkIfUsable(float powerLevel){
    
    if(powerLevel < minLevelRequired){
        rdsEnabled = false;
    }
}
