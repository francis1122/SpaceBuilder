//
//  MonsterLayer.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/3/14.
//
//

#include "MonsterLayer.h"
#include "GameManager.h"
#include "UIState.h"
#include "GameLayer.h"


USING_NS_CC;

// on "init" you need to initialize your instance
bool MonsterLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //        CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
/*
    CCLayerColor *playArea = CCLayerColor::create(ccc4(80, 80, 80, 190), visibleSize.width, visibleSize.height);
    playArea->setPosition(CCPointMake(0, 0));
    addChild(playArea);*/
    CCSprite *bg = CCSprite::createWithSpriteFrameName("MonsterLayerBG");
    bg->setPosition(ccp( bg->getContentSize().width/2, bg->getContentSize().height/2 + 310));
    this->addChild(bg);
    
    return true;
}


