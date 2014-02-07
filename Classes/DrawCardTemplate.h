//
//  DrawCardTemplate.h
//  RogueDeck
//
//  Created by Hunter Francis on 12/10/13.
//
//

#ifndef __RogueDeck__DrawCardTemplate__
#define __RogueDeck__DrawCardTemplate__

#include "cocos2d.h"
#include "CardTemplate.h"
USING_NS_CC;

class CardSprite;
class DrawCardTemplate : public CardTemplate
{
    
public:
    static const std::string CLASS_NAME; 
    static CardTemplate* create(){ return new DrawCardTemplate();}
    
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
    
    
    int drawCardAmount;
    
};

#endif /* defined(__RogueDeck__DrawCardTemplate__) */
