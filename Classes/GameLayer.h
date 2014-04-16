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
class MonsterLayer;
class TopSlideLayer;
class GameLayer : public cocos2d::CCLayer
{
public:
    
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    //setup stuff
    void setupButtons();
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameLayer);
    
    //game interface state
    CC_SYNTHESIZE_RETAIN(UIState*, currentState, CurrentState);
    
    cocos2d::CCLabelTTF *visualIndicatorLabel;
    cocos2d::CCLabelTTF *monstersLeftLabel;
    cocos2d::CCLabelTTF *sellLabel;
    
    //layers
    HandLayer *handLayer;
    MarketLayer *marketLayer;
    MonsterLayer *monsterLayer;
    ZoomLayer *zoomLayer;
    TopSlideLayer *topSlideLayer;
    
    
    
    CCLabelTTF *leftButtonLabel;
    CCLabelTTF *rightButtonLabel;
    CCMenuItemSprite *rightButton;
    CCMenuItemSprite *leftButton;
    CCSprite *rightButtonGlow, *leftButtonGlow;
    CCSprite *playAreaGlow;

    
    void setButtonLabels(const char *leftLabel, const char *rightLabel);
    
    void rightButtonPressed(CCObject *pSender);
    void leftButtonPressed(CCObject *pSender);
    
    bool isOnMonsters;
    void switchButtonPressed(CCObject *pSender);
    
    
    bool isTap;
    virtual void update(float dt);
    #pragma mark - touch code
    
    cocos2d::CCArray* allTouchesFromSet(cocos2d::CCSet *touches);
    virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    
    long previousTouchTime;
    long millisecondNow();
    
    void changeState(UIState* state);
    void changeIndicatorState(const char *label);
    
    void updateInterface();
    
    void enterZoomState();
    void leaveZoomState();
    
    void enablePlayAreaInteractive();
    void disablePlayAreaInteractive();
    void enableRightButtonMustEndTurnInteractive();
    void enableRightButtonInteractive();
    void disableRightButtonInteractive();
    void enableLeftButtonInteractive();
    void disableLeftButtonInteractive();

    #pragma mark - positioning
    CCPoint monsterLayerToMarketLayer(CCPoint monsterPoint);
    
    
    //start new round callback
    void newRound();
    
    
private:
    
};

#endif /* defined(__RogueDeck__GameLayer__) */
