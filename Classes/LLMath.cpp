//
//  LLMath.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 12/20/13.
//
//

#include "LLMath.h"


double LLMath::getDoubleValue(double max){
    
    double f = (double)arc4random() / UINT_MAX;
    return f * (max);
}

double LLMath::getDoubleValue(double min, double max){
    double f = (double)arc4random() / UINT_MAX;
    return min + f * (min - max);
}


int LLMath::getIntValue(int max){
    if(max <= 0){
        return 0;
    }
    return arc4random()%max;
}


int LLMath::getIntValue(int min, int max){
    if(min > max){
        return min;
    }
    
    if( min < 0 || max < 0){
        return 0;
    }
    
    return min + arc4random()%(max - min);
}

int LLMath::diceRoll(int range, int count){
    int total = 0;
    if(range < 1){
        range = 1;
    }
    for(int i = 0; i < count; i++){
        total += arc4random()%range;
    }
    return total;
}



