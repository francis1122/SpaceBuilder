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

#define TOP_BAR_HEIGHT 200

class LevelTemplate;
class BetweenRoundLayer : public cocos2d::CCLayer
{
public:
    
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    cocos2d::CCArray* allTouchesFromSet(cocos2d::CCSet *touches);
    virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    
    // implement the "static node()" method manually
    CREATE_FUNC(BetweenRoundLayer);

    void levelSelected(CCObject* pSender);
    void startRound(cocos2d::CCObject* pSender);
    
    CCLayer *topNode;
    CCLayer *bottomNode;
    CCSprite *selectedSprite;
    CCMenuItemSprite *startButton;
    CCLabelTTF* levelTitle;
    CCLabelTTF* levelDescription;
    
    LevelTemplate *selectedLevel;
    
    //scrolling view
    CCPoint previousTouch;
    
private:
    
};


#endif /* defined(__RogueDeck__BetweenRoundLayer__) */
