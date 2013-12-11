//
//  ActionGainTemplate.h
//  RogueDeck
//
//  Created by Hunter Francis on 12/10/13.
//
//

#ifndef __RogueDeck__ActionGainTemplate__
#define __RogueDeck__ActionGainTemplate__


#include "cocos2d.h"
#include "CardTemplate.h"
USING_NS_CC;

class CardSprite;
class ActionGainTemplate : public CardTemplate
{
    
public:
    virtual void addAugmentationStatus();
    virtual void addAdditionalCost();
    virtual void addMainStatus();
    virtual int calculateSoul();
    
    int actionGain;

};

#endif /* defined(__RogueDeck__ActionGainTemplate__) */
