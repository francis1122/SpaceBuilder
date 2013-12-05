//
//  MonsterGenerator.h
//  RogueDeck
//
//  Created by Hunter Francis on 11/26/13.
//
//

#ifndef __RogueDeck__MonsterGenerator__
#define __RogueDeck__MonsterGenerator__

#include "cocos2d.h"
USING_NS_CC;
class MonsterSprite;

class MonsterGenerator
{
private:
    //Constructor
    MonsterGenerator();
    
    //Instance of the singleton
    static MonsterGenerator* m_mySingleton;
    
public:
    //Get instance of singleton
    static MonsterGenerator* sharedGameManager();
  
    MonsterSprite* createMonster(int powerLevel);
    
    
};

#endif /* defined(__RogueDeck__MonsterGenerator__) */
