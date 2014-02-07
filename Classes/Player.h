//
//  Player.h
//  RogueDeck
//
//  Created by Hunter Francis on 11/21/13.
//
//

#ifndef __RogueDeck__Player__
#define __RogueDeck__Player__

#include "cocos2d.h"
#include "GameLayer.h"
#include "CardSprite.h"
#include "Action.h"

USING_NS_CC;

class Player
{
    
public:
    Player();
    
    //player variables
    int health;
    int maxHealth;
    int soul;
    int maxSoul;
    CCArray *actionsLeftArray;
    
    
    //deck variables
    CCArray *deckCards;
    
    CCSprite *currentPlayCard;
    CCArray *playedCards;
    CCArray *libraryCards;
    CCArray *discardCards;
    CCArray *handCards;
    
    void reset();
    
    //action manipulation
    void addAction(ActionType actionType);
    void spendAction(ActionType actionType);
    void clearActions();
    bool hasAction(ActionType actionType);
    
    //card manipulation
    void organizeHand();
    void organizePlayedCards();
    void removeCard(CardSprite *card);
    void acquireCard(CardSprite *card);
    void addCardToHand();
    void playCard(CardSprite *card);
    void finishedPlayingCard();
    void discardCard(CardSprite* card);
    void discardPlayedCards();
    void discardHand();
    void drawHand();
    void reshuffleLibrary();
    void shuffle(CCArray *array);
    
    void changeSoul(int soulOffset);
};
#endif /* defined(__RogueDeck__Player__) */
