//
//  AbilityTargets.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 7/29/14.
//
//

#include "AbilityTargets.h"
#include "CardTargets.h"
#include "GameManager.h"
#include "CardSprite.h"
#include "UIState.h"
#include "Player.h"
#include "Statuses.h"
#include "GameLayer.h"
#include "Constants.h"
#include "ShipModel.h"



USING_NS_CC;


// on "init" you need to initialize your instance
bool AbilityTargets::init()
{
    
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    if(!BaseTargets::init()){
        return false;
    }
    
    CCString *string = new CCString();
    string->initWithFormat("ResearchHolder");
    normalCommandImage = string;
    selectedCommandImage = string;
    disabledCommandImage = string;
    
    objectsToUse = CurrentPlayer;
    //which objects to apply status to
    applyToAllFriendly =  false;
    applyToHomeSystem = false;
    
    return true;
}

void AbilityTargets::highlightInteractiveObjects(UIState* state, Ability *ability){

}


//checks whether the ability can be activated
bool AbilityTargets::isAbilityActivatable(UIState* state, Ability *ability){
    return false;
}

// checks whether the ability can be used
bool AbilityTargets::isAbilityReady(Ability *ability){
    return false;
}

//targets objects to use ability on
bool AbilityTargets::targetObjectWithTargetingState(CCTouch* touch, UIState* state, Ability *ability)
{
    return false;
}

void AbilityTargets::initialChangeState(UIState *state, Ability *ability)
{
    state->transitionToShipTargetingState(ability);
}



//does what the ability should do
void AbilityTargets::useAbility(Ability *ability){
    BaseTargets::useAbility();
}




