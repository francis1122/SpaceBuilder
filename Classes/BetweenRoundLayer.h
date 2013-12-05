//
//  BetweenRoundLayer.h
//  RogueDeck
//
//  Created by Hunter Francis on 11/26/13.
//
//

#ifndef __RogueDeck__BetweenRoundLayer__
#define __RogueDeck__BetweenRoundLayer__

#include "cocos2d.h"
#include "UIState.h"
#include "CardTargets.h"


class BetweenRoundLayer : public cocos2d::CCLayer
{
public:
    
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(BetweenRoundLayer);

    void startRound(cocos2d::CCObject* pSender);
    
private:
    
};


#endif /* defined(__RogueDeck__BetweenRoundLayer__) */
