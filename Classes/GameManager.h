//
//  GameManager.h
//  RogueDeck
//
//  Created by Hunter Francis on 11/17/13.
//
//

#ifndef __RogueDeck__GameManager__
#define __RogueDeck__GameManager__

#include "cocos2d.h"
#include "GameLayer.h"
#include "CardSprite.h"
#include "Player.h"

USING_NS_CC;
class LevelTemplate;
class GameManager
{
private:
    //Constructor
    GameManager();
    
    //Instance of the singleton
    static GameManager* m_mySingleton;
    
public:
    //Get instance of singleton
    static GameManager* sharedGameManager();
    
    bool isInteractive;
    
    GameLayer *gameLayer;
    Player *player;
    
    
    CCArray *solarSystemArray;
    
    //level/round information
    int currentLevel;
    int currentTurn;
    
    
    void startNewGame();
    void setIsInteractive(bool value);
    //checked to remove monsters or update cards that weren't affected directly
    
    void gameStateCheck();
    void afterCardPlayedStateCheck();
    
    //endTurn
    bool hasMorePlayerInteraction();
    void endTurn();
    
    //solar system
    void createNodes();
    void updateNodes();
    
    
};

#endif /* defined(__RogueDeck__GameManager__) */
