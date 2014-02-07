//
//  DragonBossTemplate.h
//  RogueDeck
//
//  Created by Hunter Francis on 1/30/14.
//
//

#ifndef __RogueDeck__DragonBossTemplate__
#define __RogueDeck__DragonBossTemplate__

#include "Action.h"
#include "LLMath.h"
#include "MonsterSprite.h"
#include "MonsterTemplate.h"
USING_NS_CC;


class MonsterSprite;
class DragonBossTemplate : public MonsterTemplate
{
    
public:
    static const std::string CLASS_NAME;
    static MonsterTemplate* create(){ return new DragonBossTemplate();}
    
    
    virtual void addAugmentationStatus();
    virtual void addMainStats();
    virtual void addRewards();
    
    
};

#endif /* defined(__RogueDeck__DragonBossTemplate__) */
