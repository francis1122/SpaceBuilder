//
//  CCShake.h
//  RogueDeck
//
//  Created by Hunter Francis on 2/11/14.
//
//

#ifndef __RogueDeck__CCShake__
#define __RogueDeck__CCShake__

#include "cocos2d.h"
USING_NS_CC;

#define CCSHAKE_EVERY_FRAME	0

class CCShake : public CCActionInterval
{
public:
    float shakeInterval;
	float nextShake;
	bool dampening;
	CCPoint startAmplitude;
	CCPoint amplitude;
	CCPoint last;
    
    bool init(float ptime, CCPoint pamplitude, bool pdampening, int pshakeNum);
    
    virtual void startWithTarget(CCNode *aTarget);
    virtual void stop();
    virtual void update(float t);
    
};
/*
@interface CCShake : CCActionInterval
{
	float shakeInterval;
	float nextShake;
	bool dampening;
	CGPoint startAmplitude;
	CGPoint amplitude;
	CGPoint last;
}

+ (id) actionWithDuration:(ccTime)t amplitude:(CGPoint)pamplitude;
+ (id) actionWithDuration:(ccTime)t amplitude:(CGPoint)pamplitude dampening:(bool)pdampening;
+ (id) actionWithDuration:(ccTime)t amplitude:(CGPoint)pamplitude shakes:(int)pshakeNum;
+ (id) actionWithDuration:(ccTime)t amplitude:(CGPoint)pamplitude dampening:(bool)pdampening shakes:(int)pshakeNum;
- (id) initWithDuration:(ccTime)t amplitude:(CGPoint)pamplitude dampening:(bool)pdampening shakes:(int)pshakeNum;

@end*/

#endif /* defined(__RogueDeck__CCShake__) */
