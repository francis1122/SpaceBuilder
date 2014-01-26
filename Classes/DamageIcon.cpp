//
//  DamageIcon.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/20/14.
//
//

#include "DamageIcon.h"

#include "Player.h"
#include "Statuses.h"
#include "Constants.h"
#include "Utility.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool DamageIcon::init(int damage)
{
    //////////////////////////////
    // 1. super init first
    
    if (!CCSprite::initWithSpriteFrameName("damageIcon"))
    {
        return false;
    }
    isZoomed = false;
    isInteractive = false;
    //label for damage
    CCLabelTTF *damageLabel =  CCLabelTTF::create("", LARGE_NUMBER_FONT, 178);
    damageLabel->setColor(ccWHITE);
    damageLabel->setPosition(CCPointMake(255, 195));
    
    CCString *damageString = CCString::createWithFormat("%i", damage);
    damageLabel->setString(damageString->getCString());
    
    this->addChild(damageLabel, 1);
    
    CCRenderTexture *damageShadow = Utility::createTTFStroke(damageLabel, 7, ccBLACK, 255);
    this->addChild(damageShadow, 0);
    
    this->setCascadeOpacityEnabled(true);
    
    return true;
}