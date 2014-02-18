//
//  LabelWrapper.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 2/8/14.
//
//

#include "LabelWrapper.h"

#include "Player.h"
#include "Statuses.h"
#include "Constants.h"
#include "Utility.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool LabelWrapper::initWithLabel(CCLabelTTF *label)
{
    //////////////////////////////
    // 1. super init first
    
    if (!CCSprite::init())
    {
        return false;
    }
    isZoomed = false;
    isInteractive = false;
    //label for damage
    this->addChild(label, 1);
    this->setCascadeOpacityEnabled(true);
    
    return true;
}
