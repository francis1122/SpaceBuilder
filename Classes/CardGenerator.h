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
#include "CardTemplate.h"

typedef CardTemplate* (*createFunc)(void); // function pointer type
typedef std::map<std::string, createFunc> script_map;

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
    
    CardSprite* createCard(float powerLevel);
    
    CardSprite* chooseCardColor(float powerLevel);

    CardSprite* cardForRed(float powerLevel);
    CardSprite* cardForBlue(float powerLevel);
    CardSprite* cardForYellow(float powerLevel);
    CardSprite* cardForGreen(float powerLevel);
    CardSprite* cardForNeutral(float powerLevel);
    
    

    
    
    script_map map;
    
    void registerClass(const std::string& pFunction, createFunc function);
    
    CardTemplate* createClass(const std::string& pFunction);
    
};
#endif /* defined(__RogueDeck__CardGenerator__) */
