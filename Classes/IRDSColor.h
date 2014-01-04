//
//  IRDSColor.h
//  RogueDeck
//
//  Created by Hunter Francis on 12/19/13.
//
//

#ifndef __RogueDeck__IRDSColor__
#define __RogueDeck__IRDSColor__
#include "IRDSObject.h"
#include "Action.h"

class IRDSColor : public IRDSObject
{
    
public:
    IRDSColor(ActionType chosenColor, double odds);
    ActionType color;
};


#endif /* defined(__RogueDeck__IRDSColor__) */
