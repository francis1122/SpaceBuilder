//
//  IRDSTable.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 12/19/13.
//
//

#include "IRDSTable.h"
#include "LLMath.h"

IRDSTable::IRDSTable()
{
    rdsContents = new CCArray();
    rdsContents->init();
}


IRDSObject* IRDSTable::rdsResult(float powerLevel){
    
    // Now calculate the real dropcount, this is the table's count minus the
    // number of Always-drops.
    // It is possible, that the remaining drops go below zero, in which case
    // no other objects will be added to the result here.
    CCArray *filteredArray = new CCArray();
    filteredArray->init();
    filteredArray->autorelease();
    
    for(int i = 0; i < rdsContents->count(); i++){
        IRDSObject *object = (IRDSObject*)rdsContents->objectAtIndex(i);
        object->checkIfUsable(powerLevel);
        if(object->rdsEnabled){
            filteredArray->addObject(object);
        }
        
        
    }
    
    double probCount = 0;
    for(int i = 0; i < filteredArray->count(); i++){
        IRDSObject *object = (IRDSObject*)filteredArray->objectAtIndex(i);
        probCount += object->rdsProbability;
    }
    
    //Todo::should be a double
    double hitValue = LLMath::getDoubleValue(probCount);
    double runningValue = 0.0;
    for(int i = 0; i < filteredArray->count(); i++){
        IRDSObject *object = (IRDSObject*)filteredArray->objectAtIndex(i);
        runningValue += object->rdsProbability;
        if(runningValue > hitValue){
            return object;
        }
    }

    return (IRDSObject*)filteredArray->lastObject();
}

