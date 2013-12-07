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
    
    //A function that returns zero "0"
    int ReturnZero(){return 0;}
    // another test function
    void runScene() { CCLOG("test");};
    
    GameLayer *gameLayer;
    Player *player;
    
    //level/round information
    int currentLevel;
    int monstersLeft;
    int currentTurn;
    
    //monster variables
    CCArray *monsterArray;
    CCArray *marketCardArray;
    
    
    void startNewGame();
    void startNewRound(int level);
    
    //checked to remove monsters or update cards that weren't affected directly
    
    void gameStateCheck();
    void afterCardPlayedStateCheck();
    
    //endTurn
    void endTurn();
    
    //market stuff
    void organizeMarket();
    void sellCard(CardSprite* card);
    void addMarketCard(CardSprite* marketCard);
    void removeMarketCard(CardSprite *marketCard);
    bool buyCardFromMarket(CardSprite *marketCard);
    void marketTurn();
    
    //monster spawn stuff
    void organizeMonsters();
    void removeMonster(MonsterSprite *monster);
    void spawnMonster();
    void addMonstersPhase();
    void monsterTurn();
    
};

#endif /* defined(__RogueDeck__GameManager__) */
