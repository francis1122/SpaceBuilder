//
//  OnDefendDirectDamageTemplate.h
//  RogueDeck
//
//  Created by Hunter Francis on 1/9/14.
//
//

#ifndef __RogueDeck__OnDefendDirectDamageTemplate__
#define __RogueDeck__OnDefendDirectDamageTemplate__

#include "cocos2d.h"
#include "CardTemplate.h"
USING_NS_CC;

class CardSprite;
class OnDefendDirectDamageTemplate : public CardTemplate
{
    
public:
    static const std::string CLASS_NAME;
    static CardTemplate* create(){ return new OnDefendDirectDamageTemplate();}
    
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

#endif /* defined(__RogueDeck__OnDefendDirectDamageTemplate__) */
