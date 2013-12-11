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

    virtual void addAugmentationStatus();
    virtual void addAdditionalCost();
    virtual void addMainStatus();
    virtual int calculateSoul();
    
    int soulGain;
    
    
};

#endif /* defined(__RogueDeck__SoulGainTemplate__) */
