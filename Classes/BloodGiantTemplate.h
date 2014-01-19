//
//  BloodGiantTemplate.h
//  RogueDeck
//
//  Created by Hunter Francis on 1/15/14.
//
//

#ifndef __RogueDeck__BloodGiantTemplate__
#define __RogueDeck__BloodGiantTemplate__

#include "Action.h"
#include "LLMath.h"
#include "MonsterSprite.h"
#include "MonsterTemplate.h"
USING_NS_CC;


class MonsterSprite;
class BloodGiantTemplate : public MonsterTemplate
{
    
public:
    static const std::string CLASS_NAME;
    static MonsterTemplate* create(){ return new BloodGiantTemplate();}
    
    
    virtual void addAugmentationStatus();
    virtual void addMainStats();
    virtual void addRewards();
    
    
};


#endif /* defined(__RogueDeck__BloodGiantTemplate__) */
