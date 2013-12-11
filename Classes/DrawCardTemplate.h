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
    virtual void addAugmentationStatus();
    virtual void addAdditionalCost();
    virtual void addMainStatus();
    virtual int calculateSoul();
    
    int drawCardAmount;
    
};

#endif /* defined(__RogueDeck__DrawCardTemplate__) */
