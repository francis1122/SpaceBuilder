//
//  ShipSprite.h
//  RogueDeck
//
//  Created by Hunter Francis on 7/28/14.
//
//

#ifndef __RogueDeck__ShipSprite__
#define __RogueDeck__ShipSprite__

#include "cocos2d.h"
#include "BaseObject.h"
#include "Constants.h"



class CardSprite;
class Player;
class BuildingObject;
class ResourceCardSprite;
class ShipModel;

class ShipSprite : public BaseObject
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool initWithSpriteFrameName(const char *pszSpriteFrameName);
    
    ShipModel *shipModel;
    
    // implement the "static node()" method manually
    CREATE_FUNC(ShipSprite);
    

    void updateInterface();
};

#endif /* defined(__RogueDeck__ShipSprite__) */
