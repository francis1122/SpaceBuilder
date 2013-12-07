//
//  UIState.h
//  RogueDeck
//
//  Created by Hunter Francis on 11/18/13.
//
//

#ifndef __RogueDeck__UIState__
#define __RogueDeck__UIState__

#include "cocos2d.h"

class CardSprite;
class MonsterSprite;

class UIState : public cocos2d::CCObject
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    
    // implement the "static node()" method manually
    CREATE_FUNC(UIState);
    
    #pragma mark - utility functions
    CardSprite *handCardAtPoint(cocos2d::CCTouch*touch);
    CardSprite *marketCardAtPoint(cocos2d::CCTouch*touch);
    MonsterSprite *monsterCardAtPoint(cocos2d::CCTouch*touch);
    cocos2d::CCObject* objectAtPoint(cocos2d::CCTouch* touch);
    
    //cocos2d::CCArray* allTouchesFromSet(cocos2d::CCSet *touches);
    virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    virtual void doubleTap(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    
    //button touches
    virtual void leftButtonTouch();
    virtual void rightButtonTouch();
    
    //collision checks
    bool cardInDiscardArea(CardSprite* card);
    bool cardInPlayArea(CardSprite* card);
    bool cardInSellArea(CardSprite*card);
    MonsterSprite* doesCardTouchMonster(CardSprite* card);
    MonsterSprite* doesPointTouchMonster(cocos2d::CCTouch *touch);
    
    
    //State Transitions
    virtual void transitionToNormalState();
    virtual void transitionToHandCardSelectedState(CardSprite* selectedCard);
    virtual void transitionToSelectMonsterState(CardSprite* selectedCard);
    virtual void transitionToCardTargetingState(CardSprite* selectedCard);
    virtual void transitionToCardDraggingState(CardSprite* selectedCard);
    //type 0 = hand card, 1 = monster card, 2 = market card
    virtual void transitionToZoomState(CCObject *selectedObject, int type);
    
    
private:
    
};



#endif /* defined(__RogueDeck__UIState__) */
