//
//  IRDSTable.h
//  RogueDeck
//
//  Created by Hunter Francis on 12/19/13.
//
//

#ifndef __RogueDeck__IRDSTable__
#define __RogueDeck__IRDSTable__

#include <iostream>
#include "IRDSObject.h"
#include "cocos2d.h"

USING_NS_CC;

class IRDSTable : public IRDSObject
{
    
public:
    IRDSTable();
    CCArray* rdsContents; // The contents of the table
    IRDSObject* rdsResult(float powerLevel);   // The Result set
    
};


#endif /* defined(__RogueDeck__IRDSTable__) */
