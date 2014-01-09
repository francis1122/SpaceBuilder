//
//  CardSprite.h
//  RogueDeck
//
//  Created by Hunter Francis on 11/17/13.
//
//

#ifndef __RogueDeck__CardSprite__
#define __RogueDeck__CardSprite__

#include "cocos2d.h"
#include "BaseObject.h"


typedef enum CardType{
    Attack,
    Soul,
    Equipment,
    Spell
} CardType;

class CardTargets;
class Action;
class CardSprite : public BaseObject
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void addCard();
    void removeCard();
    
    const char *cardImageFile;
    int turnsLeftInMarket;
    int soulCost;
    bool isInteractive;
    Action *action;
    
    

    
    cocos2d::CCSprite *textBox;
    cocos2d::CCSprite *costBox;
    cocos2d::CCLabelTTF *detailsLabel;
    cocos2d::CCLabelTTF *costLabel;
    
    cocos2d::CCSprite *glowSprite;
    
    
    // implement the "static node()" method manually
    CREATE_FUNC(CardSprite);
    
    CardTargets *cardTargets;
    
    void enableInteractive();
    void disableInteractive();
    
    void setCardType(CardType newCardType);
    CardType getCardType(){ return cardType;}
    void setSoulCostOfCard(int newSoulCost);
    
    void setAction(Action* newAction);
#pragma mark - card creation
    void addActionGain(cocos2d::CCArray* actionArray);
    void setupDamageCard(int damage);
    
    void setupSoulGainCard(int soulGain);
    
private:
    CardType cardType;
    
};


#endif /* defined(__RogueDeck__CardSprite__) */
