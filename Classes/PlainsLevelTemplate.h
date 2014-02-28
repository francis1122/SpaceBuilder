//
//  PlainsLevelTemplate.h
//  RogueDeck
//
//  Created by Hunter Francis on 1/15/14.
//
//

#ifndef __RogueDeck__PlainsLevelTemplate__
#define __RogueDeck__PlainsLevelTemplate__

#include "Action.h"
#include "LLMath.h"
#include "MonsterSprite.h"
#include "LevelTemplate.h"
USING_NS_CC;


class MonsterSprite;
class PlainsLevelTemplate : public LevelTemplate
{
    
public:
    virtual bool init(int _levelNumber);
    static LevelTemplate* create(){ return new PlainsLevelTemplate();}
    
    virtual MonsterSprite *spawnMonster();
    
    virtual MonsterSprite *spawnBossMonster();
};


#endif /* defined(__RogueDeck__PlainsLevelTemplate__) */
