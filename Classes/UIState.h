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

USING_NS_CC;

class CardSprite;
class MonsterSprite;
class CardTargets;
class SolarSystemObject;
class UIState : public cocos2d::CCObject
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    
    // implement the "static node()" method manually
    CREATE_FUNC(UIState);
    
    #pragma mark - utility functions
    CardSprite *handCardAtPoint(cocos2d::CCTouch*touch);
    SolarSystemObject *solarSystemObjectAtPoint(cocos2d::CCTouch *touch);
    CardSprite *marketCardAtPoint(cocos2d::CCTouch*touch);
    MonsterSprite *monsterCardAtPoint(cocos2d::CCTouch*touch);
    cocos2d::CCObject* objectAtPoint(cocos2d::CCTouch* touch);
    
    //visualize what can be touched
    virtual void clearInteractiveState();
    //used for when card is being played
    virtual void highlightInteractiveObjects(CardSprite *card);
    
    virtual void defaultInteractiveState();
    
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
    
    //camera
    CCPoint previousTouchPoint;
    CCPoint deltaTouch;
    CCPoint cameraVelocity;
    bool moveCameraUp;
    bool moveCameraDown;
    bool moveCameraLeft;
    bool moveCameraRight;
    
    virtual void sideCameraMovement(cocos2d::CCTouch* touch);
    virtual void cameraOnTouchBegan(cocos2d::CCTouch* touch);
    virtual void cameraOnTouchMoved(cocos2d::CCTouch* touch);
    virtual void cameraOnTouchEnded(cocos2d::CCTouch* touch);
    virtual void cameraOnTouchCancelled(cocos2d::CCTouch* touch);
    virtual void updateCamera(float dt);
    virtual void checkCameraBounds();
    virtual void cleanCameraVariables();
    
    
    
    //State Transitions
    virtual void transitionToNormalState();
    virtual void transitionToHandCardSelectedState(CardSprite* selectedCard);
    virtual void transitionToSolarSystemDetailsState(SolarSystemObject *selectedSolarSystem);
    virtual void transitionToSelectMonsterState(CardSprite* selectedCard);
    virtual void transitionToCardTargetingState(CardSprite* selectedCard);
    virtual void transitionToCardDraggingState(CardSprite* selectedCard);
    virtual void transitionToMonsterTurnState();
    //type 0 = hand card, 1 = monster card, 2 = market card
    virtual void transitionToZoomState(CCObject *selectedObject, int type);
    
    
private:
    
};



#endif /* defined(__RogueDeck__UIState__) */
