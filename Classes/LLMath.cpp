//
//  LLMath.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 12/20/13.
//
//

#include "LLMath.h"

USING_NS_CC;

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

CCPoint LLMath::truncate(CCPoint vector, float max){
    float magnitude = ccpLength(vector);
    //	float magnitude = sqrt(pow(vector.x,2) + pow(vector.y,2));
	if (magnitude > max) {
		return CCPointMake((vector.x / (magnitude + .001)) * max, (vector.y / (magnitude + .001)) * max);
	}
	else {
		return vector;
	}
}


#pragma mark - 2D geometry


bool LLMath::intersectionCheck(CCPoint a, CCPoint b, CCPoint c, CCPoint d)
{
    CCPoint ab = makeVector(a, b);
    CCPoint cd = makeVector(c, d);
    
    if (areParallelVectors(ab, cd))
        return false;
//        return IntersectionType.Parallel;
    
    //might want <= for checks
    if ((value(a, c, d) * value(b, c, d) < 0) && (value(c, a, b) * value(d, a, b) < 0))
        return true;
  //      return IntersectionType.InsideSegment;
    else
        return false;
    //    return IntersectionType.OutsideSegment;
}

CCPoint LLMath::makeVector(CCPoint a, CCPoint b){
    return ccp(b.x - a.x, b.y - a.y);
}


// computes the result of line(ab) equation for point p
// this value is 0 if p is on (ab)
float LLMath::value(CCPoint p, CCPoint a, CCPoint b)
{
    CCPoint d = makeVector(a, b);
    
    return d.y * p.x - d.x * p.y + d.x * a.y - d.y * a.x;
}

// return true if the vector could be normalized (length != 0), false otherwise
bool LLMath::normalized(CCPoint &v)
{
    float lg = ccpLength(v);
    
    if (lg == 0)
    {
        return false;
    }
    else
    {
//        MultiplyVector(1/lg, ref v);
        v = ccpMult(v, 1/lg);
        return true;
    }
}

bool LLMath::areParallelVectors(CCPoint v, CCPoint w)
{
    CCPoint vp = v;
    normalized(vp);
    
    CCPoint wp = w;
    normalized(wp);
    
    if (vp.x == wp.x && vp.y == wp.y)
        return true;
    
    return false;
}
