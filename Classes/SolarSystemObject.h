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

class Player;
class SolarSystemObject : public BaseObject
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool initWithSpriteFrameName(const char *pszSpriteFrameName);
    
    // implement the "static node()" method manually
    CREATE_FUNC(SolarSystemObject);
    
    int cardSlots;
    //array for actual cards
    //CCArray
    int incomeGeneration;
    int populationFraction;
    int population;
    int populationLimit;
    
    Player *owner;
    
    void update();

    
};


#endif /* defined(__RogueDeck__SolarSystemObject__) */
