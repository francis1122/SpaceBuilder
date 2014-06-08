//
//  MonsterLayer.h
//  RogueDeck
//
//  Created by Hunter Francis on 1/3/14.
//
//

#ifndef __RogueDeck__MonsterLayer__
#define __RogueDeck__MonsterLayer__

#include "cocos2d.h"

USING_NS_CC;

class MonsterLayer : public CCLayer
{
public:
    
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
//    CCArray *monsterSpawnArray;
    
    
    // implement the "static node()" method manually
    CREATE_FUNC(MonsterLayer);
    
    void updateInterface();
private:
    
};

#endif /* defined(__RogueDeck__MonsterLayer__) */
