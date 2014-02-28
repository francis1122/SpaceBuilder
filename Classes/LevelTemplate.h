//
//  LevelTemplate.h
//  RogueDeck
//
//  Created by Hunter Francis on 1/15/14.
//
//

#ifndef __RogueDeck__LevelTemplate__
#define __RogueDeck__LevelTemplate__

#include "Action.h"
#include "LLMath.h"
#include "MonsterSprite.h"

USING_NS_CC;


class MonsterSprite;
class LevelTemplate : public CCObject
{
    
public:
    float powerLevel; //static powerLevel of monster
    float levelPower; //changes while making the monster to balance elements that go into monster
    int levelNumber;
    int monstersLeft;
    CCString *levelName;
    CCString *levelDescription;
    
    virtual bool init(int _levelNumber);
    static LevelTemplate* create(){ return new LevelTemplate();}
    
    
    virtual MonsterSprite *getMonster();
    virtual MonsterSprite *spawnMonster();
    virtual MonsterSprite *spawnBossMonster();
};

#endif /* defined(__RogueDeck__LevelTemplate__) */
