//
//  PostRoundLayer.h
//  RogueDeck
//
//  Created by Hunter Francis on 11/26/13.
//
//

#ifndef __RogueDeck__PostRoundLayer__
#define __RogueDeck__PostRoundLayer__

#include "cocos2d.h"

class PostRoundLayer : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(PostRoundLayer);
    
    void nextRound(CCObject* pSender);
    
private:
    
};

#endif /* defined(__RogueDeck__PostRoundLayer__) */
