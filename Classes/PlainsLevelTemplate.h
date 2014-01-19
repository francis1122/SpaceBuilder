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
    
    static LevelTemplate* create(){ return new PlainsLevelTemplate();}
    
    virtual MonsterSprite *spawnMonster();
};


#endif /* defined(__RogueDeck__PlainsLevelTemplate__) */
