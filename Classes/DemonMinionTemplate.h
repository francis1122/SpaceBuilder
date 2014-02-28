//
//  DemonMinionTemplate.h
//  RogueDeck
//
//  Created by Hunter Francis on 2/23/14.
//
//

#ifndef __RogueDeck__DemonMinionTemplate__
#define __RogueDeck__DemonMinionTemplate__

#include "Action.h"
#include "LLMath.h"
#include "MonsterSprite.h"
#include "MonsterTemplate.h"
USING_NS_CC;


class MonsterSprite;
class DemonMinionTemplate : public MonsterTemplate
{
    
public:
    static const std::string CLASS_NAME;
    static MonsterTemplate* create(){ return new DemonMinionTemplate();}
    
    
    virtual void addAugmentationStatus();
    virtual void addMainStats();
    virtual void addRewards();
    
    
};

#endif /* defined(__RogueDeck__DemonMinionTemplate__) */
