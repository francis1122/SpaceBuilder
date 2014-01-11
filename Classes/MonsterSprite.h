//
//  MonsterSprite.h
//  RogueDeck
//
//  Created by Hunter Francis on 11/20/13.
//
//

#ifndef __RogueDeck__MonsterSprite__
#define __RogueDeck__MonsterSprite__

#include "cocos2d.h"
#include "BaseObject.h"

class MonsterSprite : public BaseObject
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static node()" method manually
    CREATE_FUNC(MonsterSprite);
    
    cocos2d::CCLabelTTF *lifeLabel;
    cocos2d::CCLabelTTF *attackLabel;
    
    cocos2d::CCLabelTTF *detailsLabel;
    
    cocos2d::CCSprite *glowSprite;
    
    //monster variables
    int life;
    int attack;
    int location;
    int lane;
    float monsterLevel;
    
    
    void updateInterface();
    void turnUpdate();
    void onDeath();
    
    //effects that happen when the monster dies
    cocos2d::CCArray *afterDeathEffectArray;
    
    //effects that get added on attack, this array is cleared at the end of each attack
    cocos2d::CCArray *killingBlowArray;
    cocos2d::CCArray *activeStatusArray;
    
    void enableInteractive();
    void disableInteractive();
    
private:
    
};

#endif /* defined(__RogueDeck__MonsterSprite__) */
