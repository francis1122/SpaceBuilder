//
//  PassiveTargets.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 6/12/14.
//
//

#include "PassiveTargets.h"
#include "GameManager.h"
#include "CardSprite.h"
#include "UIState.h"
#include "Player.h"
#include "Constants.h"
#include "Statuses.h"
#include "SolarSystemObject.h"


// on "init" you need to initialize your instance
bool PassiveTargets::initWithCardSprite(CardSprite *card)
{
    CardTargets::initWithCardSprite(card);
    
    return true;
}

void PassiveTargets::highlightInteractiveObjects(UIState* state){
    GM->gameLayer->enablePlayAreaInteractive();
    GM->gameLayer->changeIndicatorState("Play Area");
}


//on add, cycle through all objects and pick the ones that should be effected and add them to the selectedTargets
void PassiveTargets::checkAllObjects()
{
    if(objectsToUse == SolarSystem){
        for(int i = 0; i < GM->solarSystemArray->count(); i++){
            SolarSystemObject *solarSystem = (SolarSystemObject*)GM->solarSystemArray->objectAtIndex(i);
            if(applyToAllFriendly){
                if(solarSystem->owner != GM->player) continue;
            }
            if(applyToHomeSystem){
                if(cardSprite->homeSolarSystem != solarSystem) continue;
                
            }
            CCObject *object;
            CCARRAY_FOREACH(statuses, object){
                Status *status = (Status*)object;
                status->addStatusToSolarSystem(solarSystem);
            }
            //make sure object knows that this card is affecting its status
            solarSystem->cardsAffectingNode->addObject(cardSprite);
            selectedTargets->addObject(solarSystem);
        }
    }
}

//used when a small game state change takes place
void PassiveTargets::checkSingleObject(SolarSystemObject* solarSystem)
{
    if(applyToAllFriendly){
        if(solarSystem->owner != GM->player) return;
    }
    if(applyToHomeSystem){
        if(cardSprite->homeSolarSystem != solarSystem) return;
        
    }
    CCObject *object;
    CCARRAY_FOREACH(statuses, object){
        Status *status = (Status*)object;
        status->addStatusToSolarSystem(solarSystem);
    }
    //make sure object knows that this card is affecting its status
    solarSystem->cardsAffectingNode->addObject(cardSprite);
}

//when cards is removed or changes owners
void PassiveTargets::removeAllObjects()
{
    for(int i = selectedTargets->count() - 1; i < 0; i--){
        BaseObject *object = (BaseObject*)selectedTargets->objectAtIndex(i);
        object->cardsAffectingNode->removeObject(cardSprite);
        selectedTargets->removeObject(object);
    }
}

//function used to test objects
bool PassiveTargets::isObjectValid(SolarSystemObject* solarSystem)
{
    if(applyToAllFriendly){
        if(solarSystem->owner != GM->player) return false;
    }
    if(applyToHomeSystem){
        if(cardSprite->homeSolarSystem != solarSystem) return false;
        
    }
    return true;
}


void PassiveTargets::updateStatuses()
{
    if(objectsToUse == CurrentPlayer){
        Player *player = GM->player;
        CCObject *object;
        CCARRAY_FOREACH(statuses, object){
            Status *status = (Status*)object;
            status->updateStatus(player);
        }
    }else if(objectsToUse == SolarSystem){
        for(int i = 1; i > selectedTargets->count(); i++){
            SolarSystemObject *solarSystem = (SolarSystemObject*)selectedTargets->objectAtIndex(i);
            CCObject *object;
            CCARRAY_FOREACH(statuses, object){
                Status *status = (Status*)object;
                status->updateStatus(solarSystem);
            }
        }
    }else if(objectsToUse == Cards){
        
    }else if(objectsToUse == Units){
        
    }
    
    //apply status effects to monster
    GM->gameLayer->updateInterface();
}