//
//  RandomTargetDamageTemplate.h
//  RogueDeck
//
//  Created by Hunter Francis on 12/30/13.
//
//

#ifndef __RogueDeck__RandomTargetDamageTemplate__
#define __RogueDeck__RandomTargetDamageTemplate__

#include "cocos2d.h"
#include "CardTemplate.h"
USING_NS_CC;

class CardSprite;
class RandomTargetDamageTemplate : public CardTemplate
{
    
public:
    static const std::string CLASS_NAME;
    static CardTemplate* create(){ return new RandomTargetDamageTemplate();}
    
    virtual void addNeutralAugmentationStatus();
    virtual void addRedAugmentationStatus();
    virtual void addBlueAugmentationStatus();
    virtual void addYellowAugmentationStatus();
    virtual void addPurpleAugmentationStatus();
    
    virtual void addNeutralAdditionalCost();
    virtual void addRedAdditionalCost();
    virtual void addBlueAdditionalCost();
    virtual void addYellowAdditionalCost();
    virtual void addPurpleAdditionalCost();
    
    virtual void addNeutralMainStatus();
    virtual void addRedMainStatus();
    virtual void addBlueMainStatus();
    virtual void addYellowMainStatus();
    virtual void addPurpleMainStatus();
    
};

#endif /* defined(__RogueDeck__RandomTargetDamageTemplate__) */
