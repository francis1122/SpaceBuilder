//
//  CCShake.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 2/11/14.
//
//

#include "CCShake.h"
#include "cocos2d.h"

USING_NS_CC;

bool CCShake::init(float ptime, CCPoint pamplitude, bool pdampening, int pshakeNum)
{
    if ( !CCActionInterval::initWithDuration(ptime) )
    {
        return false;
    }
    {
		startAmplitude	= pamplitude;
		dampening	= pdampening;
        
		// calculate shake intervals based on the number of shakes
		if(pshakeNum == CCSHAKE_EVERY_FRAME)
			shakeInterval = 0;
        else
            shakeInterval = 1.f/pshakeNum;
    }
    
	return true;

}

void CCShake::startWithTarget(CCNode *aTarget)
{
    CCActionInterval::startWithTarget(aTarget);
	amplitude	= startAmplitude;
	last		= CCPointZero;
	nextShake	= 0;
}

void CCShake::stop()
{
	// undo the last shake
    m_pTarget->setPosition(ccpSub(m_pTarget->getPosition(), last));
    CCActionInterval::stop();
}

void CCShake::update(float t)
{
	// waits until enough time has passed for the next shake
	if(shakeInterval == CCSHAKE_EVERY_FRAME)
    {} // shake every frame!
	else if(t < nextShake)
		return; // haven't reached the next shake point yet
	else
		nextShake += shakeInterval; // proceed with shake this time and increment for next shake goal
        
        // calculate the dampening effect, if being used
        if(dampening)
        {
            float dFactor = (1-t);
            amplitude.x = dFactor * startAmplitude.x;
            amplitude.y = dFactor * startAmplitude.y;
        }
    
	CCPoint newPos = ccp((CCRANDOM_0_1()*amplitude.x*2) - amplitude.x,(CCRANDOM_0_1()*amplitude.y*2) - amplitude.y);
    
	// simultaneously un-move the last shake and move the next shake
    m_pTarget->setPosition(ccpAdd(ccpSub(m_pTarget->getPosition(), last), newPos));
//	m_pTarget->setPosition(ccpAdd(ccpSub(m_pTarget->getPosition(), last),new));
    
	// store the current shake value so it can be un-done
	last = newPos;
}

/*
- (id) initWithDuration:(ccTime)t amplitude:(CGPoint)pamplitude dampening:(bool)pdampening shakes:(int)shakeNum
{
 if((self=[super initWithDuration:t]) != nil)
 {
    startAmplitude	= pamplitude;
    dampening	= pdampening;
 
 // calculate shake intervals based on the number of shakes
    if(shakeNum == CCSHAKE_EVERY_FRAME)
        shakeInterval = 0;
    else
        shakeInterval = 1.f/shakeNum;
 }
 
 return self;
}

- (id) copyWithZone: (NSZone*) zone
{
	CCAction *copy = [[[self class] allocWithZone: zone] initWithDuration:[self duration] amplitude:amplitude dampening:dampening shakes:shakeInterval == 0 ? 0 : 1/shakeInterval];
	return copy;
}

- (void) startWithTarget:(CCNode *)aTarget
{
	[super startWithTarget:aTarget];
    
	amplitude	= startAmplitude;
	last		= CGPointZero;
	nextShake	= 0;
}

- (void) stop
{
	// undo the last shake
	[_target setPosition:ccpSub(((CCNode*)_target).position, last)];
    
	[super stop];
}

- (void) update:(ccTime)t
{
	// waits until enough time has passed for the next shake
	if(shakeInterval == CCSHAKE_EVERY_FRAME)
    {} // shake every frame!
	else if(t < nextShake)
		return; // haven't reached the next shake point yet
	else
		nextShake += shakeInterval; // proceed with shake this time and increment for next shake goal
        
        // calculate the dampening effect, if being used
        if(dampening)
        {
            float dFactor = (1-t);
            amplitude.x = dFactor * startAmplitude.x;
            amplitude.y = dFactor * startAmplitude.y;
        }
    
	CGPoint new = ccp((CCRANDOM_0_1()*amplitude.x*2) - amplitude.x,(CCRANDOM_0_1()*amplitude.y*2) - amplitude.y);
    
	// simultaneously un-move the last shake and move the next shake
	[_target setPosition:ccpAdd(ccpSub(((CCNode*)_target).position, last),new)];
    
	// store the current shake value so it can be un-done
	last = new;
}
*/

