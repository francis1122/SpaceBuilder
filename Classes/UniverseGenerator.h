//
//  UniverseGenerator.h
//  RogueDeck
//
//  Created by Hunter Francis on 7/11/14.
//
//

#ifndef __RogueDeck__UniverseGenerator__
#define __RogueDeck__UniverseGenerator__

#include "cocos2d.h"
#include "GameLayer.h"
#include "CardSprite.h"
#include "Player.h"

USING_NS_CC;

class SolarSystemObject;
class UniverseGenerator
{
    
public:
    UniverseGenerator();
    
    static CCArray *createUniverse();

    static SolarSystemObject* createSystem();
    
    static void setupResourcesForSystem(SolarSystemObject *solarSystem);
    
    static bool isOverlapping(SolarSystemObject *solarSystem, CCArray *universeArray);
    
    static void createConnections(CCArray *universeArray);
    
    static bool isOpenPath(SolarSystemObject *solarSystemA, SolarSystemObject *solarSystemB, CCArray *universeArray);
};

#endif /* defined(__RogueDeck__UniverseGenerator__) */
