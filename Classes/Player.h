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

USING_NS_CC;

class Player
{
    
public:
    Player();
    
    //player variables
    int health;
    int soul;
    int actionsLeft;
    
    
    //deck variables
    CCArray *deckCards;
    
    CCArray *playedCards;
    CCArray *libraryCards;
    CCArray *discardCards;
    CCArray *handCards;
    
    void reset();
    
    //card manipulation functions
    void organizeHand();
    void organizePlayedCards();
    void removeCard(CardSprite *card);
    void acquireCard(CardSprite *card);
    void addCardToHand();
    void playCard(CardSprite *card);
    void discardCard(CardSprite* card);
    void discardPlayedCards();
    void discardHand();
    void drawHand();
    void reshuffleLibrary();
    void shuffle(CCArray *array);
};
#endif /* defined(__RogueDeck__Player__) */
