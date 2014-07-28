//
//  CreateResourceCardStatus.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 7/24/14.
//
//

#include "CreateResourceCardStatus.h"
#include "GameManager.h"
#include "Player.h"
#include "SolarSystemObject.h"
#include "ResourceCardSprite.h"
#include "CardFactory.h"


USING_NS_CC;


// on "init" you need to initialize your instance
bool CreateResourceCardStatus::initWithResourceCard(ResourceTypes _type, int _tier)
{
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    className = new CCString();
    className->initWithFormat("CreateResourceCardStatus");
    type = _type;
    tier = _tier;
    return true;
}

void CreateResourceCardStatus::addStatusToSolarSystem(SolarSystemObject *solarSystemObject)
{
    ResourceCardSprite *card;
    //create a resource card
    if(type == FoodResource){
        card = CardFactory::food();
        card->tier = tier;
    }else if(type == MoneyResource){
        card = CardFactory::money();
        card->tier = tier;
    }else if(type == ProductionResource){
        card = CardFactory::production();
        card->tier = tier;
    }else if(type == TechResource){
        card = CardFactory::tech();
        card->tier = tier;
    }else if(type == WasteResource){
        
    }
    
    //give resource card to system, if planet is owned, the function gives the card to the player
    solarSystemObject->addResourceCard(card);
}

//checks whether the status can be used
bool CreateResourceCardStatus::checkStart()
{
    return true;
}

//called when status is given to object
void CreateResourceCardStatus::applyStatus()
{
    //GameManager::sharedGameManager()->player->changeMoney(moneyOffset);
}

//called when the status ends
void CreateResourceCardStatus::applyEndStatus()
{
    
}

//checks whether the status should be destroyed
bool CreateResourceCardStatus::checkEnd()
{
    return true;
}

//called at end of turn
void CreateResourceCardStatus::updateStatus()
{
    
}

void CreateResourceCardStatus::updateStatus(Player *player)
{
    
}