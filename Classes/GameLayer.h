//
//  GameLayer.h
//  RogueDeck
//
//  Created by Hunter Francis on 11/17/13.
//
//

#ifndef __RogueDeck__GameLayer__
#define __RogueDeck__GameLayer__

#include "cocos2d.h"
#include "UIState.h"
#include "CardTargets.h"

class HandLayer;
class MarketLayer;
class ZoomLayer;
class GameLayer : public cocos2d::CCLayer
{
public:
    
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameLayer);
    
    //game interface state
    CC_SYNTHESIZE_RETAIN(UIState*, currentState, CurrentState);
    
    cocos2d::CCLabelTTF *visualIndicatorLabel;
    
    //layers
    HandLayer *handLayer;
    MarketLayer *marketLayer;
    ZoomLayer *zoomLayer;
    
    cocos2d::CCArray* allTouchesFromSet(cocos2d::CCSet *touches);
    virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    
    long previousTouchTime;
    long millisecondNow();
    
    void changeState(UIState* state);
    void changeIndicatorState(TargetingType indicatorState);
    
    void updateInterface();
    
    void enterZoomState();
    void leaveZoomState();
    
    
private:
    
};

#endif /* defined(__RogueDeck__GameLayer__) */
