//
//  CardInfoLayer.h
//  RogueDeck
//
//  Created by Hunter Francis on 7/22/14.
//
//

#ifndef __RogueDeck__CardInfoLayer__
#define __RogueDeck__CardInfoLayer__

#include "cocos2d.h"

USING_NS_CC;

class CardSprite;
class CardInfoLayer : public CCLayer
{
public:
    
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    
    // implement the "static node()" method manually
    CREATE_FUNC(CardInfoLayer);
    
    
    void updateInterface();
    
    
private:
    
};

#endif /* defined(__RogueDeck__CardInfoLayer__) */
