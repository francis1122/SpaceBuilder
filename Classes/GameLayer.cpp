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
#include "ZoomLayer.h"
#include "Player.h"
#include "MonsterLayer.h"
#include "AnimationManager.h"
#include "Constants.h"
#include "SolarSystemDetailsLayer.h"
#include "EmpireCardLayer.h"
#include "ResearchLayer.h"
#include "ResearchTypeTargetLayer.h"
#include "CardInfoLayer.h"
#include "ResourceCardInfoLayer.h"
#include "SolarSystemWorldDetailsLayer.h"
#include "ShipWorldDetailsLayer.h"

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

void GameLayer::setupButtons(){
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    rightButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("CardGainSoul"),
                                           CCSprite::createWithSpriteFrameName("Button_Pressed"),
                                           this,
                                           menu_selector(GameLayer::rightButtonPressed));
    leftButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("CardCostBox"),
                                          CCSprite::createWithSpriteFrameName("Button_Pressed"),
                                          this,
                                          menu_selector(GameLayer::leftButtonPressed));
    endTurnButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("Button"),
                                          CCSprite::createWithSpriteFrameName("Button_Pressed"),
                                          this,
                                          menu_selector(GameLayer::endTurnButtonPressed));
    
    empireCardsButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("Button"),
                                             CCSprite::createWithSpriteFrameName("Button_Pressed"),
                                             this,
                                             menu_selector(GameLayer::empireCardsButtonPressed));
    researchButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("Button"),
                                                 CCSprite::createWithSpriteFrameName("Button_Pressed"),
                                                 this,
                                                 menu_selector(GameLayer::researchButtonPressed));
    
    endTurnButton->setScale(.7);
    rightButton->setScale(.7);
    leftButton->setScale(.7);
    empireCardsButton->setScale(.7);
    researchButton->setScale(.7);
    
	rightButton->setPosition(ccp(visibleSize.width - 60,
                                 120));
	leftButton->setPosition(ccp( 50,
                                120));
	endTurnButton->setPosition(ccp( visibleSize.width - 80,
                                visibleSize.height - 60));
    empireCardsButton->setPosition(ccp( visibleSize.width - 380,
                                   visibleSize.height - 60));
    researchButton->setPosition(ccp( visibleSize.width - 580,
                                    visibleSize.height - 60));
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create( researchButton, empireCardsButton, endTurnButton, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 102);
    
    CCMenu *handOptions = CCMenu::create(leftButton, rightButton, NULL);
    handOptions->setPosition(CCPointZero);
    this->addChild(handOptions, 1000002);
    
    
    //labels
    leftButtonLabel = CCLabelTTF::create("Cards", Main_Font, 32);
    rightButtonLabel = CCLabelTTF::create("End Turn", Main_Font, 32);
    //    rightButtonLabel->enableStroke(ccBLACK, 2);
    
    leftButtonLabel->setPosition(ccp(visibleSize.width - 380, visibleSize.height - 60));
    rightButtonLabel->setPosition(ccp(visibleSize.width - 80, visibleSize.height - 60));
    
    this->addChild(leftButtonLabel, 103);
    this->addChild(rightButtonLabel, 103);
    
    this->scheduleUpdate();
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
    
    
    AM->resetAnimationManager();
    this->addChild(AM);
    
    previousTouchTime = millisecondNow();
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    isOnMonsters = true;
    setupButtons();
    
    
    //play area glow
    
