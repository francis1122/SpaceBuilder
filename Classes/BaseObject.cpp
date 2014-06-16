//
//  BaseObject.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/7/14.
//
//

#include "BaseObject.h"

USING_NS_CC;

bool BaseObject::initDefaultState()
{
    isZoomed = false;
    isInteractive = false;
    cardsAffectingNode = new CCArray();
    cardsAffectingNode->init();

    return true;
    
    
}


void BaseObject::removeBaseObject()
{
    this->removeFromParentAndCleanup(true);
    
}


void BaseObject::doDamage()
{
    
}