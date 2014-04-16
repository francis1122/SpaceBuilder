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
    
    //holds levels that can be played, used to create the BetweenRoundLayer Map
    CCArray *possibleLevelArray;
    
    //monster spawn stuff
    LevelTemplate *currentLevelTemplate;
    
    //level/round information
    int currentLevel;
    int currentTurn;
    
    //monster variables
    CCArray *locationArray;
    CCArray *monsterArray;
    CCArray *marketCardArray;
    
    void generateLevels();
    void startNewGame();
    void startNewRound(LevelTemplate *newLevel);
    void setIsInteractive(bool value);
    //checked to remove monsters or update cards that weren't affected directly
    
    void gameStateCheck();
    void afterCardPlayedStateCheck();
    
    //endTurn
    bool hasMorePlayerInteraction();
    void endTurn();
    
    //market stuff
    void organizeMarketAlt();
    void organizeMarket();
    void sellCard(CardSprite* card);
    void addMarketCard(CardSprite* marketCard);
    void removeMarketCard(CardSprite *marketCard);
    bool buyCardFromMarket(CardSprite *marketCard);
    void marketTurn();
    

    
    void organizeMonsters();
    void removeMonster(MonsterSprite *monster);
    void spawnMonster();
    void addMonstersPhase();
    void monsterTurn();
    
    //helper functions
    bool tauntPresent();
    
};

#endif /* defined(__RogueDeck__GameManager__) */
