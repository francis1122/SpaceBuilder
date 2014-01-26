//
//  DamageIcon.h
//  RogueDeck
//
//  Created by Hunter Francis on 1/20/14.
//
//

#ifndef __RogueDeck__DamageIcon__
#define __RogueDeck__DamageIcon__


#include "cocos2d.h"
#include "BaseObject.h"
USING_NS_CC;
class DamageIcon : public BaseObject
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(int damage);
    
    
};

#endif /* defined(__RogueDeck__DamageIcon__) */
