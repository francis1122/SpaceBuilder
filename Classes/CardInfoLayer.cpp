//
//  CardInfoLayer.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 7/22/14.
//
//

#include "CardInfoLayer.h"

#include "GameManager.h"
#include "UIState.h"
#include "GameLayer.h"
#include "Constants.h"
#include "SolarSystemObject.h"
#include "UIState.h"
#include "Utility.h"
#include "Player.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool CardInfoLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCLayerColor *bg = CCLayerColor::create(ccc4(50, 50, 50, 100));
    //     bg->setPosition(ccp( bg->getContentSize().width/2, bg->getContentSize().height/2 + 310));
    this->addChild(bg);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    

    
    return true;
}


void CardInfoLayer::updateInterface()
{
    
    
}

