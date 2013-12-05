//
//  CardGenerator.h
//  RogueDeck
//
//  Created by Hunter Francis on 11/27/13.
//
//

#ifndef __RogueDeck__CardGenerator__
#define __RogueDeck__CardGenerator__

#include "cocos2d.h"

USING_NS_CC;
class CardSprite;
class CardGenerator
{
private:
    //Constructor
    CardGenerator();
    
    //Instance of the singleton
    static CardGenerator* m_mySingleton;
    
public:
    //Get instance of singleton
    static CardGenerator* sharedGameManager();
    
    CardSprite* createCard(int powerLevel);
    
    
};
#endif /* defined(__RogueDeck__CardGenerator__) */
