//
//  MonsterTemplate.h
//  RogueDeck
//
//  Created by Hunter Francis on 1/9/14.
//
//

#ifndef __RogueDeck__MonsterTemplate__
#define __RogueDeck__MonsterTemplate__

#include "cocos2d.h"
#include "Action.h"
#include "LLMath.h"
#include "MonsterSprite.h"

USING_NS_CC;


class MonsterSprite;
class MonsterTemplate
{
    
public:
    float powerLevel; //static powerLevel of monster
    float monsterPower; //changes while making the monster to balance elements that go into monster
    MonsterSprite *createdMonster;
    
    virtual bool init(float powerLevel);
    static MonsterTemplate* create(){ return new MonsterTemplate();}    
    
    MonsterSprite* createMonster();
    
    virtual void addAugmentationStatus();
    virtual void addMainStats();
    virtual void addRewards();
    
    CCString *augmentationDescription;
    CCString *rewardDescription;

    void addDescriptionText();
    
};

#endif /* defined(__RogueDeck__MonsterTemplate__) */
