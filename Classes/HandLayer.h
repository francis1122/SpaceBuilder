//
//  HandLayer.h
//  RogueDeck
//
//  Created by Hunter Francis on 11/19/13.
//
//

#ifndef __RogueDeck__HandLayer__
#define __RogueDeck__HandLayer__

#include "cocos2d.h"

class HandLayer : public cocos2d::CCLayer
{
public:
    
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    
    // implement the "static node()" method manually
    CREATE_FUNC(HandLayer);
    
    cocos2d::CCLabelTTF *libraryCountLabel;
    cocos2d::CCLabelTTF *healthLabel;
    cocos2d::CCLabelTTF *soulLabel;
    cocos2d::CCLabelTTF *discardCountLabel;
    cocos2d::CCLabelTTF *actionLabel;

    void endTurn();
    void updateInterface();
    
private:
    
};
#endif /* defined(__RogueDeck__HandLayer__) */
