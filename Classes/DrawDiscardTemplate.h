//
//  DrawDiscardTemplate.h
//  RogueDeck
//
//  Created by Hunter Francis on 1/3/14.
//
//

#ifndef __RogueDeck__DrawDiscardTemplate__
#define __RogueDeck__DrawDiscardTemplate__

#include "cocos2d.h"
#include "CardTemplate.h"
USING_NS_CC;

class CardSprite;
class DrawDiscardTemplate : public CardTemplate
{
    
public:
    static const std::string CLASS_NAME;
    static CardTemplate* create(){ return new DrawDiscardTemplate();}
    
    virtual void createCardTargets();
    
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

#endif /* defined(__RogueDeck__DrawDiscardTemplate__) */
