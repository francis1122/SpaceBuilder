//
//  PlayAbilityTargets.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 7/29/14.
//
//

#include "PlayAbilityTargets.h"
#include "PlayAbilityTargets.h"
#include "GameManager.h"
#include "CardSprite.h"
#include "MonsterLayer.h"
#include "SolarSystemDetailsLayer.h"
#include "UIState.h"
#include "Player.h"
#include "Constants.h"
#include "Statuses.h"
#include "SolarSystemObject.h"
#include "ShipModel.h"
#include "Ability.h"

// on "init" you need to initialize your instance
bool PlayAbilityTargets::init()
{
    
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    if(!BaseTargets::init()){
        return false;
    }
    
    objectsToUse = CurrentPlayer;
    //which objects to apply status to
    applyToAllFriendly =  false;
    applyToHomeSystem = false;
    targetFriendlySystems = false;
    targetNeutralSystems = false;
    
    
    return true;
}

void PlayAbilityTargets::highlightInteractiveObjects(UIState* state, Ability *ability){
    GM->gameLayer->enablePlayAreaInteractive();
    CCObject *object;
    CCARRAY_FOREACH(GM->solarSystemArray, object){
        SolarSystemObject *solarSystem = (SolarSystemObject*)object;
        if(this->isValidSolarSystem(solarSystem, ability)){
            solarSystem->setHighlighted(true);
        }
    }
    
    // GM->gameLayer->changeIndicatorState("Target System");
    
}

//checks whether the ability can be activated
bool PlayAbilityTargets::isAbilityActivatable(UIState* state, Ability *ability){
    
    
    int targetCount = 0;
    CCObject *object;
    CCARRAY_FOREACH(GM->solarSystemArray, object){
        SolarSystemObject *solarSystem = (SolarSystemObject*)object;
        if(this->isValidSolarSystem(solarSystem, ability)){
            targetCount++;
        }
    }
    
    
    if(targetCount >= targetAmount){
        return true;
    }else{
        return false;
    }
}



//targets objects to use ability on
bool PlayAbilityTargets::targetObjectWithTargetingState(CCTouch* touch, UIState* state, Ability *ability)
{
    CCPoint touchPoint = GM->gameLayer->monsterLayer->convertTouchToNodeSpace(touch);
    CCObject *object;
    CCARRAY_FOREACH(GM->solarSystemArray, object){
        SolarSystemObject *solarSystem = (SolarSystemObject*)object;
        CCRect collisionRect = CCRectMake(solarSystem->getPosition().x - solarSystem->getContentSize().width/2 * solarSystem->getScale(), solarSystem->getPosition().y - solarSystem->getContentSize().height/2 * solarSystem->getScale(), solarSystem->getContentSize().width * solarSystem->getScale(), solarSystem->getContentSize().height * solarSystem->getScale());
        if(collisionRect.containsPoint(touchPoint)){
            if(this->isValidSolarSystem(solarSystem, ability)){
                selectedTargets->addObject(solarSystem);
                return true;
            }
        }
    }
    
    return false;
}

// checks whether the ability can be used
bool PlayAbilityTargets::isAbilityReady(Ability *ability){
    if(selectedTargets->count() >= targetAmount){
        return true;
    }else{
        return false;
    }
}

void PlayAbilityTargets::initialChangeState(UIState *state, Ability *ability)
{
    //state->transitionToShipTargetingState(ability);
    
    //target local system
    if(isValidSolarSystem(ability->shipModel->location, ability)){
        //find target which is location of ship
        selectedTargets->addObject(ability->shipModel->location);
        //apply status which will be colonizing at first
        useAbility(ability);
        state->transitionToNormalState();
    }

}



//does what the ability should do
void PlayAbilityTargets::useAbility(Ability *ability){
    BaseTargets::useAbility();
    
    
    
    CCObject *object;
    CCARRAY_FOREACH(selectedTargets, object){
        //TODO: can target more than just monsters
        SolarSystemObject *solarSystem = (SolarSystemObject*)object;
        CCObject *object2;
        CCARRAY_FOREACH(statuses, object2){
            Status *status = (Status*)object2;
            status->addStatusToSolarSystemWithShip(solarSystem, ability->shipModel);
            //            status->addStatusToSolarSystem(solarSystem);
        }
    }
    
    //apply status effects to monster
    //    monster->updateInterface();
    
    GM->gameLayer->updateInterface();
    GM->afterCardPlayedStateCheck();
    //clear targetArray
    selectedTargets->removeAllObjects();
}

bool PlayAbilityTargets::isValidSolarSystem(SolarSystemObject *solarSystemObject, Ability *ability)
{

    bool isValid = false;
    if(targetFriendlySystems){
        if(solarSystemObject->owner){
            if(solarSystemObject->owner == GM->player){
                return true;
            }
        }
    }
    
    if(targetNeutralSystems){
        if(solarSystemObject->owner){
            
        }else{
            return true;
        }
    }
    return isValid;
}