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


USING_NS_CC;

class CardSprite;
class CardTemplate
{
    
public:
    virtual bool init(float powerLevel);
    
    float powerLevel;
    float cardPower;
    CardSprite *createdCard;
    virtual CardSprite* createCard();
    virtual void addAugmentationStatus();
    virtual void addAdditionalCost();
    virtual void addMainStatus();
    virtual void addDescriptionText();
    virtual int calculateSoul();
    
    CCString *costDescription;
    CCString *mainDescription;
    CCString *augmentationDescription;
    
    
};

#endif /* defined(__RogueDeck__CardTemplate__) */
