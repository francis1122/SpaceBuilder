//
//  ShipWorldDetailsLayer.h
//  RogueDeck
//
//  Created by Hunter Francis on 7/28/14.
//
//

#ifndef __RogueDeck__ShipWorldDetailsLayer__
#define __RogueDeck__ShipWorldDetailsLayer__

#include "cocos2d.h"

class CardSprite;
class ShipModel;
class SolarSystemObject;

USING_NS_CC;

class ShipWorldDetailsLayer : public CCLayer
{
public:
    
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    CCLabelTTF *shipNameLabel;
    CCLabelTTF *locationLabel;
    CCLabelTTF *lifeLabel;
    CCLabelTTF *attackLabel;
    
    CCMenu *abilityMenu;
    
    
    // implement the "static node()" method manually
    CREATE_FUNC(ShipWorldDetailsLayer);
    
    
    
    void updateInterface(ShipModel *shipModel);
    
    void abilityButtonPressed(CCObject *pSender);
    
    
private:
    
};

#endif /* defined(__RogueDeck__ShipWorldDetailsLayer__) */
