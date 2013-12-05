//
//  ZoomState.h
//  RogueDeck
//
//  Created by Hunter Francis on 11/27/13.
//
//

#ifndef __RogueDeck__ZoomState__
#define __RogueDeck__ZoomState__

#include "cocos2d.h"
#include "UIState.h"
#include "CardSprite.h"

class ZoomState : public UIState
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual bool initCardSprite(CardSprite *_selectedCard);
    virtual bool initMonsterSprite(MonsterSprite *_selectedMonsterCard);
    virtual bool initMarketCard(CardSprite *_selectedCard);
    
    CardSprite *selectedCard;
    MonsterSprite *selectedMonsterCard;
    
    
    // implement the "static node()" method manually
    // CREATE_FUNC(HandCardSelectedState);
    
    //cocos2d::CCArray* allTouchesFromSet(cocos2d::CCSet *touches);
    virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    
    //state changes
    virtual void transitionToNormalState();
    virtual void transitionToHandCardSelectedState(CardSprite* selectedCard);
    virtual void transitionToSelectMonsterState(CardSprite* selectedCard);
    virtual void transitionToCardTargetingState(CardSprite* selectedCard);

    
private:
    
};

#endif /* defined(__RogueDeck__ZoomState__) */
