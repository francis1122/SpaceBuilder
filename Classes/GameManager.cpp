//
//  GameManager.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/17/13.
//
//

#include "GameManager.h"
#include "CardSprite.h"
#include "HandLayer.h"
#include "Statuses.h"
#include "MonsterSprite.h"
#include "MonsterHealthOffsetStatus.h"
#include "MarketLayer.h"
#include "MonsterGenerator.h"
#include "TitleLayer.h"
#include "PostRoundLayer.h"
#include "CardGenerator.h"

using namespace cocos2d;

//All static variables need to be defined in the .cpp file
//I've added this following line to fix the problem
GameManager* GameManager::m_mySingleton = NULL;

GameManager::GameManager()
{
    
    this->monsterArray = new CCArray();
    this->monsterArray->init();
    this->marketCardArray = new CCArray();
    this->marketCardArray->init();
    

    this->player = new Player();

    currentLevel = 2;
    monstersLeft = 2;
    currentTurn = 1;
    
//        Monster *card = CardSprite::create();
  //      libraryCards->addObject(card);
    //    deckCards->addObject(card);

    
/*
    CCSprite *sprite1 = CCSprite::create();
    CCSprite *sprite2 = CCSprite::create();
    
    this->deckCards->addObject(sprite1);
    this->deckCards->addObject(sprite2);
    CCLog("capcity %i", this->deckCards->capacity());
  */
}

GameManager* GameManager::sharedGameManager()
{
    //If the singleton has no instance yet, create one
    if(NULL == m_mySingleton)
    {
        //Create an instance to the singleton
        m_mySingleton = new GameManager();
    }
    
    //Return the singleton object
    return m_mySingleton;
}

void GameManager::startNewGame(){
    delete player;
    player = NULL;
    player = new Player();
    
    currentLevel = 2;
    monstersLeft = 2;
    currentTurn = 1;
    monsterArray->removeAllObjects();
    marketCardArray->removeAllObjects();
}

void GameManager::startNewRound(int level){
    player->reset();
    currentLevel = level;
    monstersLeft = 1 + level;
    currentTurn = 1;
    monsterArray->removeAllObjects();
    marketCardArray->removeAllObjects();
    addMonstersPhase();
    player->drawHand();
    gameLayer->updateInterface();
}


#pragma mark -update the gameState from various points


void GameManager::gameStateCheck(){
    //check for dead monsters
    for(int i = monsterArray->count() - 1; i >= 0; i--){
        MonsterSprite *monster = (MonsterSprite*)monsterArray->objectAtIndex(i);
        if(monster->life <= 0){
            this->removeMonster(monster);
        }
    }
    
    //check for player death
    if(player->health <= 0){
        //TODO: make death screen to go to
        CCDirector* pDirector = CCDirector::sharedDirector();
        CCScene *pScene = TitleLayer::scene();
        // run
        pDirector->replaceScene(pScene);
    }
    
    //if all monsters are dead and no market cards are left
    if(monstersLeft <= 0 && monsterArray->count() <= 0 && marketCardArray->count()<= 0){
        //go to postRoundLayer
        CCDirector* pDirector = CCDirector::sharedDirector();
        CCScene *pScene = PostRoundLayer::scene();
        // run
        pDirector->replaceScene(pScene);
    }
}

void GameManager::afterCardPlayedStateCheck(){
    //check for dead monsters
    for(int i = monsterArray->count() - 1; i >= 0; i--){
        MonsterSprite *monster = (MonsterSprite*)monsterArray->objectAtIndex(i);
        
        
        

        
        if(monster->life <= 0){
            //activate killing blow
            CCObject *object = NULL;
            CCARRAY_FOREACH(monster->killingBlowArray, object){
                DeathBlowStatus *deathBlowStatus = (DeathBlowStatus*)object;
                deathBlowStatus->applyStatus();
            }
            
            this->removeMonster(monster);
        }
        
        //clear temp statuses
        monster->killingBlowArray->removeAllObjects();
    }
    
    //check for player death
    if(player->health <= 0){
        //TODO: make death screen to go to
        CCDirector* pDirector = CCDirector::sharedDirector();
        CCScene *pScene = TitleLayer::scene();
        // run
        pDirector->replaceScene(pScene);
    }
    
    //if all monsters are dead and no market cards are left
    if(monstersLeft <= 0 && monsterArray->count() <= 0 && marketCardArray->count()<= 0){
        //go to postRoundLayer
        CCDirector* pDirector = CCDirector::sharedDirector();
        CCScene *pScene = PostRoundLayer::scene();
        // run
        pDirector->replaceScene(pScene);
    }
}


