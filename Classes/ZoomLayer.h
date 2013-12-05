//
//  ZoomLayer.h
//  RogueDeck
//
//  Created by Hunter Francis on 11/27/13.
//
//

#ifndef __RogueDeck__ZoomLayer__
#define __RogueDeck__ZoomLayer__


#include "cocos2d.h"

USING_NS_CC;

class ZoomLayer : public CCLayer
{
public:
    
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    
    // implement the "static node()" method manually
    CREATE_FUNC(ZoomLayer);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    
    void leaveZoom(CCObject* pSender);
    
private:
    
};

#endif /* defined(__RogueDeck__ZoomLayer__) */
