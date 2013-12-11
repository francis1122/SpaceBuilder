//
//  CardSprite.h
//  RogueDeck
//
//  Created by Hunter Francis on 11/17/13.
//
//

#ifndef __RogueDeck__CardSprite__
#define __RogueDeck__CardSprite__

#include "cocos2d.h"
//#include "CardTargets.h"
class CardTargets;
class Action;
class CardSprite : public cocos2d::CCSprite
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    const char *cardImageFile;
    int turnsLeftInMarket;
    int soulCost;
    bool isInteractive;
    Action *action;
    
    cocos2d::CCLabelTTF *detailsLabel;
    cocos2d::CCLabelTTF *costLabel;
    
    cocos2d::CCSprite *glowSprite;
    
    
    // implement the "static node()" method manually
    CREATE_FUNC(CardSprite);
    
    CardTargets *cardTargets;
    
    void enableInteractive();
    void disableInteractive();
    
    void setSoulCostOfCard(int newSoulCost);
private:
    
};


#endif /* defined(__RogueDeck__CardSprite__) */
