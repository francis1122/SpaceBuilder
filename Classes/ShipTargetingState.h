//
//  ShipTargetingState.h
//  RogueDeck
//
//  Created by Hunter Francis on 7/29/14.
//
//

#ifndef __RogueDeck__ShipTargetingState__
#define __RogueDeck__ShipTargetingState__

#include "cocos2d.h"
#include "UIState.h"
#include "CardSprite.h"

class Ability;

class ShipTargetingState : public UIState
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(Ability *_ability);
    
    Ability *selectedAbility;
    
    //cocos2d::CCArray* allTouchesFromSet(cocos2d::CCSet *touches);
    virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    
    //button touches
    virtual void leftButtonTouch();
    virtual void rightButtonTouch();
    
    //state changes
    virtual void transitionToNormalState();
    virtual void transitionToHandCardSelectedState(CardSprite* selectedCard);
    virtual void transitionToShipWorldDetailsState(ShipModel *selectedShipModel);
    
    
private:
    
};

#endif /* defined(__RogueDeck__ShipTargetingState__) */
