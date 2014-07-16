//
//  ResearchTypeTargetLayer.h
//  RogueDeck
//
//  Created by Hunter Francis on 7/15/14.
//
//

#ifndef __RogueDeck__ResearchTypeTargetLayer__
#define __RogueDeck__ResearchTypeTargetLayer__

#include "cocos2d.h"

USING_NS_CC;

class CardSprite;
class ResearchTypeTargetLayer : public cocos2d::CCLayer
{
public:
    
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    
    // implement the "static node()" method manually
    CREATE_FUNC(ResearchTypeTargetLayer);
    
    
    CCSprite *militaryIcon;
    CCSprite *industryIcon;
    CCSprite *expansionIcon;
    CCSprite *scienceIcon;
    
    
    void updateInterface();
    
    
private:
    
};

#endif /* defined(__RogueDeck__ResearchTypeTargetLayer__) */
