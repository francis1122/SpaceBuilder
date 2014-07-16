//
//  ResearchLayer.h
//  RogueDeck
//
//  Created by Hunter Francis on 6/27/14.
//
//

#ifndef __RogueDeck__ResearchLayer__
#define __RogueDeck__ResearchLayer__

#include "cocos2d.h"
#include "Constants.h"

USING_NS_CC;

class SolarSystemObject;
class ResearchLayer : public CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static node()" method manually
    CREATE_FUNC(ResearchLayer);
    
    ResearchTypes currentTech;
    
    CCMenu *cardMenu;
    CCArray *cardSpriteArray;
    
    CCLabelTTF* titleLabel;
    
    void updateInterface();
    void cardPressed(CCMenuItemSprite *pSender);
    void backButtonPress(CCObject *pSender);
    
    
    void militaryButtonPress(CCObject *pSender);
    void industryButtonPress(CCObject *pSender);
    void expansionButtonPress(CCObject *pSender);
    void scienceButtonPress(CCObject *pSender);
    
private:
    
};


#endif /* defined(__RogueDeck__ResearchLayer__) */
