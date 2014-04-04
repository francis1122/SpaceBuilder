//
//  ArcherBossTemplate.h
//  RogueDeck
//
//  Created by Hunter Francis on 2/27/14.
//
//

#ifndef __RogueDeck__ArcherBossTemplate__
#define __RogueDeck__ArcherBossTemplate__

#include "Action.h"
#include "LLMath.h"
#include "MonsterSprite.h"
#include "MonsterTemplate.h"
USING_NS_CC;


class MonsterSprite;
class ArcherBossTemplate : public MonsterTemplate
{
    
public:
    static const std::string CLASS_NAME;
    static MonsterTemplate* create(){ return new ArcherBossTemplate();}
    
    
    virtual void addAugmentationStatus();
    virtual void addMainStats();
    virtual void addRewards();
    
    
};

#endif /* defined(__RogueDeck__ArcherBossTemplate__) */
