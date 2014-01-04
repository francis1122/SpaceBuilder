//
//  TopSlideLayer.h
//  RogueDeck
//
//  Created by Hunter Francis on 1/3/14.
//
//

#ifndef __RogueDeck__TopSlideLayer__
#define __RogueDeck__TopSlideLayer__


#include "cocos2d.h"

USING_NS_CC;

class TopSlideLayer : public CCLayer
{
public:
    
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    
    // implement the "static node()" method manually
    CREATE_FUNC(TopSlideLayer);
    
    
private:
    
};

#endif /* defined(__RogueDeck__TopSlideLayer__) */
