//
//  Player.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/21/13.
//
//

#include "Player.h"
#include "GameManager.h"
#include "GameLayer.h"
#include "HandLayer.h"
#include "Statuses.h"
#include "CardTargets.h"


USING_NS_CC;

Player::Player()
{
    health = 10;
    soul = 0;
    actionsLeft = 2;
    
    this->deckCards = new CCArray();
    this->playedCards = new CCArray();
    this->discardCards = new CCArray();
    this->handCards = new CCArray();
    this->libraryCards = new CCArray();
    deckCards->init();
    playedCards->init();
    discardCards->init();
    handCards->init();
    libraryCards->init();
    /*
    libraryCards->retain();
    handCards->retain();
    playedCards->retain();
    discardCards->retain();
    deckCards->retain();
    */
    //addCards To library
    
    //attack cards
    for(int i = 0; i < 6; i++){
        CardSprite *card = new CardSprite();
        card->cardImageFile = "sword";
        card->init();
        //Make card ability
        CardTargets *cardTargets = new CardTargets();
        cardTargets->init();
        card->detailsLabel->setString("do damage to monster");
        cardTargets->targetingType = Monsters;
        cardTargets->isTargetRequired = true;
        MonsterHealthOffsetStatus *status = new MonsterHealthOffsetStatus();
        status->init(2);
        cardTargets->statuses->addObject(status);
        
        card->cardTargets = cardTargets;
        
        libraryCards->addObject(card);
        deckCards->addObject(card);
    }
    
    //soul cards
    for(int i = 0; i < 4; i++){
        CardSprite *card = new CardSprite();
        card->cardImageFile = "images";
        card->init();
        card->detailsLabel->setString("gain soul");
        //Make card ability
        CardTargets *cardTargets = new CardTargets();
        cardTargets->init();
        cardTargets->isTargetRequired = false;
        GainSoulStatus *status = new GainSoulStatus();
        status->init(2);
        cardTargets->statuses->addObject(status);
        
        card->cardTargets = cardTargets;
        
        libraryCards->addObject(card);
        deckCards->addObject(card);
    }
}


#pragma mark - card manipulation functions

void Player::reset(){
    discardHand();
    discardCards->removeAllObjects();
    playedCards->removeAllObjects();
    handCards->removeAllObjects();
    libraryCards->removeAllObjects();
    
    libraryCards->addObjectsFromArray(deckCards);
    shuffle(libraryCards);
    health = deckCards->count();
    soul = 0;
    actionsLeft = 2;
}


void Player::organizeHand(){
    CCObject *object;
    int i = 0;
    CCARRAY_FOREACH(handCards, object){
        i++;
        CardSprite *card = (CardSprite*)object;
        card->setPosition(CCPointMake(150 + i * 150, 100));
    }
    organizePlayedCards();
}

void Player::organizePlayedCards(){
    CCObject *object;
    int i = 0;
    CCARRAY_FOREACH(playedCards, object){
        i++;
        CardSprite *card = (CardSprite*)object;
        card->setPosition(CCPointMake(150 + i * 150, 250));
    }
}


void Player::removeCard(CardSprite *card){
    card->removeFromParent();
    deckCards->removeObject(card);
    handCards->removeObject(card);
}

void Player::acquireCard(CardSprite *card){
    card->turnsLeftInMarket = 0;
    this->deckCards->addObject(card);
    this->discardCards->addObject(card);
}

void Player::addCardToHand(){
    GameManager *GM = GameManager::sharedGameManager();
    if(libraryCards->count() > 0){
        CCObject *object = libraryCards->lastObject();
        CCSprite *card = (CCSprite*)object;
        GM->gameLayer->addChild(card);
        handCards->addObject(card);
        libraryCards->removeLastObject();
    }
    
    organizeHand();
}

void Player::playCard(CardSprite *card){
    //execute card
    actionsLeft--;
    playedCards->addObject(card);
    handCards->removeObject(card);
}

void Player::discardCard(CardSprite* card){
    //todo: need to make a played cards array and hook it into the system
    discardCards->addObject(card);
    card->removeFromParent();
    handCards->removeObject(card);
}

void Player::discardPlayedCards(){
    CCObject *object;
    CCARRAY_FOREACH(playedCards, object){
        
        CardSprite *card = (CardSprite*)object;
        card->removeFromParent();
        
        discardCards->addObject(object);
    }
    playedCards->removeAllObjects();
}

void Player::discardHand(){
    CCObject *object;
    CCARRAY_FOREACH(handCards, object){
        
        CardSprite *card = (CardSprite*)object;
        card->removeFromParent();
        
        discardCards->addObject(object);
    }
    handCards->removeAllObjects();
}

void Player::drawHand(){
    for(int i = 0; i < 5; i++){
        if(libraryCards->count() > 0){
            addCardToHand();
        }else{
            if(discardCards->count() > 0){
                reshuffleLibrary();
                addCardToHand();
            }else{
                //no cards to draw, sorry
            }
        }
    }
    this->organizeHand();
}

void Player::reshuffleLibrary(){
    libraryCards->addObjectsFromArray(discardCards);
    shuffle(libraryCards);
    discardCards->removeAllObjects();
}

void Player::   shuffle(CCArray *array)
{
    int count = array->count();
    for (int i = 0; i < count; ++i) {
        // Select a random element between i and end of array to swap with.
        int nElements = count - i;
        int n = arc4random_uniform(nElements) + i;
        array->exchangeObjectAtIndex(i, n);
    }
}