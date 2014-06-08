//
//  SolarSystemDetailsState.h
//  RogueDeck
//
//  Created by Hunter Francis on 6/7/14.
//
//

#ifndef __RogueDeck__SolarSystemDetailsState__
#define __RogueDeck__SolarSystemDetailsState__

#include "cocos2d.h"
#include "UIState.h"

class SolarSystemObject;
class SolarSystemDetailsState : public UIState
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(SolarSystemObject *_selectedSolarSystemObject);
    // implement the "static node()" method manually
    
    SolarSystemObject *selectedSolarSystemObject;
    
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
    virtual void transitionToSolarSystemDetailsState(SolarSystemObject *selectedSolarSystem);
    virtual void transitionToCardTargetingState(CardSprite* selectedCard);
    //type 0 = hand card, 1 = monster card, 2 = market card
    void transitionToCardDraggingState(CardSprite* selectedCard);
    
private:
    
};

#endif /* defined(__RogueDeck__SolarSystemDetailsState__) */
