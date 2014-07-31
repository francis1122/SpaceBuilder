//
//  Ability.h
//  RogueDeck
//
//  Created by Hunter Francis on 7/29/14.
//
//

#ifndef __RogueDeck__Ability__
#define __RogueDeck__Ability__

#include "cocos2d.h"

USING_NS_CC;

class MonsterSprite;
class CardSprite;
class Player;
class SolarSystemObject;
class ShipModel;
class AbilityTargets;

class Ability : public CCObject
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static node()" method manually
    CREATE_FUNC(Ability);
    
    ShipModel *shipModel;
    
    AbilityTargets *targets;
    
    
    //called when ability is tapped
    virtual bool checkIfActivatable();
    virtual bool activateAbility();
    
    
};

#endif /* defined(__RogueDeck__Ability__) */
