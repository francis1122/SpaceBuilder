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
    cocos2d::CCLabelTTF *healthLabel;
    cocos2d::CCLabelTTF *soulLabel;
    cocos2d::CCLabelTTF *discardCountLabel;
    
    cocos2d::CCLayerColor *healthBG;
    cocos2d::CCLayerColor *healthIndicator;
    cocos2d::CCLayerColor *soulBG;
    cocos2d::CCLayerColor *soulIndicator;
    
    cocos2d::CCSprite *voidAreaSprite;
    cocos2d::CCSprite *voidAreaGlowSprite;
    
 
    cocos2d::CCSprite *healthHolder;
    cocos2d::CCSprite *soulHolder;
    
    cocos2d::CCSprite *handGlow;
    
    cocos2d::CCArray *actionArray;

    void updateInterface();
    
    cocos2d::CCSprite *deckCardSprite, *discardCardSprite;
    cocos2d::CCSprite *deckGlowCardSprite, *discardGlowCardSprite;
    
    void enableDeckInteractive();
    void disableDeckInteractive();
    void enableDiscardInteractive();
    void disableDiscardInterative();
    void enableHandInteractive();
    void disableHandInteractive();
    void enableVoidAreaInteractive();
    void disableVoidAreaInteractive();
    
    
private:
    
};
#endif /* defined(__RogueDeck__HandLayer__) */
