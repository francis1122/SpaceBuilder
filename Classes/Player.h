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
class CardSprite;
class Player
{
    
public:
    Player();
    
    //player variables
    int money;
    int commandPoints;
    int commandPointsMax;
    CCArray *actionsLeftArray;
    
    CCArray *solarSystemArray;
    //deck variables
    CCArray *deckCards;
    
    CardSprite *currentPlayCard;
    CCArray *playedCards;
    CCArray *libraryCards;
    CCArray *discardCards;
    CCArray *handCards;
    
    void reset();
    
    //card manipulation
    void organizeHand();
    void organizePlayedCards();
    void removeCard(CardSprite *card);
    void acquireCard(CardSprite *card);
    void addCardToHand();
    bool canPlayCard(CardSprite *card);
    void playCard(CardSprite *card);
    void finishedPlayingCard();
    void discardCard(CardSprite* card);
    void discardPlayedCards();
    void discardHand();
    void drawHand();
    void reshuffleLibrary();
    void shuffle(CCArray *array);
    
    void changeMoney(int moneyOffset);
    void changeCommandPoints(int commandPointsOffset);
    void changeCommandPoints(int commandPointsOffset, CCPoint point);
};
#endif /* defined(__RogueDeck__Player__) */