void GameManager::endTurn(){
    player->discardHand();
    player->discardPlayedCards();
    player->drawHand();
    player->organizeHand();
    //set round stuff
    //player health or soul can't be above deck count
    if(player->health > player->maxHealth){
        player->health = player->maxHealth;
    }
    if(player->soul > player->maxSoul){
        player->soul = player->maxSoul;
    }
    player->actionsLeft = 2;
    currentTurn++;
    this->marketTurn();
    this->monsterTurn();
    gameLayer->updateInterface();

}

#pragma mark - market stuff

//market stuff
void GameManager::organizeMarket(){
    int i= 0,j = 0;
    CCObject *object;
    CCARRAY_FOREACH(marketCardArray, object){
        CardSprite *card = (CardSprite*)object;
        if(card->turnsLeftInMarket == 1){
            i++;
            card->setPosition(CCPointMake(850 + i * 60, 400));
        }else if(card->turnsLeftInMarket == 2){
            j++;
            card->setPosition(CCPointMake(850 + j * 60, 540));
        }else if( card->turnsLeftInMarket== 0){
            CCLog("card should be removed from market and destroyed");
        }

    }
}

void GameManager::sellCard(CardSprite* card){
    //give player money
    player->soul += card->soulCost;
    player->actionsLeft--;

    //remove card from deck and hand
    player->removeCard(card);
}

void GameManager::addMarketCard(CardSprite* marketCard){
    this->marketCardArray->addObject(marketCard);
    this->gameLayer->addChild(marketCard);
    
    this->organizeMarket();
}

void GameManager::removeMarketCard(CardSprite *marketCard){
    this->marketCardArray->removeObject(marketCard);
    marketCard->removeFromParent();
}

bool GameManager::buyCardFromMarket(CardSprite *marketCard){
    //check if card is a market card
    if(marketCardArray->containsObject(marketCard)){
        if(player->soul >= marketCard->soulCost){
            player->soul -= marketCard->soulCost;
            player->actionsLeft--;
            this->player->acquireCard(marketCard);
            marketCard->removeFromParent();
            this->removeMarketCard(marketCard);
        return true;
        }else{
            CCLog("need more soul");
            return false;
        }
    }else{
        CCLog("not a market card");
        return false;
    }
}

void GameManager::marketTurn(){
    for(int i = marketCardArray->count() - 1; i >= 0; i--){
        CardSprite *card = (CardSprite*)marketCardArray->objectAtIndex(i);
        card->turnsLeftInMarket--;
        if(card->turnsLeftInMarket <= 0){
            this->removeMarketCard(card);
        }
    }
    this->organizeMarket();
}

#pragma mark - monster stuff

void GameManager::organizeMonsters(){
    CCObject *object;
    CCARRAY_FOREACH(monsterArray, object){
        MonsterSprite *monster = (MonsterSprite*)object;
        monster->setPosition(CCPointMake(150 + monster->lane * 150, 400 + monster->location * 40));
    }
}

void GameManager::removeMonster(MonsterSprite *monster){
    monster->removeFromParent();
    monsterArray->removeObject(monster);
    
    //add card to market
    CardSprite *card = CardGenerator::sharedGameManager()->createCard(currentLevel);
    card->turnsLeftInMarket = 2;
    this->addMarketCard(card);
    this->organizeMarket();
}


void GameManager::spawnMonster(){
    MonsterSprite *monster = MonsterGenerator::sharedGameManager()->createMonster(currentLevel);
    //give monster the correct lane
    
    //cycle through monsters to see what lane is open
    int maxMonsters = MIN(currentTurn, 4);
    int newLane = -1;
    for(int j = 0; j < maxMonsters; j++){
        bool emptyLane = true;
        for(int i = 0; i < monsterArray->count(); i++){
            MonsterSprite *monster = (MonsterSprite*)monsterArray->objectAtIndex(i);
            if(monster->lane == j){
                emptyLane = false;
                break;
            }
        }
        if(emptyLane){
            newLane = j;
            break;
        }
    }
    //yrdy
    if(newLane != -1){
        monster->lane = newLane;
    }
    
    monstersLeft--;
    this->gameLayer->addChild(monster);
    monster->updateInterface();
    
    this->monsterArray->addObject(monster);
}

void GameManager::addMonstersPhase(){
    //monsters allowed to spawn
    int maxMonsters = MIN(currentTurn, 4);
    
    while(monsterArray->count() < maxMonsters && monstersLeft > 0){
        this->spawnMonster();
    }
    this->organizeMonsters();
}

void GameManager::monsterTurn(){
    CCObject *object;
    CCARRAY_FOREACH(monsterArray, object){
        MonsterSprite *monster = (MonsterSprite*)object;
        monster->turnUpdate();
    }
    //used to check if monster died during its update step
    this->gameStateCheck();
    //if there are not enough monsters on the board, add a monster
    this->addMonstersPhase();
}




