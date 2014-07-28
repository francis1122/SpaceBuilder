//
//  PlayAreaTargets.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/10/14.
//
//

#include "PlayAreaTargets.h"
#include "GameManager.h"
#include "CardSprite.h"
#include "UIState.h"
#include "Player.h"
#include "Constants.h"
#include "Statuses.h"
#include "SolarSystemObject.h"
#include "ResourceCardSprite.h"
#include "ResourceCardInfoLayer.h"


// on "init" you need to initialize your instance
bool PlayAreaTargets::initWithCardSprite(CardSprite *card)
{
    CardTargets::initWithCardSprite(card);
    
    
    return true;
}

void PlayAreaTargets::highlightInteractiveObjects(UIState* state){
    if(cardSprite->cardType == Resource){
        GM->gameLayer->resourceCardInfoLayer->setVisible(true);
        GM->gameLayer->resourceCardInfoLayer->setupInterface((ResourceCardSprite*)cardSprite);
    }
//    GM->gameLayer->enablePlayAreaInteractive();
//    GM->gameLayer->changeIndicatorState("Play Area");
}

void PlayAreaTargets::highlightNextInteractiveObjects(UIState* state){
    CCLog("shouldn't call this");
}

//checks whether the ability can be activated
bool PlayAreaTargets::isAbilityActivatable(UIState* state){
    return true;
}

//targets objects to use ability on
bool PlayAreaTargets::targetObjectWithHandCard(CCTouch* touch, UIState* state, CardSprite *card){
    
    return state->cardInPlayArea(card);
}

// checks whether the ability can be used
bool PlayAreaTargets::isAbilityReady(){
    return true;
}

//changes the state
void PlayAreaTargets::changeState(UIState* state, CardSprite *card){
    
}

void PlayAreaTargets::useInitialAbility(){
    CCObject *object;
    CCARRAY_FOREACH(initialStatuses, object){
        Status *status = (Status*)object;
        status->applyStatus();
    }
    
    //    GM->player->organizeHand();
    //    GM->player->organizePlayedCards();
    GM->gameLayer->updateInterface();
}

//does what the ability should do
void PlayAreaTargets::useAbility(){
    CardTargets::useAbility();
    //do status
    
    if(cardSprite->cardType == Resource){
        //add resource effects
        ResourceCardSprite *card = (ResourceCardSprite*)cardSprite;
        card->generateResources();
        
    }else{
        
        CCObject *object;
        
        if(objectsToUse == CurrentPlayer){
            CCARRAY_FOREACH(statuses, object){
                Status *status = (Status*)object;
                status->addStatusToPlayer(GM->player);
            }
        }else if(objectsToUse == SolarSystem){
            for(int i = 0; i < GM->solarSystemArray->count(); i++){
                SolarSystemObject *solarSystem = (SolarSystemObject*)GM->solarSystemArray->objectAtIndex(i);
                if(applyToAllFriendly){
                    if(solarSystem->owner != GM->player) continue;  
                }
                if(applyToHomeSystem){
                    if(cardSprite->homeSolarSystem != solarSystem) continue;
                    
                }
                CCARRAY_FOREACH(statuses, object){
                    Status *status = (Status*)object;
                    status->addStatusToSolarSystem(solarSystem);
                }
            }
            
        }else if(objectsToUse == Cards){
            
        }else if(objectsToUse == Units){
            
        }
    }
    
    
    //apply status effects to monster
    GM->gameLayer->updateInterface();
    GM->afterCardPlayedStateCheck();
    //clear targetArray
    selectedTargets->removeAllObjects();
    if(cardSprite->cardType == Resource){
        GM->gameLayer->resourceCardInfoLayer->setVisible(false);
    }
}

