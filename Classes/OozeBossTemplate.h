//
//  OozeBossTemplate.h
//  RogueDeck
//
//  Created by Hunter Francis on 2/27/14.
//
//

#ifndef __RogueDeck__OozeBossTemplate__
#define __RogueDeck__OozeBossTemplate__

#include "Action.h"
#include "LLMath.h"
#include "MonsterSprite.h"
#include "MonsterTemplate.h"
USING_NS_CC;


class MonsterSprite;
class OozeBossTemplate : public MonsterTemplate
{
    
public:
    static const std::string CLASS_NAME;
    static MonsterTemplate* create(){ return new OozeBossTemplate();}
    
    
    virtual void addAugmentationStatus();
    virtual void addMainStats();
    virtual void addRewards();
    
    
};

#endif /* defined(__RogueDeck__OozeBossTemplate__) */
