//
//  SolarSystemWorldDetailsLayer.h
//  RogueDeck
//
//  Created by Hunter Francis on 7/28/14.
//
//

#ifndef __RogueDeck__SolarSystemWorldDetailsLayer__
#define __RogueDeck__SolarSystemWorldDetailsLayer__


#include "cocos2d.h"

class CardSprite;
class SolarSystemObject;

USING_NS_CC;

class SolarSystemWorldDetailsLayer : public CCLayer
{
public:
    
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    CCLabelTTF *solarSystemNameLabel;
    CCLabelTTF *resourcesLabel;
    
    // implement the "static node()" method manually
    CREATE_FUNC(SolarSystemWorldDetailsLayer);
    
    
    
    void updateInterface(SolarSystemObject *solarSystem);
    

    
    
private:
    
};

#endif /* defined(__RogueDeck__SolarSystemWorldDetailsLayer__) */
