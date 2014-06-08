//
//  SolarSystemDetailsLayer.h
//  RogueDeck
//
//  Created by Hunter Francis on 6/7/14.
//
//

#ifndef __RogueDeck__SolarSystemDetailsLayer__
#define __RogueDeck__SolarSystemDetailsLayer__

#include "cocos2d.h"

USING_NS_CC;

class SolarSystemObject;
class SolarSystemDetailsLayer : public CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static node()" method manually
    CREATE_FUNC(SolarSystemDetailsLayer);
    
    CCLabelTTF *population;
    CCLabelTTF *income;
    CCLabelTTF *cardLimit;
    
    void updateInterface(SolarSystemObject *solarSystem);
    
private:
    
};


#endif /* defined(__RogueDeck__SolarSystemDetailsLayer__) */
