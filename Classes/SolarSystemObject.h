//
//  SolarSystemObject.h
//  RogueDeck
//
//  Created by Hunter Francis on 6/7/14.
//
//

#ifndef __RogueDeck__SolarSystemObject__
#define __RogueDeck__SolarSystemObject__

#include <iostream>
#include "cocos2d.h"
#include "BaseObject.h"
#include "Constants.h"



class CardSprite;
class Player;
class BuildingObject;
class ResourceCardSprite;
class SolarSystemObject : public BaseObject
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool initWithSpriteFrameName(const char *pszSpriteFrameName);
    
    //should only get called during planet creation
    void setupHomeResourceSlots();
    void setupResourceSlots(int slots);
    
    // implement the "static node()" method manually
    CREATE_FUNC(SolarSystemObject);
    
    CCArray *connectedSystems;
    
    int cardSlots;
    CCArray *cardArray;
    //array for actual cards
    
    int buildingSlots;
    CCArray *buildingsArray;
    
    //add structure
    void addBuilding(BuildingObject *building);
    
    //remove structure
    void removeBuilding(BuildingObject *building);
    
    int populationFraction;
    int populationGrowth;
    int population;
    int populationLimit;
    CCString *solarSystemName;
    
    CCLabelTTF *populationLabel;
    CCLabelTTF *nameLabel;
    
    CCSprite *infoSprite;
    
    PlanetType planetType;
    PlanetSize planetSize;
    
    Player *owner;
    
    CCLabelTTF *resourceGeneration;
//    CCLabelTTF *foodGeneration;
//    CCLabelTTF *productionGeneration;
  //  CCLabelTTF *moneyGeneration;
//    CCLabelTTF *scienceGeneration;
    
    
    
    void update();
    void updateInterface();
    int getSystemsResourceTier(ResourceTypes type);
    bool addResourceCard(ResourceCardSprite* card);
    void populationOffset(int populationOffset, int populationFractionOffset);
    void setHighlighted(bool enabled);
    
    void replaceCardAtIndex(CardSprite *card, int index);
};


#endif /* defined(__RogueDeck__SolarSystemObject__) */
