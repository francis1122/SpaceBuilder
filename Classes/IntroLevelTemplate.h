//
//  IntroLevelTemplate.h
//  RogueDeck
//
//  Created by Hunter Francis on 1/15/14.
//
//

#ifndef __RogueDeck__IntroLevelTemplate__
#define __RogueDeck__IntroLevelTemplate__

#include "LevelTemplate.h"
#include "Action.h"
#include "LLMath.h"
#include "MonsterSprite.h"

USING_NS_CC;


class MonsterSprite;
class IntroLevelTemplate : public LevelTemplate
{
    
public:

    static LevelTemplate* create(){ return new IntroLevelTemplate();}
    
    virtual MonsterSprite *spawnMonster();
};

#endif /* defined(__RogueDeck__IntroLevelTemplate__) */
