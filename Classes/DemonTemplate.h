//
//  DemonTemplate.h
//  RogueDeck
//
//  Created by Hunter Francis on 2/23/14.
//
//

#ifndef __RogueDeck__DemonTemplate__
#define __RogueDeck__DemonTemplate__

#include "Action.h"
#include "LLMath.h"
#include "MonsterSprite.h"
#include "MonsterTemplate.h"
USING_NS_CC;


class MonsterSprite;
class DemonTemplate : public MonsterTemplate
{
    
public:
    static const std::string CLASS_NAME;
    static MonsterTemplate* create(){ return new DemonTemplate();}
    
    
    virtual void addAugmentationStatus();
    virtual void addMainStats();
    virtual void addRewards();
    
    
};

#endif /* defined(__RogueDeck__DemonTemplate__) */
