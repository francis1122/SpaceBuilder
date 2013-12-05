//
//  TitleLayer.h
//  RogueDeck
//
//  Created by Hunter Francis on 11/17/13.
//
//

#ifndef __RogueDeck__TitleLayer__
#define __RogueDeck__TitleLayer__

#include "cocos2d.h"

class TitleLayer : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(TitleLayer);
    
    // a selector callback
    void startGame(CCObject* pSender);
    
private:

};
#endif /* defined(__RogueDeck__TitleLayer__) */
