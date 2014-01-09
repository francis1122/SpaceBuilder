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
#include "Action.h"
#include "Constants.h"
#include "AnimationManager.h"
#include "AnimationObject.h"
#include "CardSprite.h"


USING_NS_CC;

Player::Player()
{
    health = 10;
    maxHealth = 10;
    soul = 0;
    maxSoul = 10;
    this->actionsLeftArray = new CCArray();
    this->actionsLeftArray->init();
    
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
//        card->detailsLabel->setString("do damage to monster");
        cardTargets->targetingType = Monsters;
        MonsterHealthOffsetStatus *status = new MonsterHealthOffsetStatus();
        status->init(2);
        cardTargets->statuses->addObject(status);
        
        card->cardTargets = cardTargets;
        card->setupDamageCard(2);
        libraryCards->addObject(card);
        deckCards->addObject(card);
    }
    
    //soul cards
    for(int i = 0; i < 4; i++){
        CardSprite *card = new CardSprite();
        card->cardImageFile = "images";
        card->init();
//        card->detailsLabel->setString("gain soul");
        //Make card ability
        CardTargets *cardTargets = new CardTargets();
        cardTargets->init();
        GainSoulStatus *status = new GainSoulStatus();
        status->initWithSoulGain(2);
        cardTargets->statuses->addObject(status);
        
        card->cardTargets = cardTargets;
        card->setupSoulGainCard(2);
        libraryCards->addObject(card);
        deckCards->addObject(card);
    }
    reset();
}

#pragma mark - action manipulation

void Player::addAction(ActionType actionType){
    Action *action = new Action();
    action->init(actionType);
    action->autorelease();
    this->actionsLeftArray->addObject(action);
}

void Player::spendAction(ActionType actionType){
    //check for specific match first
    CCObject *object;
    CCARRAY_FOREACH( actionsLeftArray, object){
        Action *action = (Action*)object;
        if(actionType ==  action->actionType || actionType == Neutral){
            actionsLeftArray->removeObject(object);
            return;
        }
    }
    
    //check for neutral match
    CCARRAY_FOREACH( actionsLeftArray, object){
        Action *action = (Action*)object;
        if(action->actionType == Neutral){
            actionsLeftArray->removeObject(object);
            return;
        }
    }
    
}

void Player::clearActions(){
    actionsLeftArray->removeAllObjects();
}

bool Player::hasAction(ActionType actionType){
    CCObject *object;
    CCARRAY_FOREACH( actionsLeftArray, object){
        Action *action = (Action*)object;
        if(actionType ==  action->actionType || action->actionType == Neutral){
            return true;
        }
    }
    return false;
}

#pragma mark - card manipulation

void Player::reset(){
    clearActions();
    discardHand();
    discardCards->removeAllObjects();
    playedCards->removeAllObjects();
    handCards->removeAllObjects();
    libraryCards->removeAllObjects();
    
    libraryCards->addObjectsFromArray(deckCards);
    shuffle(libraryCards);
    health = deckCards->count();
    soul = 0;
    addAction(Neutral);
    addAction(Neutral);
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
        //card->setPosition(CCPointMake(startPoint + i * 110, 75));
        
        AnimationObject *animation = new AnimationObject();
        CCMoveTo *move = CCMoveTo::create(.3, CCPointMake(startPoint + i * 110, 75));
        animation->init(move, card);
        
        animationHolder->addAnimation(animation);
        
        
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
//        card->setPosition(CCPointMake(startPoint + i * 110, 260));
        AnimationObject *animation = new AnimationObject();
        CCMoveTo *move = CCMoveTo::create(.3, CCPointMake(startPoint + i * 110, 260));
        animation->init(move, card);
        
        animationHolder->addAnimation(animation);
        
        i++;
    }
    animationHolder->duration = .05;
    AM->addAnimation(animationHolder);
}


void Player::removeCard(CardSprite *card){
    card->removeFromParent();
    deckCards->removeObject(card);
    handCards->removeObject(card);
    this->maxHealth--;
    this->maxSoul--;
}

void Player::acquireCard(CardSprite *card){
    card->turnsLeftInMarket = 0;
    this->deckCards->addObject(card);
    this->discardCards->addObject(card);
    this->maxHealth++;
    this->maxSoul++;
}

void Player::addCardToHand(){
    
    if(libraryCards->count() > 0){
        CCObject *object = libraryCards->lastObject();
        CardSprite *card = (CardSprite*)object;
        card->setScale(.25);
    
//        GM->gameLayer->addChild(card, 10000);
//        card->setVisible(false);
        
        AnimationObject *animation = new AnimationObject();

        CCCallFunc *obj = CCCallFunc::create(card, callfunc_selector(CardSprite::addCard));
        animation->init(obj, AM);
        animation->duration = .03;
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

void Player::playCard(CardSprite *card){
    //execute card
    spendAction(card->action->actionType);
    card->setScale(.15);
    card->cardTargets->useInitialAbility();
    playedCards->addObject(card);
    handCards->removeObject(card);
    GM->player->organizeHand();
    GM->player->organizePlayedCards();
}

void Player::discardCard(CardSprite* card){
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
        AnimationObject *holderAnimation = new AnimationObject();
    holderAnimation->init();
    CCARRAY_FOREACH(handCards, object){
        AnimationObject *animation = new AnimationObject();
        CardSprite *card = (CardSprite*)object;
        
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

void Player::drawHand(){
    for(int i = 0; i < 5; i++){
        addCardToHand();
    }
}

void Player::reshuffleLibrary(){
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