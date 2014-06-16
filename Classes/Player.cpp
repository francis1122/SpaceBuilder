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
#include "Constants.h"
#include "AnimationManager.h"
#include "AnimationObject.h"
#include "CardSprite.h"
#include "Targets.h"
#include "SolarSystemObject.h"

USING_NS_CC;

Player::Player()
{
    this->deckCards = new CCArray();
    this->playedCards = new CCArray();
    this->discardCards = new CCArray();
    this->handCards = new CCArray();
    this->libraryCards = new CCArray();
    this->solarSystemArray = new CCArray();
    deckCards->init();
    playedCards->init();
    discardCards->init();
    handCards->init();
    libraryCards->init();
    solarSystemArray->init();
}

void Player::setupPlayer()
{
    money = 10;
    commandPoints = 10;
    commandPointsMax = 10;

    
    currentPlayCard = NULL;
    //addCards To library
    
    //get home solar system
    //SolarSystemObject *homeSystem = (SolarSystemObject*)solarSystemArray->objectAtIndex(0);
    
    //attack cards
    for(int i = 0; i < 12; i++){
        if(i == 0){
            CardSprite *card = new CardSprite();
            card->cardImageFile = "sword";
            card->initWithSpriteFrameName("YellowCard");
            card->detailsLabel->setString("colonize card");
            //Make card ability
            SolarSystemTargets *cardTargets = new SolarSystemTargets();
            cardTargets->initWithCardSprite(card);
            cardTargets->targetNeutralSystems = true;
            ColonizeStatus *status = new ColonizeStatus();
            status->init();
            cardTargets->statuses->addObject(status);
            
            card->cardTargets = cardTargets;
            acquireCard(card);
        }else if(i < 5){
            CardSprite *card = new CardSprite();
            card->cardImageFile = "sword";
            card->initWithSpriteFrameName("YellowCard");
            card->detailsLabel->setString("increase population of solar system by 1");
            //Make card ability
            SolarSystemTargets *cardTargets = new SolarSystemTargets();
            cardTargets->initWithCardSprite(card);
            cardTargets->targetFriendlySystems = true;
            
            
            PopulationOffsetStatus *status = new PopulationOffsetStatus();
            status->initWithPopulationOffset(1, 0);
            cardTargets->statuses->addObject(status);
            
            card->cardTargets = cardTargets;
            acquireCard(card);
            
        }else if(i == 6){
            CardSprite *card = new CardSprite();
            card->cardImageFile = "sword";
            card->initWithSpriteFrameName("YellowCard");
            card->isPassive = true;
            card->detailsLabel->setString("Building: generate 50 money each turn");
            //Make card ability
            PassiveTargets *cardTargets = new PassiveTargets();
            cardTargets->initWithCardSprite(card);
            
            MoneyOffsetStatus *status = new MoneyOffsetStatus();
            status->initWithMoneyOffset(50);
            cardTargets->statuses->addObject(status);
            
            card->passiveTargets = cardTargets;
            acquireCard(card);
        }else{
            
            CardSprite *card = new CardSprite();
            card->cardImageFile = "sword";
            card->initWithSpriteFrameName("YellowCard");
            //Make card ability
            CardTargets *cardTargets = new PlayAreaTargets();
            cardTargets->initWithCardSprite(card);
            
            MoneyOffsetStatus *status = new MoneyOffsetStatus();
            status->initWithMoneyOffset(10);
            cardTargets->statuses->addObject(status);
            
            card->cardTargets = cardTargets;
            acquireCard(card);
        }
    }
    
    /*
     //soul cards
     for(int i = 0; i < 4; i++){
     CardSprite *card = new CardSprite();
     card->cardImageFile = "images";
     card->initWithSpriteFrameName("NeutralCard");
     //Make card ability
     CardTargets *cardTargets = new PlayAreaTargets();
     cardTargets->initWithCardSprite(card);
     GainSoulStatus *status = new GainSoulStatus();
     status->initWithSoulGain(2);
     cardTargets->statuses->addObject(status);
     
     card->cardTargets = cardTargets;
     card->setupSoulGainCard(2);
     libraryCards->addObject(card);
     deckCards->addObject(card);
     }
     */
    reset();
}

#pragma mark - card manipulation

