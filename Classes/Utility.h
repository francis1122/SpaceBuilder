//
//  Utility.h
//  RogueDeck
//
//  Created by Hunter Francis on 1/18/14.
//
//

#ifndef __RogueDeck__Utility__
#define __RogueDeck__Utility__

#include "cocos2d.h"
USING_NS_CC;

class Utility{
    
public:
    
    
    static CCRenderTexture* createTTFStroke(CCSprite* label, int size, ccColor3B color, GLubyte opacity);
    
};

#endif /* defined(__RogueDeck__Utility__) */
