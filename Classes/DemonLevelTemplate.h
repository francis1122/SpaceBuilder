//
//  DemonLevelTemplate.h
//  RogueDeck
//
//  Created by Hunter Francis on 2/23/14.
//
//

#ifndef __RogueDeck__DemonLevelTemplate__
#define __RogueDeck__DemonLevelTemplate__

#include "Action.h"
#include "LLMath.h"
#include "MonsterSprite.h"
#include "LevelTemplate.h"
USING_NS_CC;


class MonsterSprite;
class DemonLevelTemplate : public LevelTemplate
{
    
public:
    virtual bool init(int _levelNumber);
    
    static LevelTemplate* create(){ return new DemonLevelTemplate();}
    virtual MonsterSprite *getMonster();
    virtual MonsterSprite *spawnMonster();
    
    virtual MonsterSprite *spawnBossMonster();
};


#endif /* defined(__RogueDeck__DemonLevelTemplate__) */
