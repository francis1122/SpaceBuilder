//
//  GameLayer.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/17/13.
//
//

#include "GameLayer.h"
#include "GameManager.h"
#include "CardSprite.h"
#include "NormalState.h"
#include "UIState.h"
#include "HandLayer.h"
#include "MarketLayer.h"
#include "ZoomLayer.h"

USING_NS_CC;

CCScene* GameLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameLayer *layer = GameLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}



// on "init" you need to initialize your instance
bool GameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    previousTouchTime = millisecondNow();
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    visualIndicatorLabel = CCLabelTTF::create("GAME LAYER", "Arial", 24);
    
    // position the label on the center of the screen
    visualIndicatorLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - visualIndicatorLabel->getContentSize().height - 255));
    
    // add the label as a child to this layer
    this->addChild(visualIndicatorLabel, 1);
    
    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::createWithSpriteFrameName("background");
//    pSprite->initWithSpriteFrameName("background");
    
    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    GameManager *GM = GameManager::sharedGameManager();

    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    this->setTouchEnabled(true);

    //layer creation
    handLayer = HandLayer::create();
    marketLayer = MarketLayer::create();
    zoomLayer = ZoomLayer::create();
    this->addChild(handLayer);
    this->addChild(marketLayer);
    this->addChild(zoomLayer, 100);
    
    this->leaveZoomState();
    
    
    //set game layer to gamemanager
    GM->gameLayer = this;
    GM->player->drawHand();
    this->setCurrentState(new NormalState());
    currentState->init();

    GM->addMonstersPhase();
    GM->organizeMonsters();
    
    return true;
}

#pragma mark - touch code


CCArray* GameLayer::allTouchesFromSet(CCSet *touches)
{
    CCArray *arr = new CCArray();
    
    CCSetIterator it;
    
	for( it = touches->begin(); it != touches->end(); it++)
    {
        arr->addObject((CCTouch *)*it);
    }
    return arr;
}

bool GameLayer::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event)
{
    return currentState->ccTouchBegan(touch, event);
    
    
/*    // This method is passed an NSSet of touches called (of course) "touches"
    // We need to convert it to an array first
    CCArray *allTouches = this->allTouchesFromSet(touches);
    CCTouch* fingerOne = (CCTouch *)allTouches->objectAtIndex(0);
    
    // Convert each UITouch object to a CGPoint, which has x/y coordinates we can actually use
    CCPoint pointOne = fingerOne->getLocationInView();
    
    // The touch points are always in "portrait" coordinates - convert to landscape
    pointOne = CCDirector::sharedDirector()->convertToGL(pointOne);
    
    // We store the starting point of the touch so we can determine whether the touch is a swipe or tap.
 */
}

void GameLayer::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    currentState->ccTouchMoved(touch, event);
    // This method is passed an NSSet of touches called (of course) "touches"
    // We need to convert it to an array first
/*    CCArray *allTouches = this->allTouchesFromSet(touches);
    
    // Only run the following code if there is more than one touch
    if (allTouches->count() > 1)
    {
        // We're going to track the first two touches (i.e. first two fingers)
        // Create "UITouch" objects representing each touch
        CCTouch* fingerOne = (CCTouch *)allTouches->objectAtIndex(0);
        
        // Convert each UITouch object to a CGPoint, which has x/y coordinates we can actually use
        CCPoint pointOne = fingerOne->getLocationInView();
        
        // The touch points are always in "portrait" coordinates - you will need to convert them if in landscape (which we are)
        pointOne = CCDirector::sharedDirector()->convertToGL(pointOne);
    }
 */
}

void GameLayer::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    currentState->ccTouchEnded(touch, event);
    

    long currentTouchTime = millisecondNow();
    long deltaTime = currentTouchTime - previousTouchTime;
    if(deltaTime < 150){
        //is a double tap
        currentState->doubleTap(touch, event);
    }
    
    previousTouchTime = currentTouchTime;
}

void GameLayer::ccTouchCancelled(CCTouch *touch, CCEvent *event){
    currentState->ccTouchCancelled(touch, event);
    
}

long GameLayer::millisecondNow()
{
    struct cc_timeval now;
    CCTime::gettimeofdayCocos2d(&now, NULL);
    return (now.tv_sec * 1000 + now.tv_sec / 1000);
}

void GameLayer::changeState(UIState* state){
    this->setCurrentState(state);
    GameManager *GM = GameManager::sharedGameManager();
    GM->gameStateCheck();
}

void GameLayer::changeIndicatorState(TargetingType indicatorState){
    if(indicatorState == None){
        visualIndicatorLabel->setString("");
    }else if(indicatorState == PlayArea){
        visualIndicatorLabel->setString("Play Area");
    }else if (indicatorState == Monsters){
        visualIndicatorLabel->setString("Play Area or Target Monster");
    }else if(indicatorState == DiscardArea){
        visualIndicatorLabel->setString("Discard Area");
    }else if(indicatorState == RequireActions){
        visualIndicatorLabel->setString("More Actions Required");
    }
}

void GameLayer::enterZoomState(){
    zoomLayer->setVisible(true);
}

void GameLayer::leaveZoomState(){
    zoomLayer->setVisible(false);
}

void GameLayer::updateInterface(){
    handLayer->updateInterface();
}

