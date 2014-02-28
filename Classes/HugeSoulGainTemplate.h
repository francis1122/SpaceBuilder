//
//  HugeSoulGainTemplate.h
//  RogueDeck
//
//  Created by Hunter Francis on 2/25/14.
//
//

#ifndef __RogueDeck__HugeSoulGainTemplate__
#define __RogueDeck__HugeSoulGainTemplate__


#include "cocos2d.h"
#include "CardTemplate.h"
USING_NS_CC;

class CardSprite;
class HugeSoulGainTemplate : public CardTemplate
{
    
public:
    static const std::string CLASS_NAME;
    static CardTemplate* create(){ return new HugeSoulGainTemplate();}
    
    virtual void createCardTargets(CardSprite *card);
    
    virtual void addNeutralAugmentationStatus();
    virtual void addRedAugmentationStatus();
    virtual void addBlueAugmentationStatus();
    virtual void addYellowAugmentationStatus();
    virtual void addGreenAugmentationStatus();
    
    virtual void addNeutralAdditionalCost();
    virtual void addRedAdditionalCost();
    virtual void addBlueAdditionalCost();
    virtual void addYellowAdditionalCost();
    virtual void addGreenAdditionalCost();
    
    virtual void addNeutralMainStatus();
    virtual void addRedMainStatus();
    virtual void addBlueMainStatus();
    virtual void addYellowMainStatus();
    virtual void addGreenMainStatus();
    
};


#endif /* defined(__RogueDeck__HugeSoulGainTemplate__) */
