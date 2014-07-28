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
    for(int i = 0; i < 14; i++){
        SolarSystemObject *solarSystem = createSystem();
        
        //check if system isn't too close another system
        while(isOverlapping(solarSystem, universeArray)){
            CCLog("overlapping");
            solarSystem->setPosition(ccp(LLMath::getDoubleValue(1600), LLMath::getDoubleValue(1000)));
        }
        universeArray->addObject(solarSystem);
    }
    
    createConnections(universeArray);

    ((SolarSystemObject*)universeArray->objectAtIndex(0))->setupHomeResourceSlots();
    
    return universeArray;
}

SolarSystemObject* UniverseGenerator::createSystem()
{
    SolarSystemObject *solarSystem = new SolarSystemObject();
    //define planetTypes
    int type = arc4random()%3;
    if(type == 0){
        solarSystem->initWithSpriteFrameName("solarSystem_0");
        solarSystem->planetType = Terran;
    }else if(type == 1){
        solarSystem->initWithSpriteFrameName("planets_arid");
        solarSystem->planetType = Arid;
        
    }else if(type == 2){
        solarSystem->initWithSpriteFrameName("planets_water");
        solarSystem->planetType = Artic;
    }

    
    solarSystem->setPosition(ccp(LLMath::getDoubleValue(2000), LLMath::getDoubleValue(1200)));
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
                card->tier = 1;
            }
            card->setHomeSolarSystem(solarSystem);
            solarSystem->cardArray->addObject(card);
        }
    }
    
    if(solarSystem->planetType == Artic){
        solarSystem->cardSlots = 4;
        //random cards should be added to planets on creation
        for(int i = 0; i < solarSystem->cardSlots; i++){
            ResourceCardSprite *card;
            if(i == 0){
                card = CardFactory::tech();
                card->tier = 4;
            }else if(i == 1){
                card = CardFactory::production();
                card->tier = 1;
            }else if(i == 2){
                card = CardFactory::money();
                card->tier = 1;
            }else if(i == 3){
                card = CardFactory::waste();
            }
            card->setHomeSolarSystem(solarSystem);
            solarSystem->cardArray->addObject(card);
        }
    }
}

bool UniverseGenerator::isOverlapping(SolarSystemObject *solarSystem, CCArray *universeArray)
{
    //check distance between all stars in galaxy
    for(int i = 0; i < universeArray->count(); i++){
        SolarSystemObject *solarSystemB = (SolarSystemObject*)universeArray->objectAtIndex(i);
        if(ccpDistance(solarSystem->getPosition(), solarSystemB->getPosition()) < 300){
            return true;
        }
    }
    return false;
}

void UniverseGenerator::createConnections(CCArray *universeArray)
{
    //create connections between systems
    for(int i = 0; i < universeArray->count(); i++){
        SolarSystemObject *solarSystemA = (SolarSystemObject*)universeArray->objectAtIndex(i);
        for(int j = 0; j < universeArray->count(); j++){
            SolarSystemObject *solarSystemB = (SolarSystemObject*)universeArray->objectAtIndex(j);
            if(solarSystemA != solarSystemB){
                //test distance
                float distance = ccpDistance(solarSystemA->getPosition(), solarSystemB->getPosition());
                if(distance < 370){
                    CCLog("connection distance: %f", distance);
                    //check if path is clear
                    if(isOpenPath(solarSystemA, solarSystemB, universeArray)){
                        //create path between A and B
                        if(!solarSystemA->connectedSystems->containsObject(solarSystemB)){
                            solarSystemA->connectedSystems->addObject(solarSystemB);
                        }
                        if(!solarSystemB->connectedSystems->containsObject(solarSystemA)){
                            solarSystemB->connectedSystems->addObject(solarSystemA);
                        }
                    }
                }
                
            }
        }
    }
    
    //create connections between systems
    for(int i = 0; i < universeArray->count(); i++){
        SolarSystemObject *solarSystemA = (SolarSystemObject*)universeArray->objectAtIndex(i);
        for(int j = 0; j < universeArray->count(); j++){
            SolarSystemObject *solarSystemB = (SolarSystemObject*)universeArray->objectAtIndex(j);
            if(solarSystemA != solarSystemB){
                //test distance
                float distance = ccpDistance(solarSystemA->getPosition(), solarSystemB->getPosition());
                if(distance < 450){
                    CCLog("connection distance: %f", distance);
                    //check if path is clear
                    if(isOpenPath(solarSystemA, solarSystemB, universeArray)){
                        //create path between A and B
                        if(!solarSystemA->connectedSystems->containsObject(solarSystemB)){
                            solarSystemA->connectedSystems->addObject(solarSystemB);
                        }
                        if(!solarSystemB->connectedSystems->containsObject(solarSystemA)){
                            solarSystemB->connectedSystems->addObject(solarSystemA);
                        }
                    }
                }
                
            }
        }
    }
    
    
    //create connections between systems
    for(int i = 0; i < universeArray->count(); i++){
        SolarSystemObject *solarSystemA = (SolarSystemObject*)universeArray->objectAtIndex(i);
        for(int j = 0; j < universeArray->count(); j++){
            SolarSystemObject *solarSystemB = (SolarSystemObject*)universeArray->objectAtIndex(j);
            if(solarSystemA != solarSystemB){
                //test distance
                float distance = ccpDistance(solarSystemA->getPosition(), solarSystemB->getPosition());
                if(distance < 550){
                    CCLog("connection distance: %f", distance);
                    //check if path is clear
                    if(isOpenPath(solarSystemA, solarSystemB, universeArray)){
                        //create path between A and B
                        if(!solarSystemA->connectedSystems->containsObject(solarSystemB)){
                            solarSystemA->connectedSystems->addObject(solarSystemB);
                        }
                        if(!solarSystemB->connectedSystems->containsObject(solarSystemA)){
                            solarSystemB->connectedSystems->addObject(solarSystemA);
                        }
                    }
                }
                
            }
        }
    }
    
    
}



bool UniverseGenerator::isOpenPath(SolarSystemObject *solarSystemA, SolarSystemObject *solarSystemB, CCArray *universeArray)
{
    //check if possible route betwen a and b intersects other already setup routes
    for(int i = 0; i < universeArray->count(); i++){
        SolarSystemObject *solarSystemC = (SolarSystemObject*)universeArray->objectAtIndex(i);
        if(solarSystemC != solarSystemA && solarSystemC != solarSystemB){
            CCArray *existingConnections = solarSystemC->connectedSystems;
            for(int j = 0; j < existingConnections->count(); j++){
                SolarSystemObject *solarSystemD = (SolarSystemObject*) existingConnections->objectAtIndex(j);
                
                //check for intersections
                if(LLMath::intersectionCheck(solarSystemA->getPosition(), solarSystemB->getPosition(), solarSystemC->getPosition(), solarSystemD->getPosition())){
                    return false;
                    
                }
                
            }
        }

    }
    
    return true;
}

