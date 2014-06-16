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
class SolarSystemObject;
class Player
{
    
public:
    Player();
    void setupPlayer();
    
    //player variables
    int money;
    int commandPoints;
    int commandPointsMax;
    CCArray *actionsLeftArray;
    
    CCArray *solarSystemArray;
    //deckCards array is all cards the player owns
    CCArray *deckCards;
    
    CardSprite *currentPlayCard;
    //playedCards are cards that have been played this turn
    CCArray *playedCards;
    //library are the cards that get drawn into the hand
    CCArray *libraryCards;
    CCArray *discardCards;
    CCArray *handCards;
    
    void reset();
    
    //card manipulation
    void organizeHand();
    void organizePlayedCards();
    void removeCard(CardSprite *card);
    
    //adds card to specific solar system player controls, used for replacing cards
    void acquireCardInSolarSystemSpot(CardSprite *card, SolarSystemObject* solarSystem, int index);
    
    //adds card to deck
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
    
    void loseSolarSystem(SolarSystemObject *solarSystem);
    void acquireSolarSystem(SolarSystemObject *solarSystem);
    
    void changeMoney(int moneyOffset);
    void changeCommandPoints(int commandPointsOffset);
    void changeCommandPoints(int commandPointsOffset, CCPoint point);
};
#endif /* defined(__RogueDeck__Player__) */
