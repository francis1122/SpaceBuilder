//
//  LLMath.h
//  RogueDeck
//
//  Created by Hunter Francis on 12/20/13.
//
//

#ifndef __RogueDeck__LLMath__
#define __RogueDeck__LLMath__

#include "cocos2d.h"
USING_NS_CC;

class LLMath{
    
public:
    
    static double getDoubleValue(double max);             // From 0.0 (incl) to max (excl)
    static double getDoubleValue(double min, double max); // From min (incl) to max (excl)
    
    static int getIntValue(int max); // From   0 (incl) to max (excl

    static int getIntValue(int min, int max); // From min (incl) to max (excl)
    
    static int diceRoll(int range, int count);
    
    static CCPoint truncate(CCPoint vector, float max);
    
    
    //2d geometry
    static bool intersectionCheck(CCPoint a, CCPoint b, CCPoint c, CCPoint d);
    
    static CCPoint makeVector(CCPoint a, CCPoint b);
    
    static float value(CCPoint p, CCPoint a, CCPoint b);
    
    static bool normalized(CCPoint &v);
    
    static bool areParallelVectors(CCPoint v, CCPoint w);
    
};

#endif /* defined(__RogueDeck__LLMath__) */
