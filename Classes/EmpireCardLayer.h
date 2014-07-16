//
//  EmpireCardLayer.h
//  RogueDeck
//
//  Created by Hunter Francis on 6/15/14.
//
//

#ifndef __RogueDeck__EmpireCardLayer__
#define __RogueDeck__EmpireCardLayer__

#include "cocos2d.h"

USING_NS_CC;

class SolarSystemObject;
class EmpireCardLayer : public CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static node()" method manually
    CREATE_FUNC(EmpireCardLayer);
    
    
    CCArray *cardSpriteArray;
    
    void updateInterface(SolarSystemObject *solarSystem);
    CCSprite *getSpriteFromSprite(CCSprite *citySprite, float citySpriteWidth, float citySpriteHeight);
    void backButtonPress(CCObject *pSender);
    
private:
    
};


#endif /* defined(__RogueDeck__EmpireCardLayer__) */
