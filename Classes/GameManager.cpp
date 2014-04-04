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
#include "UIState.h"
#include "MonsterLayer.h"
#include "MarketLayer.h"
#include "AnimationManager.h"
#include "AnimationObject.h"
#include "Constants.h"
#include "LevelTemplates.h"



using namespace cocos2d;

//All static variables need to be defined in the .cpp file
//I've added this following line to fix the problem
GameManager* GameManager::m_mySingleton = NULL;

GameManager::GameManager()
{
    AM;
    currentLevelTemplate = NULL;
    this->monsterArray = new CCArray();
    this->monsterArray->init();
    this->marketCardArray = new CCArray();
    this->marketCardArray->init();
    this->locationArray = new CCArray();
    this->player = new Player();
    this->possibleLevelArray = new CCArray();
    this->possibleLevelArray->init();
    
    this->locationArray->init();
    for(int i = 0;i < 5; i++){
        CCInteger *value = CCInteger::create(1);
        locationArray->addObject(value);
    }
    
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

void GameManager::generateLevels()
{
    this->possibleLevelArray->removeAllObjects();
    for(int i = 1; i < 9; i++){
        CCArray *levelOptions = new CCArray();
        levelOptions->init();
        for(int j = 0; j < 2; j++){
            //should randomly choose levels here
            if(i == 1){
                LevelTemplate *levelTemplate = new IntroLevelTemplate();
                levelTemplate->init(i);
                levelOptions->addObject(levelTemplate);
                j++;
            }else{
                LevelTemplate *levelTemplate;
                int rand = arc4random()%3;
                rand = arc4random()%3;
                if(rand == 0){
                    levelTemplate = new PlainsLevelTemplate();
                    levelTemplate->init(i);
                }else if(rand == 1){
                    levelTemplate = new ForestLevelTemplate();
                    levelTemplate->init(i);
                }else if(rand == 2 ){
                    levelTemplate = new DemonLevelTemplate();
                    levelTemplate->init(i);
                }
                levelOptions->addObject(levelTemplate);
            }
        }
        this->possibleLevelArray->addObject(levelOptions);
    }
}


void GameManager::startNewGame(){
    delete player;
    player = NULL;
    player = new Player();
    
    //generate levels
    this->generateLevels();
    currentLevel = 1;
    CCArray *levels = (CCArray*)this->possibleLevelArray->objectAtIndex(0);
    
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCScene *pScene = GameLayer::scene();
    
    // run
    pDirector->replaceScene(pScene);
    
    this->startNewRound((LevelTemplate*)levels->objectAtIndex(0));
    

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

void GameManager::startNewRound(LevelTemplate *newLevel){
    player->reset();
    currentLevelTemplate = newLevel;
    currentLevel = newLevel->levelNumber;
    
    //used to control spawning rate of creatures, reseting values for that feature
    for(int i = 0; i < 5; i++){
        CCInteger *value = (CCInteger*)this->locationArray->objectAtIndex(i);
        value->setValue(1);
    }

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
}


#pragma mark -update the gameState from various points

void GameManager::gameStateCheck(){
    //check for dead monsters
    for(int i = monsterArray->count() - 1; i >= 0; i--){
        MonsterSprite *monster = (MonsterSprite*)monsterArray->objectAtIndex(i);
        if(monster->life <= 0 || monster->isDead){
            this->removeMonster(monster);
        }
    }
    
    //check for player death
    if(player->health <= 0){
        //TODO: make death screen to go to
        gameLayer->unscheduleUpdate();
        CCDirector* pDirector = CCDirector::sharedDirector();
        CCScene *pScene = TitleLayer::scene();
        // run
        pDirector->replaceScene(pScene);
    }
    
    //if all monsters are dead and no market cards are left
    if(currentLevelTemplate->monstersLeft <= 0 && monsterArray->count() <= 0 && marketCardArray->count()<= 0){
        //go to postRoundLayer
        gameLayer->unscheduleUpdate();
        CCDirector* pDirector = CCDirector::sharedDirector();
        CCScene *pScene = PostRoundLayer::scene();
        // run
        pDirector->replaceScene(pScene);
    }
}

void GameManager::afterCardPlayedStateCheck()
{
    //check for dead monsters
    for(int i = monsterArray->count() - 1; i >= 0; i--){
        MonsterSprite *monster = (MonsterSprite*)monsterArray->objectAtIndex(i);
        
        if(monster->life <= 0 || monster->isDead){
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
    if(currentLevelTemplate->monstersLeft <= 0 && monsterArray->count() <= 0 && marketCardArray->count()<= 0){
        //go to postRoundLayer
        CCDirector* pDirector = CCDirector::sharedDirector();
        CCScene *pScene = PostRoundLayer::scene();
        // run
        pDirector->replaceScene(pScene);
    }
}

void GameManager::setIsInteractive(bool value)
{
    isInteractive = value;
    if(value == false){
        
    }
}

void GameManager::endTurn()
{
    gameLayer->getCurrentState()->transitionToMonsterTurnState();

    player->discardHand();
    player->discardPlayedCards();
    
    //set round stuff
    //player health or soul can't be above deck count
    if(player->health > player->maxHealth){
        player->health = player->maxHealth;
    }
    if(player->soul > player->maxSoul){
        player->soul = player->maxSoul;
    }
    player->clearActions();
    player->addAction(Neutral);
    player->addAction(Neutral);
    currentTurn++;
    this->marketTurn();
    this->monsterTurn();
    
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

#pragma mark - market stuff

//market stuff
void GameManager::organizeMarketAlt(){
    CCObject *object;
    AnimationObject *cardAnimation = new AnimationObject();
    cardAnimation->init();
    CCARRAY_FOREACH(marketCardArray, object){
        CardSprite *card = (CardSprite*)object;
//        CCPoint monsterPos = ccp(170 + monster->lane * 160, 400 + monster->location * 30);
        CCPoint cardPos = ccp(180 + card->lane * 190, 400);
        CCMoveTo *action = CCMoveTo::create(.3, cardPos);
        AnimationObject *animationObject = new AnimationObject();
        animationObject->init(action, card);
        if(!card->isZoomed){
            cardAnimation->addAnimation(animationObject);
            card->setScale(DEFAULT_CARD_SCALE);
        }
    }
    cardAnimation->duration = .05;
    AM->addAnimation(cardAnimation);

    
}

void GameManager::organizeMarket(){
    organizeMarketAlt();
    /*
    int i= 0,j = 0, k = 0;
    CCLog("Market Organize");
    AnimationObject *cardAnimation = new AnimationObject();
    cardAnimation->init();
    CCObject *object;
    CCARRAY_FOREACH(marketCardArray, object){
        CardSprite *card = (CardSprite*)object;
        CCPoint cardPos;
        if(card->turnsLeftInMarket == 1){
            k++;
            cardPos = ccp(140 + k * 130, 390);
        }else if(card->turnsLeftInMarket == 2){
            k++;
            //            card->setPosition(CCPointMake(170 + j * 140, 540));
            cardPos = ccp(140 + k * 130, 465);
        }else if( card->turnsLeftInMarket== 3){
            k++;
            //            card->setPosition(CCPointMake(170 + j * 140, 540));
            cardPos = ccp(140 + k * 130, 540);
        }else if( card->turnsLeftInMarket== 0){
            CCLog("card should be removed from market and destroyed");
            cardPos = CCPoint(0,0);
        }
        CCMoveTo *action = CCMoveTo::create(.3, cardPos);
        AnimationObject *animationObject = new AnimationObject();
        animationObject->init(action, card);
        if(!card->isZoomed){
            cardAnimation->addAnimation(animationObject);
        }
        
    }
    cardAnimation->duration = .05;
    AM->addAnimation(cardAnimation);
    */
    
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
     this->marketCardArray->addObject(marketCard);
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
//            player->spendAction(Neutral);
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

#pragma mark - monster stuff
void GameManager::organizeMonsters(){
    CCObject *object;
    AnimationObject *monsterAnimation = new AnimationObject();
    monsterAnimation->init();
    CCARRAY_FOREACH(monsterArray, object){
        MonsterSprite *monster = (MonsterSprite*)object;
        CCPoint monsterPos = ccp(180 + monster->lane * 190, 400 + monster->location * 30);
        CCMoveTo *action = CCMoveTo::create(.3, monsterPos);
        AnimationObject *animationObject = new AnimationObject();
        animationObject->init(action, monster);
        if(!monster->isZoomed){
            monsterAnimation->addAnimation(animationObject);
        }
        monster->updateInterface();
    }
    monsterAnimation->duration = .05;
    AM->addAnimation(monsterAnimation);
}

void GameManager::removeMonster(MonsterSprite *monster){
    //do damage Icon
    //add card to market
    CardSprite *card;
    if(monster->isBoss){
        //maybe draw cards from a different list of cards
        card = CardGenerator::sharedGameManager()->createCard(monster->monsterLevel * 1.5);
        card->setSoulCostOfCard(0);
    }else{
        card = CardGenerator::sharedGameManager()->createCard(monster->monsterLevel);
    }
    card->setPosition(monster->getPosition());
    card->turnsLeftInMarket = 1;
    card->lane = monster->lane;
    this->addMarketCard(card);
    monster->onDeath();
    monster->removeFromParent();
    monsterArray->removeObject(monster);
}

void GameManager::spawnMonster(){

    //add value to all locations
    for(int i = 0; i < 5; i++ ){
        CCInteger *value = (CCInteger*)this->locationArray->objectAtIndex(i);
        value->setValue((value->getValue()) + 1);
    }
    //reset location value if monster exists there
    int maxMonsters = MIN(currentTurn, 5);
    for(int i = 0; i < maxMonsters; i++ ){
        CCInteger *value = (CCInteger*)this->locationArray->objectAtIndex(i);
        int isOpen = value->getValue();
        if(isOpen > 1){
            //add monster to open lane
            MonsterSprite *monster;
            monster = currentLevelTemplate->getMonster();
            //make sure a monster is returned, if monster isn't returned, then probably is the end of the level
            if(monster != NULL){
                monster->lane = i;
                this->gameLayer->monsterLayer->addChild(monster, 100);
                monster->setPosition( ccp(180 + monster->lane * 190, 1000));
                monster->updateInterface();
                this->monsterArray->addObject(monster);
                CCLog("monster added to layer");
            }
        }
    }
    
    //if a monster is in a lane, reduce lane respawn count to zero
    for(int i = 0; i < monsterArray->count(); i++){
        MonsterSprite *monster = (MonsterSprite*)monsterArray->objectAtIndex(i);
        int monsterLane = monster->lane;
        CCInteger *value = (CCInteger*)this->locationArray->objectAtIndex(monsterLane);
        value->setValue(0);
    }
    //reduce location spawn for lanes with no monsters
    for(int i = maxMonsters + 1; i < 5; i++){
        CCInteger *value = (CCInteger*)this->locationArray->objectAtIndex(i);
        value->setValue(0);
    }
    //if all monsters are dead for the level
    if(currentLevelTemplate->monstersLeft <= 0){
        for(int i = 0; i < 5; i++){
            CCInteger *value = (CCInteger*)this->locationArray->objectAtIndex(i);
            value->setValue(0);
        }
    }
}

void GameManager::addMonstersPhase(){
    //monsters allowed to spawn
    if(currentLevelTemplate->monstersLeft > 0){
        this->spawnMonster();
    }
    this->organizeMonsters();
    gameLayer->updateInterface();
}

void GameManager::monsterTurn(){
    //used to check if monster died during its update step
    this->gameStateCheck();
    
    //if there are not enough monsters on the board, add a monster
    this->addMonstersPhase();
    
    CCObject *object;
    CCARRAY_FOREACH(monsterArray, object){
        MonsterSprite *monster = (MonsterSprite*)object;
        monster->turnUpdate();
    }
    

    
    //used to check if monster died during its update step
    this->gameStateCheck();
    this->organizeMonsters();

}

#pragma mark - utility functions

bool GameManager::tauntPresent()
{
    bool tauntIsPresent = false;
    CCObject *object;
    CCARRAY_FOREACH(monsterArray, object){
        MonsterSprite *monster = (MonsterSprite*)object;
        if(monster->hasTaunt){
            tauntIsPresent = true;
        }
    }
    return tauntIsPresent;
    
}


