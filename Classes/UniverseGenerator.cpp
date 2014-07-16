//
//  UniverseGenerator.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 7/11/14.
//
//

#include "UniverseGenerator.h"
#include "CardFactory.h"
#include "LLMath.h"
#include "Player.h"
#include "GameManager.h"
#include "GameLayer.h"
#include "HandLayer.h"
#include "Statuses.h"
#include "CardTargets.h"
#include "Constants.h"
#include "AnimationManager.h"
#include "AnimationObject.h"
#include "CardSprite.h"
#include "Targets.h"
#include "SolarSystemObject.h"
#include "Constants.h"
#include "ResourceCardSprite.h"

USING_NS_CC;

CCArray *UniverseGenerator::createUniverse()
{
    CCArray *universeArray = new CCArray();
    universeArray->init();
    
    //add them to monster layer
    for(int i = 0; i < 6; i++){
        universeArray->addObject(createSystem());
    }
    

    ((SolarSystemObject*)universeArray->objectAtIndex(0))->setupHomeResourceSlots();
    
    return universeArray;
}

SolarSystemObject* UniverseGenerator::createSystem()
{
    SolarSystemObject *solarSystem = new SolarSystemObject();
    solarSystem->initWithSpriteFrameName("solarSystem_0");
    
    solarSystem->setPosition(ccp(LLMath::getDoubleValue(1400), LLMath::getDoubleValue(800)));
    //define size
    int size = arc4random()%3;
    if(size == 0){
        solarSystem->planetSize = Small;
        solarSystem->populationLimit = 3;
        solarSystem->setScale(.35);
        
    }else if(size == 1){
        solarSystem->planetSize = Medium;
        solarSystem->populationLimit = 5;
        solarSystem->setScale(.5);
    }else{
        solarSystem->planetSize = Large;
        solarSystem->populationLimit = 7;
        solarSystem->setScale(.65);
    }
    
    //define planetTypes
    int type = arc4random()%4;
    if(type == 0){
        solarSystem->planetType = Terran;
    }else if(type == 1){
        solarSystem->planetType = Arid;

    }else if(type == 2){
        solarSystem->planetType = Artic;
    }
    
    setupResourcesForSystem(solarSystem);
    

    //gameLayer->monsterLayer->addChild(solarSystem);
    
    CCString *name = new CCString();
    
    name->initWithFormat("Sol:%i", arc4random()%100);
    solarSystem->solarSystemName = name;
    solarSystem->nameLabel->setString(name->getCString());
    

    solarSystem->updateInterface();
    return solarSystem;
}

void UniverseGenerator::setupResourcesForSystem(SolarSystemObject *solarSystem)
{
    //make sure resources are clear
    solarSystem->cardArray->removeAllObjects();

    if(solarSystem->planetType == Terran){
        solarSystem->cardSlots = 4;
        //random cards should be added to planets on creation
        for(int i = 0; i < solarSystem->cardSlots; i++){
            ResourceCardSprite *card;
            if(i == 0){
                card = CardFactory::food();
                card->tier = 2;
            }else if(i == 1){
                card = CardFactory::production();
                card->tier = 2;
            }else if(i == 2){
                card = CardFactory::money();
                card->tier = 2;
            }else{
                card = CardFactory::tech();
                card->tier = 2;
            }
            card->setHomeSolarSystem(solarSystem);
            solarSystem->cardArray->addObject(card);
        }
    }
    
    if(solarSystem->planetType == Arid){
        solarSystem->cardSlots = 4;
        //random cards should be added to planets on creation
        for(int i = 0; i < solarSystem->cardSlots; i++){
            ResourceCardSprite *card;
            if(i == 0){
                card = CardFactory::food();
                card->tier = 1;
            }else if(i == 1){
                card = CardFactory::production();
                card->tier = 3;
            }else if(i == 2){
                card = CardFactory::money();
                card->tier = 2;
            }else{
                card = CardFactory::tech();
                card->tier = 2;
            }
            card->setHomeSolarSystem(solarSystem);
            solarSystem->cardArray->addObject(card);
        }
    }
    
    if(solarSystem->planetType == Artic){
        solarSystem->cardSlots = 3;
        //random cards should be added to planets on creation
        for(int i = 0; i < solarSystem->cardSlots; i++){
            ResourceCardSprite *card;
            if(i == 0){
                card = CardFactory::tech();
                card->tier = 4;
            }else if(i == 1){
                card = CardFactory::production();
                card->tier = 3;
            }else if(i == 2){
                card = CardFactory::money();
                card->tier = 2;
            }
            card->setHomeSolarSystem(solarSystem);
            solarSystem->cardArray->addObject(card);
        }
    }
}

