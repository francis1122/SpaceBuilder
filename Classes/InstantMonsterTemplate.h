//
//  InstantMonsterTemplate.h
//  RogueDeck
//
//  Created by Hunter Francis on 1/18/14.
//
//

#ifndef __RogueDeck__InstantMonsterTemplate__
#define __RogueDeck__InstantMonsterTemplate__

#include "cocos2d.h"
#include "CardTemplate.h"
USING_NS_CC;

//kills a monster with less than a certain amount of health

class CardSprite;
class InstantMonsterTemplate : public CardTemplate
{
    
public:
    static const std::string CLASS_NAME;
    static CardTemplate* create(){ return new InstantMonsterTemplate();}
    
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

#endif /* defined(__RogueDeck__InstantMonsterTemplate__) */
