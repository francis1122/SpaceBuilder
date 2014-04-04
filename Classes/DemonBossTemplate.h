//
//  DemonBossTemplate.h
//  RogueDeck
//
//  Created by Hunter Francis on 2/27/14.
//
//

#ifndef __RogueDeck__DemonBossTemplate__
#define __RogueDeck__DemonBossTemplate__

#include "Action.h"
#include "LLMath.h"
#include "MonsterSprite.h"
#include "MonsterTemplate.h"
USING_NS_CC;


class MonsterSprite;
class DemonBossTemplate : public MonsterTemplate
{
    
public:
    static const std::string CLASS_NAME;
    static MonsterTemplate* create(){ return new DemonBossTemplate();}
    
    
    virtual void addAugmentationStatus();
    virtual void addMainStats();
    virtual void addRewards();
    
    
};

#endif /* defined(__RogueDeck__DemonBossTemplate__) */
