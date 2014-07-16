//
//  ResourceCardSprite.h
//  RogueDeck
//
//  Created by Hunter Francis on 7/10/14.
//
//

#ifndef __RogueDeck__ResourceCardSprite__
#define __RogueDeck__ResourceCardSprite__

#include "cocos2d.h"
#include "Constants.h"
#include "CardSprite.h"


class CardTargets;
class SolarSystemObject;
class Player;
class PassiveTargets;
class ResourceCardSprite : public CardSprite
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool initWithSpriteFrameName(const char *pszSpriteFrameName);
    
    
    
    // implement the "static node()" method manually
    CREATE_FUNC(ResourceCardSprite);
    
    virtual void updateInterface();
    ResourceTypes resourceType;
    int tier;
    
    void generateResources();
};


#endif /* defined(__RogueDeck__ResourceCardSprite__) */
