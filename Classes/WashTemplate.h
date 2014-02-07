//
//  WashTemplate.h
//  RogueDeck
//
//  Created by Hunter Francis on 1/17/14.
//
//

#ifndef __RogueDeck__WashTemplate__
#define __RogueDeck__WashTemplate__

#include "cocos2d.h"
#include "CardTemplate.h"
USING_NS_CC;

class CardSprite;
class WashTemplate : public CardTemplate
{
    
public:
    static const std::string CLASS_NAME;
    static CardTemplate* create(){ return new WashTemplate();}
    
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
    
    virtual int calculateSoul();
    
};

#endif /* defined(__RogueDeck__WashTemplate__) */
