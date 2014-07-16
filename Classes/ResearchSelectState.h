//
//  ResearchSelectState.h
//  RogueDeck
//
//  Created by Hunter Francis on 6/28/14.
//
//

#ifndef __RogueDeck__ResearchSelectState__
#define __RogueDeck__ResearchSelectState__


#include "cocos2d.h"
#include "UIState.h"

class SolarSystemObject;

class ResearchSelectState : public UIState
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(CardSprite *_selectedCard);
    
    CardSprite *selectedCard;
    CardSprite *researchCardAtPoint(cocos2d::CCTouch *touch);
    
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
    virtual void transitionToResearchState();
    virtual void transitionToSolarSystemDetailsState(SolarSystemObject *selectedSolarSystem);
    virtual void transitionToCardTargetingState(CardSprite* selectedCard);
    //type 0 = hand card, 1 = monster card, 2 = market card
    virtual void transitionToZoomState(CCObject *selectedObject, int type);
    
private:
    
};

#endif /* defined(__RogueDeck__ResearchSelectState__) */