//    playAreaGlow = CCSprite::createWithSpriteFrameName("PlayGlow");
//    playAreaGlow->setPosition(ccp(visibleSize.width/2, 255));
//    playAreaGlow->setVisible(false);
//    this->addChild(playAreaGlow, 100);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    visualIndicatorLabel = CCLabelTTF::create("GAME LAYER", Main_Font, 24);


    
    // position the label on the center of the screen
    visualIndicatorLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                                          origin.y + visibleSize.height - visualIndicatorLabel->getContentSize().height - 255));
    visualIndicatorLabel->setColor(ccWHITE);

    // add the label as a child to this layer
    this->addChild(visualIndicatorLabel, 102);

    

    
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    this->setTouchEnabled(true);
    
    //layer creation
    handLayer = HandLayer::create();
    zoomLayer = ZoomLayer::create();
    monsterLayer = MonsterLayer::create();
    solarSystemDetailsLayer = SolarSystemDetailsLayer::create();
    empireCardLayer = EmpireCardLayer::create();
    researchLayer = ResearchLayer::create();
    researchTypeTargetLayer = ResearchTypeTargetLayer::create();
    cardInfoLayer = CardInfoLayer::create();
    resourceCardInfoLayer = ResourceCardInfoLayer::create();
    solarSystemWorldDetailsLayer = SolarSystemWorldDetailsLayer::create();
    shipWorldDetailsLayer = ShipWorldDetailsLayer::create();
    
//    topSlideLayer = TopSlideLayer::create();
//    this->addChild(topSlideLayer);
    this->addChild(handLayer, 1000);
    this->addChild(solarSystemDetailsLayer, 150);
    this->addChild(monsterLayer, 100);
    this->addChild(zoomLayer, 1000000);
    this->addChild(empireCardLayer, 150);
    this->addChild(researchLayer, 150);
    this->addChild(researchTypeTargetLayer, 100000);
    this->addChild(cardInfoLayer, 100000);
    this->addChild(resourceCardInfoLayer, 100000);
    this->addChild(solarSystemWorldDetailsLayer, 1000);
    this->addChild(shipWorldDetailsLayer, 1000);
    
    empireCardLayer->setVisible(false);
    solarSystemDetailsLayer->setVisible(false);
    researchLayer->setVisible(false);
    researchTypeTargetLayer->setVisible(false);
    cardInfoLayer->setVisible(false);
    resourceCardInfoLayer->setVisible(false);
    solarSystemWorldDetailsLayer->setVisible(false);
    shipWorldDetailsLayer->setVisible(false);
    
    this->leaveZoomState();
    
    //set game layer to gamemanager
    GM->gameLayer = this;
//    GM->player->drawHand();
//    GM->player->organizeHand();
    this->setCurrentState(new NormalState());
    currentState->init();
    
  //  GM->addMonstersPhase();
//   / GM->organizeMonsters();
    
    
    //market/monster switch button
    /*CCMenuItemSprite *switchButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("Button"),
                                                              CCSprite::createWithSpriteFrameName("Button_Pressed"),
                                                              this,
                                                              menu_selector(GameLayer::switchButtonPressed));
    
	switchButton->setPosition(ccp(visibleSize.width,
                                  470));
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(switchButton, NULL);
    pMenu->setPosition(CCPointZero);
    topSlideLayer->addChild(pMenu, 100);
    
    */
    
    
    
    this->updateInterface();
    
    
    
    return true;
}

void GameLayer::update(float dt)
{
    CCNode::update(dt);
//    updateCamera
    currentState->updateCamera(dt);
  //  setCurrentState
}


void GameLayer::setButtonLabels(const char *leftLabel, const char *rightLabel){
    leftButtonLabel->setString(leftLabel);
    rightButtonLabel->setString(rightLabel);
}


void GameLayer::rightButtonPressed(CCObject *pSender){
    if(GM->isInteractive){
        currentState->rightButtonTouch();
    }
}

void GameLayer::leftButtonPressed(CCObject *pSender){
    if(GM->isInteractive){
        currentState->leftButtonTouch();
    }
}

void GameLayer::endTurnButtonPressed(CCObject *pSender){
    GM->endTurn();
}


void GameLayer::empireCardsButtonPressed(CCObject *pSender){
    empireCardLayer->setVisible(true);
}

