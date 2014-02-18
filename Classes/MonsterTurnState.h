//
//  MonsterTurnState.h
//  RogueDeck
//
//  Created by Hunter Francis on 2/7/14.
//
//

#ifndef __RogueDeck__MonsterTurnState__
#define __RogueDeck__MonsterTurnState__


#include "UIState.h"

class MonsterTurnState : public UIState
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static node()" method manually
    CREATE_FUNC(MonsterTurnState);
    
    //cocos2d::CCArray* allTouchesFromSet(cocos2d::CCSet *touches);
    virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    virtual void doubleTap(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    
    
    //button touches
    virtual void leftButtonTouch();
    virtual void rightButtonTouch();
    
    //state changes
    virtual void transitionToNormalState();
    
private:
    
};

#endif /* defined(__RogueDeck__MonsterTurnState__) */
