//
//  WeakMinionTemplate.h
//  RogueDeck
//
//  Created by Hunter Francis on 1/9/14.
//
//

#ifndef __RogueDeck__WeakMinionTemplate__
#define __RogueDeck__WeakMinionTemplate__

#include "Action.h"
#include "LLMath.h"
#include "MonsterSprite.h"
#include "MonsterTemplate.h"
USING_NS_CC;


class MonsterSprite;
class WeakMinionTemplate : public MonsterTemplate
{

public:
    static const std::string CLASS_NAME;
    static MonsterTemplate* create(){ return new WeakMinionTemplate();}
    
    
    virtual void addAugmentationStatus();
    virtual void addMainStats();
    virtual void addRewards();
    
    
};

#endif /* defined(__RogueDeck__WeakMinionTemplate__) */