void Player::reset(){
    discardHand();
    discardCards->removeAllObjects();
    playedCards->removeAllObjects();
    handCards->removeAllObjects();
    libraryCards->removeAllObjects();
    
    libraryCards->addObjectsFromArray(deckCards);
    shuffle(libraryCards);
    money = 10;
    commandPoints = commandPointsMax;
}


void Player::organizeHand(){
    CCObject *object;
    int handSize = handCards->count();
    int i = 0;
    CCLog("Hand Organize");
    float centralPoint = 550;
    float cardOffset = 110;
    float startPoint = centralPoint - (cardOffset/2)*handSize;
    AnimationObject *animationHolder = new AnimationObject();
    animationHolder->init();
    
    CCARRAY_FOREACH(handCards, object){
        CardSprite *card = (CardSprite*)object;
        card->setScale(DEFAULT_CARD_SCALE);
        //card->setPosition(CCPointMake(startPoint + i * 110, 75));
        AnimationObject *animation = new AnimationObject();
        CCMoveTo *move = CCMoveTo::create(.3, CCPointMake(startPoint + i * 110, 75));
        animation->init(move, card);
        if(!card->isZoomed){
            animationHolder->addAnimation(animation);
        }else{
            CCLog("nothing");
        }
        
        
        i++;
    }
    animationHolder->duration = .05;
    AM->addAnimation(animationHolder);
    //    organizePlayedCards();
}

void Player::organizePlayedCards(){
    CCObject *object;
    int handSize = playedCards->count();
    int i = 0;
    CCLog("PlayedCards Organize");
    float centralPoint = 700;
    float cardOffset = 110;
    float startPoint = centralPoint - (cardOffset/2)*handSize;
    AnimationObject *animationHolder = new AnimationObject();
    animationHolder->init();
    CCARRAY_FOREACH(playedCards, object){
        CardSprite *card = (CardSprite*)object;
        card->setScale(.15);
        AnimationObject *animation = new AnimationObject();
        CCMoveTo *move = CCMoveTo::create(.3, CCPointMake(startPoint + i * 70, 260));
        animation->init(move, card);
        if(!card->isZoomed){
            animationHolder->addAnimation(animation);
        }
        i++;
    }
    if(currentPlayCard != NULL){
        currentPlayCard->setScale(.3);
        currentPlayCard->setPosition(ccp(650, 250));
    }
    animationHolder->duration = .05;
    AM->addAnimation(animationHolder);
}

void Player::removeCard(CardSprite *card)
{
    card->removeFromParent();
    deckCards->removeObject(card);
    handCards->removeObject(card);
    libraryCards->removeObject(card);
    playedCards->removeObject(card);
    discardCards->removeObject(card);
    
    if(card->isPassive){
        card->passiveTargets->removeAllObjects();
    }
    card->owner = NULL;
}

void Player::acquireCardInSolarSystemSpot(CardSprite *card, SolarSystemObject* solarSystem, int index)
{
    CardSprite *cardBeingReplaced = (CardSprite*)solarSystem->cardArray->objectAtIndex(index);
    removeCard(cardBeingReplaced);
    card->owner = this;
    solarSystem->cardArray->replaceObjectAtIndex(index, card, true);
    if(card->isPassive){
        card->passiveTargets->checkAllObjects();
    }
    this->deckCards->addObject(card);
    this->discardCards->addObject(card);
}

void Player::acquireCard(CardSprite *card)
{
    card->owner = this;
    if(card->isPassive){
        card->passiveTargets->checkAllObjects();
    }
    this->deckCards->addObject(card);
    this->discardCards->addObject(card);
}

void Player::addCardToHand()
{
    if(libraryCards->count() > 0){
        CCObject *object = libraryCards->lastObject();
        CardSprite *card = (CardSprite*)object;
        card->setScale(DEFAULT_CARD_SCALE);
        AnimationObject *animation = new AnimationObject();
        CCCallFunc *obj = CCCallFunc::create(card, callfunc_selector(CardSprite::addCard));
        animation->initWithNode(obj, GM->gameLayer);
        animation->duration = .001;
        AM->addAnimation(animation);
        handCards->addObject(card);
        libraryCards->removeLastObject();
    }else{
        if(discardCards->count() > 0){
            reshuffleLibrary();
            addCardToHand();
        }else{
            // no cards to draw
            CCLog("No Cards To Draw");
        }
    }
}