void GameLayer::researchButtonPressed(CCObject *pSender){
    currentState->transitionToResearchState();
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
    GameManager::sharedGameManager();
    if(GM->isInteractive){
        isTap = true;
        return currentState->ccTouchBegan(touch, event);
    }else{
        return false;
    }
    
    
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
    if(GM->isInteractive){
        isTap = false;
        currentState->ccTouchMoved(touch, event);
    }
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
    if(GM->isInteractive){
//        currentState->ccTouchEnded(touch, event);
        
        if(isTap){
            long currentTouchTime = millisecondNow();
            long deltaTime = currentTouchTime - previousTouchTime;
            if(deltaTime < 150){
                //is a double tap
                currentState->doubleTap(touch, event);
            }else{
                currentState->ccTouchEnded(touch, event);
            }
            previousTouchTime = currentTouchTime;
        }else{
            currentState->ccTouchEnded(touch, event);
        }
    }
}

void GameLayer::ccTouchCancelled(CCTouch *touch, CCEvent *event){
    if(GM->isInteractive){
        currentState->ccTouchCancelled(touch, event);
    }
    
}

long GameLayer::millisecondNow()
{
    struct cc_timeval now;
    CCTime::gettimeofdayCocos2d(&now, NULL);
    return (now.tv_sec * 1000 + now.tv_sec / 1000);
}

void GameLayer::changeState(UIState* state){
    this->setCurrentState(state);
    GM->gameStateCheck();
}

void GameLayer::changeIndicatorState(const char *label){
    visualIndicatorLabel->setString(label);
    /*
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
    }else if(indicatorState == DiscardCard){
        visualIndicatorLabel->setString("Must Discard a Card");
    }else if(indicatorState == DrawCard){
        visualIndicatorLabel->setString("Must Draw a Card");
    }else if(indicatorState == BuyCard){
        visualIndicatorLabel->setString("Drag to Discard to Buy Card");
    }else if(indicatorState == DrawCard_DiscardCard){
        visualIndicatorLabel->setString("Must Discard a Card");
    }
     */
}

void GameLayer::enterZoomState(){
    zoomLayer->setVisible(true);
}

void GameLayer::leaveZoomState(){
    zoomLayer->setVisible(false);
}

void GameLayer::updateInterface(){
    handLayer->updateInterface();
    monsterLayer->updateInterface();
}

void GameLayer::enableRightButtonMustEndTurnInteractive()
{

    /*rightButton->setEnabled(true);
    
    rightButton->setColor(ccGREEN);
    rightButtonLabel->setColor(ccRED);
    rightButtonLabel->setScale(1.4);
    rightButtonGlow->setVisible(true);
    */
}

void GameLayer::enableRightButtonInteractive(){
    rightButton->setVisible(true);
    rightButton->setEnabled(true);
/*    rightButton->setEnabled(true);
    rightButton->setColor(ccWHITE);
    rightButtonLabel->setColor(ccWHITE);
    rightButtonLabel->setScale(1.0);
    rightButtonGlow->setVisible(true);
    */
}

void GameLayer::disableRightButtonInteractive(){
    rightButton->setVisible(false);
    rightButton->setEnabled(false);
//    rightButtonGlow->setVisible(false);
}


void GameLayer::enableLeftButtonInteractive(){
    leftButton->setVisible(true);
    leftButton->setEnabled(true);
//    leftButtonGlow->setVisible(true);
}

void GameLayer::disableLeftButtonInteractive(){
    leftButton->setEnabled(false);
    leftButton->setVisible(false);
//    leftButtonGlow->setVisible(false);
}

void GameLayer::enablePlayAreaInteractive(){
//    playAreaGlow->setVisible(true);
}

void GameLayer::disablePlayAreaInteractive(){
  //  playAreaGlow->setVisible(false);
}


#pragma mark - global positioning



void GameLayer::newRound()
{
    currentState->transitionToNormalState();
}
    
