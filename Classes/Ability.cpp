//
//  Ability.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 7/29/14.
//
//

#include "Ability.h"
#include "Targets.h"
#include "Constants.h"
#include "GameLayer.h"
#include "GameManager.h"


bool Ability::init()
{
    return true;
}

bool Ability::checkIfActivatable()
{
    if(targets->isAbilityActivatable(GM->gameLayer->getCurrentState(), this)){
        return true;
    }
    return false;
}

//called when ability is tapped
bool Ability::activateAbility()
{
    CCLog("this worked");
    if(targets->isAbilityActivatable(GM->gameLayer->getCurrentState(), this)){
        targets->initialChangeState( GM->gameLayer->getCurrentState(), this);
        return true;
    }
    return false;
}
