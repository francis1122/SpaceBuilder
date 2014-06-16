//
//  PassiveTargets.h
//  RogueDeck
//
//  Created by Hunter Francis on 6/12/14.
//
//

#ifndef __RogueDeck__PassiveTargets__
#define __RogueDeck__PassiveTargets__

#include "cocos2d.h"
#include "CardTargets.h"

class CardSprite;
class UIState;
class BaseObject;
class SolarSystemObject;


USING_NS_CC;

class PassiveTargets : public CardTargets
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool initWithCardSprite(CardSprite *card);
    
    //array of statuses
    //inital statuses cannot require targets, gets called before statuses get's called and before state change
    
    
    virtual void highlightInteractiveObjects(UIState* state);

    //on add, cycle through all objects and pick the ones that should be effected and add them to the selectedTargets
    virtual void checkAllObjects();
    
    //used when a small game state change takes place
    virtual void checkSingleObject(SolarSystemObject* solarSystem);
    
    //when cards is removed or changes owners
    virtual void removeAllObjects();
    
    //function used to test objects
    virtual bool isObjectValid(SolarSystemObject* solarSystem);
    
    void updateStatuses();
    
};

#endif /* defined(__RogueDeck__PassiveTargets__) */
