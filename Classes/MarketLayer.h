//
//  MarketLayer.h
//  RogueDeck
//
//  Created by Hunter Francis on 11/26/13.
//
//

#ifndef __RogueDeck__MarketLayer__
#define __RogueDeck__MarketLayer__

#include "cocos2d.h"

USING_NS_CC;

class MarketLayer : public CCLayer
{
public:
    
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    
    // implement the "static node()" method manually
    CREATE_FUNC(MarketLayer);
    
    void endTurn();
    void updateInterface();
    
private:
    
};

#endif /* defined(__RogueDeck__MarketLayer__) */
