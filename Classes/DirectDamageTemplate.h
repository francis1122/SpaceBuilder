//
//  DirectDamageTemplate.h
//  RogueDeck
//
//  Created by Hunter Francis on 12/6/13.
//
//

#ifndef __RogueDeck__DirectDamageTemplate__
#define __RogueDeck__DirectDamageTemplate__

#include "cocos2d.h"
#include "CardTemplate.h"
USING_NS_CC;

class CardSprite;
class DirectDamageTemplate : public CardTemplate
{
    
public:
    
    virtual void addAugmentationStatus();
    virtual void addAdditionalCost();
    virtual void addMainStatus();
    virtual int calculateSoul();
    
    
};

#endif /* defined(__RogueDeck__DirectDamageTemplate__) */
