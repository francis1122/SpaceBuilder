//
//  SoulGainTemplate.h
//  RogueDeck
//
//  Created by Hunter Francis on 12/10/13.
//
//

#ifndef __RogueDeck__SoulGainTemplate__
#define __RogueDeck__SoulGainTemplate__


#include "cocos2d.h"
#include "CardTemplate.h"
USING_NS_CC;

class CardSprite;
class SoulGainTemplate : public CardTemplate
{
    
public:
    static const std::string CLASS_NAME;
    static CardTemplate* create(){ return new SoulGainTemplate();}
    
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
    
    int soulGain;
};

#endif /* defined(__RogueDeck__SoulGainTemplate__) */
