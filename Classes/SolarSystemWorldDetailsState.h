//
//  SolarSystemWorldDetailsState.h
//  RogueDeck
//
//  Created by Hunter Francis on 7/28/14.
//
//

#ifndef __RogueDeck__SolarSystemWorldDetailsState__
#define __RogueDeck__SolarSystemWorldDetailsState__

#include "cocos2d.h"
#include "UIState.h"

class SolarSystemObject;

class SolarSystemWorldDetailsState : public UIState
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(SolarSystemObject *_selectedSolarSystemObject);
    
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
    virtual void transitionToSolarSystemWorldDetailsState(SolarSystemObject *selectedSolarSystem);
    virtual void transitionToShipWorldDetailsState(ShipModel *selectedShipModel);

    
private:
    
};

#endif /* defined(__RogueDeck__SolarSystemWorldDetailsState__) */