bool Player::canPlayCard(CardSprite *card)
{
    if(commandPoints < card->commandPointsToPlay){
        return false;
    }
    if(money < card->costToPlay){
        return false;
    }
    return true;
}

void Player::playCard(CardSprite *card){
    //execute card
    card->setScale(.15);
    commandPoints -= card->commandPointsToPlay;
    currentPlayCard = card;
    handCards->removeObject(card);
    GM->player->organizeHand();
    GM->player->organizePlayedCards();
}

void Player::finishedPlayingCard(){
    if(currentPlayCard != NULL){
        //check if card should either go to discard, or do anything else
        playedCards->addObject(currentPlayCard);
        currentPlayCard = NULL;
        GM->player->organizeHand();
        GM->player->organizePlayedCards();
    }
}

void Player::discardCard(CardSprite* card)
{
    discardCards->addObject(card);
    card->removeFromParent();
    handCards->removeObject(card);
}

void Player::discardPlayedCards()
{
    CCObject *object;
    CCARRAY_FOREACH(playedCards, object){
        
        CardSprite *card = (CardSprite*)object;
        card->removeFromParent();
        card->disableInteractive();
        discardCards->addObject(object);
    }
    playedCards->removeAllObjects();
}

void Player::discardHand()
{
    CCObject *object;
    AnimationObject *holderAnimation = new AnimationObject();
    holderAnimation->init();
    CCARRAY_FOREACH(handCards, object){
        AnimationObject *animation = new AnimationObject();
        CardSprite *card = (CardSprite*)object;
        card->disableInteractive();
        discardCards->addObject(object);
        CCMoveTo *move = CCMoveTo::create(.4, ccp(900, 10));
        CCCallFunc *obj = CCCallFunc::create(card, callfunc_selector(CardSprite::removeCard));
        CCSequence *seq = CCSequence::createWithTwoActions(move, obj);
        animation->init(seq, card);
        holderAnimation->addAnimation(animation);
    }
    holderAnimation->duration = .4;
    AM->addAnimation(holderAnimation);
    handCards->removeAllObjects();
}

void Player::drawHand()
{
    for(int i = 0; i < 5; i++){
        addCardToHand();
    }
}

void Player::reshuffleLibrary()
{
    libraryCards->addObjectsFromArray(discardCards);
    shuffle(libraryCards);
    discardCards->removeAllObjects();
}

void Player::shuffle(CCArray *array)
{
    int count = array->count();
    for (int i = 0; i < count; ++i) {
        // Select a random element between i and end of array to swap with.
        int nElements = count - i;
        int n = arc4random_uniform(nElements) + i;
        array->exchangeObjectAtIndex(i, n);
    }
}

void Player::loseSolarSystem(SolarSystemObject *solarSystem)
{
    solarSystem->owner = NULL;
    for(int i = 0; i < solarSystem->cardArray->count(); i++){
        CardSprite *card = (CardSprite*)solarSystem->cardArray->objectAtIndex(i);
        this->removeCard(card);
    }
}

void Player::acquireSolarSystem(SolarSystemObject *solarSystem)
{
    //clean up previous solar system owner
    if(solarSystem->owner){
        solarSystem->owner->loseSolarSystem(solarSystem);
    }
    //acquire
    solarSystem->owner = this;
    for(int i = 0; i < solarSystem->cardArray->count(); i++){
        CardSprite *card = (CardSprite*)solarSystem->cardArray->objectAtIndex(i);
        this->acquireCard(card);
    }
}



void Player::changeMoney(int moneyOffset)
{
    if(moneyOffset > 0){
//        AM->createSoulIcon(moneyOffset, ccp(545,260));
    }
    this->money += moneyOffset;
}

void Player::changeCommandPoints(int commandPointsOffset)
{
    Player::changeCommandPoints(commandPointsOffset, ccp(470, 300));
}

void Player::changeCommandPoints(int commandPointsOffset, CCPoint point)
{
    commandPoints -= commandPointsOffset;
    GM->gameLayer->updateInterface();
    GM->gameStateCheck();
}










