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

USING_NS_CC;

Player::Player()
{
    money = 10;
    commandPoints = 10;
    commandPointsMax = 10;
    this->actionsLeftArray = new CCArray();
    this->actionsLeftArray->init();
    
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
    
    currentPlayCard = NULL;
    //addCards To library
    
    //attack cards
    for(int i = 0; i < 12; i++){
        CardSprite *card = new CardSprite();
        card->cardImageFile = "sword";
        card->initWithSpriteFrameName("NeutralCard");
        //Make card ability
        CardTargets *cardTargets = new PlayAreaTargets();
        cardTargets->initWithCardSprite(card);

        /*cardTargets->targetingType = Monsters;
        MonsterHealthOffsetStatus *status = new MonsterHealthOffsetStatus();
        status->initWithHealthOffset(-2);
        cardTargets->statuses->addObject(status);
        */
        card->cardTargets = cardTargets;
        libraryCards->addObject(card);
        deckCards->addObject(card);
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
    float centralPoint = 700;
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
}

void Player::acquireCard(CardSprite *card)
{
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
        //check if card should either go to discard, or be destroyed, or do anything else
        if(currentPlayCard->cardTargets->shouldCardBeDestroyed()){
            currentPlayCard->removeFromParent();
            currentPlayCard = NULL;
            GM->player->organizeHand();
            GM->player->organizePlayedCards();
        }else{
            playedCards->addObject(currentPlayCard);
            currentPlayCard = NULL;
            GM->player->organizeHand();
            GM->player->organizePlayedCards();
        }
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
        CCMoveTo *move = CCMoveTo::create(.4, GM->gameLayer->handLayer->discardCardSprite->getPosition());
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

void changeCommandPoints(int commandPointsOffset);
void changeCommandPoints(int commandPointsOffset, CCPoint point);

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










