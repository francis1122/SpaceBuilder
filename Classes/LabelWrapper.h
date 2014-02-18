//
//  LabelWrapper.h
//  RogueDeck
//
//  Created by Hunter Francis on 2/8/14.
//
//

#ifndef __RogueDeck__LabelWrapper__
#define __RogueDeck__LabelWrapper__

#include "cocos2d.h"
#include "BaseObject.h"
USING_NS_CC;
class LabelWrapper : public BaseObject
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool initWithLabel(CCLabelTTF *label);
    
    
};

#endif /* defined(__RogueDeck__LabelWrapper__) */
