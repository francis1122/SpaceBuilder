//
//  CardTemplate.h
//  RogueDeck
//
//  Created by Hunter Francis on 12/6/13.
//
//

#ifndef __RogueDeck__CardTemplate__
#define __RogueDeck__CardTemplate__

#include "cocos2d.h"
#include "Action.h"
#include "LLMath.h"

USING_NS_CC;


class CardSprite;
class CardTemplate
{
    
public:
    float powerLevel;
    float cardPower;
    float cardCostOffset;
    ActionType cardColor;
    CardSprite *createdCard;
    
    virtual bool init(float powerLevel, ActionType color);
    static CardTemplate* create(){ return new CardTemplate();}

    virtual CardSprite* createCard();
    
    virtual void createCardTargets();
    
    virtual void addAugmentationStatus();
    virtual void addNeutralAugmentationStatus();
    virtual void addRedAugmentationStatus();
    virtual void addBlueAugmentationStatus();
    virtual void addYellowAugmentationStatus();
    virtual void addPurpleAugmentationStatus();
    
    virtual void addAdditionalCost();
    virtual void addNeutralAdditionalCost();
    virtual void addRedAdditionalCost();
    virtual void addBlueAdditionalCost();
    virtual void addYellowAdditionalCost();
    virtual void addPurpleAdditionalCost();
    
    virtual void addMainStatus();
    virtual void addNeutralMainStatus();
    virtual void addRedMainStatus();
    virtual void addBlueMainStatus();
    virtual void addYellowMainStatus();
    virtual void addPurpleMainStatus();
    
    virtual void addDescriptionText();
    virtual int calculateSoul();
    
    
    //card description varaibles
    CCArray *actionsGained;
    CCString *costDescription;
    CCString *mainDescription;
    CCString *augmentationDescription;
    
    //functions
    
};



#endif /* defined(__RogueDeck__CardTemplate__) */
