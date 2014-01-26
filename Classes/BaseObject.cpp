//
//  BaseObject.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/7/14.
//
//

#include "BaseObject.h"


bool BaseObject::initDefaultState()
{
    isZoomed = false;
    isInteractive = false;
    return true;
}


void BaseObject::removeBaseObject(){
    this->removeFromParentAndCleanup(true);
    
}