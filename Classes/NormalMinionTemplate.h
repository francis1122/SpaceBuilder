//
//  NormalMinionTemplate.h
//  RogueDeck
//
//  Created by Hunter Francis on 2/27/14.
//
//

#ifndef __RogueDeck__NormalMinionTemplate__
#define __RogueDeck__NormalMinionTemplate__

#include "Action.h"
#include "LLMath.h"
#include "MonsterSprite.h"
#include "MonsterTemplate.h"
USING_NS_CC;


class MonsterSprite;
class NormalMinionTemplate : public MonsterTemplate
{
    
public:
    static const std::string CLASS_NAME;
    static MonsterTemplate* create(){ return new NormalMinionTemplate();}
    
    
    virtual void addAugmentationStatus();
    virtual void addMainStats();
    virtual void addRewards();
    
    
};

#endif /* defined(__RogueDeck__NormalMinionTemplate__) */
