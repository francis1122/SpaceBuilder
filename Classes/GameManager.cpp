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
#include "TitleLayer.h"
#include "PostRoundLayer.h"
#include "UIState.h"
#include "MonsterLayer.h"
#include "AnimationManager.h"
#include "AnimationObject.h"
#include "Constants.h"
#include "SolarSystemObject.h"
#include "LLMath.h"
#include "PassiveTargets.h"
#include "UniverseGenerator.h"
#include "ShipModel.h"
#include "ShipSprite.h"


using namespace cocos2d;

//All static variables need to be defined in the .cpp file
//I've added this following line to fix the problem
GameManager* GameManager::m_mySingleton = NULL;

GameManager::GameManager()
{
    AM;
    this->player = new Player();
    
    currentLevel = 1;
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
    solarSystemArray = new CCArray();
    shipsArray = new CCArray();
    
    solarSystemArray->init();
    shipsArray->init();
    
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

    CCDirector* pDirector = CCDirector::sharedDirector();
    CCScene *pScene = GameLayer::scene();
    
    // run
    pDirector->replaceScene(pScene);
    gameLayer->getCurrentState()->defaultInteractiveState();
    isInteractive = true;
    createNodes();
    player->setupPlayer();

    //give player a starting solar systems to player
    SolarSystemObject *system1 = (SolarSystemObject*)solarSystemArray->objectAtIndex(0);
    player->acquireSolarSystem( system1);

    player->reset();
    player->drawHand();
    player->organizeHand();
    
//    system2->cardSlots = 5;
    /*
    for(int i = 0; i < 5; i++){
        CardSprite *card = (CardSprite*)player->deckCards->objectAtIndex(i);
        card->setHomeSolarSystem(system1);
        system1->cardArray->addObject(card);
    }
    for(int i = 5; i < player->deckCards->count(); i++){
        CardSprite *card = (CardSprite*)player->deckCards->objectAtIndex(i);
        card->setHomeSolarSystem(system2);
        system2->cardArray->addObject(card);
    }

    */
    
    gameLayer->updateInterface();
    
    /*
     isInteractive = true;
     currentLevel = 1;
     currentTurn = 1;
     monsterArray->removeAllObjects();
     marketCardArray->removeAllObjects();
     addMonstersPhase();
     CCObject *object;
     CCARRAY_FOREACH(monsterArray, object){
     MonsterSprite *monster = (MonsterSprite*)object;
     monster->turnUpdate();
     }
     player->drawHand();
     player->organizeHand();
     gameLayer->updateInterface();
     gameLayer->getCurrentState()->defaultInteractiveState();
     
     isInteractive = true;
     */
    
}



#pragma mark -update the gameState from various points

void GameManager::gameStateCheck(){
    
}

void GameManager::afterCardPlayedStateCheck()
{
    

}

void GameManager::setIsInteractive(bool value)
{
    isInteractive = value;
    if(value == false){
        
    }
}

bool GameManager::hasMorePlayerInteraction(){
    bool hasCardToPlay = false;
    
    //check if cards from player hand can be played
    for(int i = 0; i < player->handCards->count(); i++){
//        CardSprite *card = (CardSprite*)player->handCards->objectAtIndex(i);
    }
    
    
    return (hasCardToPlay);
}

void GameManager::endTurn()
{
    gameLayer->getCurrentState()->transitionToMonsterTurnState();

    updateNodes();
    player->discardHand();
    player->discardPlayedCards();
    
    currentTurn++;
    
    //passive shit
    for(int i = 0; i < player->deckCards->count(); i++){
        CardSprite *card = (CardSprite*)player->deckCards->objectAtIndex(i);
        if(card->isPassive){
            PassiveTargets *passiveTarget = (PassiveTargets*)card->passiveTargets;
            passiveTarget->updateStatuses();
        }
    }
    
    player->drawHand();
    player->organizeHand();
    

    gameLayer->updateInterface();
    
    //transition back to normal state after all animations are done
    
    //    CCScaleTo *action = CCScaleTo::create(.05, .4);
    //    CCEaseIn *ease = CCEaseIn::create(action, 1.0);
    CCDelayTime *delay = CCDelayTime::create(1.5);
    CCCallFunc *obj = CCCallFunc::create(gameLayer, callfunc_selector(GameLayer::newRound));
    
    CCSequence *seq = CCSequence::create( delay, obj, NULL);
    gameLayer->runAction(seq);
    
}


