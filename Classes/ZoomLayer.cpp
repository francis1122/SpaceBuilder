//
//  ZoomLayer.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/27/13.
//
//

#include "ZoomLayer.h"
#include "GameManager.h"
#include "UIState.h"
#include "GameLayer.h"


USING_NS_CC;

// on "init" you need to initialize your instance
bool ZoomLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
//        CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    
     CCLayerColor *playArea = CCLayerColor::create(ccc4(80, 80, 80, 190), visibleSize.width, visibleSize.height);
     playArea->setPosition(CCPointMake(0, 0));
     addChild(playArea);
     
     
    
    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemLabel *pCloseItem = CCMenuItemLabel::create(CCLabelTTF::create("Close", "Arial", 64),
                                                          this,
                                                          menu_selector(ZoomLayer::leaveZoom));
                                                 
//    pCloseItem->
	pCloseItem->setPosition(ccp(700,
                                500));
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setTouchPriority(kCCMenuHandlerPriority - 2);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    //swallow all touches
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 1, true);
    this->setTouchEnabled(true);
    
    
    return true;
}


bool ZoomLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if(this->isVisible()){
        return true;
    }else{
        return false;
    }
}

void ZoomLayer::leaveZoom(CCObject* pSender)
{
    GameManager *GM = GameManager::sharedGameManager();
    GM->gameLayer->getCurrentState()->transitionToNormalState();
}


