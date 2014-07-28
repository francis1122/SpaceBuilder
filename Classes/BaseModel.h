//
//  BaseModel.h
//  RogueDeck
//
//  Created by Hunter Francis on 7/22/14.
//
//

#ifndef __RogueDeck__BaseModel__
#define __RogueDeck__BaseModel__

#include "cocos2d.h"
USING_NS_CC;

class SolarSystemObject;
class BaseModel : public CCObject
{
public:
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static node()" method manually
    CREATE_FUNC(BaseModel);
    
};


#endif /* defined(__RogueDeck__BaseModel__) */
