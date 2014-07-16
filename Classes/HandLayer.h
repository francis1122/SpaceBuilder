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

class CardSprite;
class HandLayer : public cocos2d::CCLayer
{
public:
    
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    
    
    // implement the "static node()" method manually
    CREATE_FUNC(HandLayer);
    
    cocos2d::CCLabelTTF *libraryCountLabel;
    cocos2d::CCLabelTTF *moneyLabel;
    cocos2d::CCLabelTTF *commandPointsLabel;
    cocos2d::CCLabelTTF *discardCountLabel;
    
    cocos2d::CCLayerColor *healthBG;
    cocos2d::CCLayerColor *soulBG;
    
    
 
    cocos2d::CCSprite *moneyHolder;
    cocos2d::CCSprite *commandPointHolder;
    
    
    cocos2d::CCSprite *handGlow;
    

    void updateInterface();
    
    cocos2d::CCSprite *deckCardSprite;
    cocos2d::CCSprite *deckGlowCardSprite;
    
    void enableDeckInteractive();
    void disableDeckInteractive();
    void enableHandInteractive();
    void disableHandInteractive();
    
    
private:
    
};
#endif /* defined(__RogueDeck__HandLayer__) */