void GameManager::addShip(ShipModel *shipModel)
{
    shipsArray->addObject(shipModel);
    shipModel->worldShipSprite = new ShipSprite();
    shipModel->worldShipSprite->initWithSpriteFrameName(shipModel->shipSpriteName->getCString());
    shipModel->worldShipSprite->shipModel = shipModel;
    gameLayer->monsterLayer->addChild(shipModel->worldShipSprite);
    shipModel->worldShipSprite->updateInterface();
    
}


void GameManager::removeShip(ShipModel *shipModel)
{
    gameLayer->monsterLayer->removeChild(shipModel->worldShipSprite);
    shipsArray->removeObject(shipModel);
}

#pragma mark - solar system
void GameManager::createNodes()
{
    solarSystemArray = UniverseGenerator::createUniverse();
    
    //add them to monster layer
    for(int i = 0; i < solarSystemArray->count(); i++){
        SolarSystemObject *solarSystem = (SolarSystemObject*)solarSystemArray->objectAtIndex(i);
        gameLayer->monsterLayer->addChild(solarSystem);
        
        //create connections
        for(int j = 0; j < solarSystem->connectedSystems->count(); j++){
            SolarSystemObject *solarSystemB = (SolarSystemObject*)solarSystem->connectedSystems->objectAtIndex(j);
            //temp:: add graphical sprite at midpoint between systems to show path
            CCSprite *road = CCSprite::createWithSpriteFrameName("waypoint");
            road->setAnchorPoint(ccp(.5, .5));
//            road->setScale(.5);
            CCPoint posA = solarSystem->getPosition();
            CCPoint posB = solarSystemB->getPosition();
            road->setPosition(ccpMidpoint(posA, posB));
            
            float dx = posA.x - posB.x;
            float dy = posA.y - posB.y;
            float angle = atan2f(dy,dx);
//            float angle = atan2(posB.y, posB.x) - atan2(posA.y, posA.x);
//            angle = angle * 180 / M_PI;
             angle = CC_RADIANS_TO_DEGREES(angle);
            road->setRotation(-angle);
            
            gameLayer->monsterLayer->addChild(road);
            
        }
        
        solarSystem->updateInterface();
    }
}

void GameManager::updateNodes()
{
    //update stuff on fields
    for(int i = 0; i < solarSystemArray->count(); i++){
        SolarSystemObject *solarSystem = (SolarSystemObject*)solarSystemArray->objectAtIndex(i);
        solarSystem->update();
    }
}

#pragma mark - market stuff
/*
void GameManager::organizeMarket(){


    
}

void GameManager::sellCard(CardSprite* card){
    //give player money
    GM->player->changeSoul(card->soulCost);
    player->spendAction(Neutral);
    
    //remove card from deck and hand
    player->removeCard(card);
}

void GameManager::addMarketCard(CardSprite* marketCard){
    // this->marketCardArray->addObject(marketCard);
    //  this->gameLayer->marketLayer->addChild(marketCard);
    
    //    this->organizeMarket();
    marketCard->turnsLeftInMarket = 2;
    marketCard->setScale(DEFAULT_CARD_SCALE);
    this->gameLayer->monsterLayer->addChild(marketCard);
    
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
            GM->player->changeSoul(-marketCard->soulCost);
            player->spendAction(Neutral);
            marketCard->turnsLeftInMarket = 0;
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
 */


#pragma mark - utility functions



