//
//  ResourceCardInfoLayer.h
//  RogueDeck
//
//  Created by Hunter Francis on 7/22/14.
//
//

#ifndef __RogueDeck__ResourceCardInfoLayer__
#define __RogueDeck__ResourceCardInfoLayer__

#include "cocos2d.h"



USING_NS_CC;
class ResourceCardSprite;
class CardSprite;
class ResourceCardInfoLayer : public CCLayer
{
public:
    
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    
    // implement the "static node()" method manually
    CREATE_FUNC(ResourceCardInfoLayer);
    
    CCSprite *moneySprite;
    CCSprite *productionSprite;
    CCSprite *foodSprite;
    
    CCLabelTTF *description;
    
    void setupInterface(ResourceCardSprite *resourceCard);
    void updateInterface();
    
    
private:
    
};

#endif /* defined(__RogueDeck__ResourceCardInfoLayer__) */
