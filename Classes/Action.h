//
//  Action.h
//  RogueDeck
//
//  Created by Hunter Francis on 12/10/13.
//
//

#ifndef __RogueDeck__Action__
#define __RogueDeck__Action__

#include "cocos2d.h"

typedef enum ActionType{
    Neutral,
    Red,
    Blue,
    Green,
    Yellow
} ActionType;


USING_NS_CC;


class Action : public CCObject
{
public:
    bool init(ActionType type);

    ActionType actionType;
    
    ccColor3B getActionColor();
};

#endif /* defined(__RogueDeck__Action__) */
