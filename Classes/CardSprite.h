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
#include "Constants.h"


typedef enum CardType{
    Utility,
    Building,
    Unit,
    Resource
} CardType;

class CardTargets;
class SolarSystemObject;
class Player;
class PassiveTargets;
class CardSprite : public BaseObject
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool initWithSpriteFrameName(const char *pszSpriteFrameName);
    
    void addCard();
    void removeCard();
    
    const char *cardImageFile;
    int costToBuy;
    
    int costToPlay;
    int productionToPlay;
    
    bool isPassive;
    
    Player *owner;
    
//    cocos2d::CCSprite *costBox;
//    cocos2d::CCSprite *playCostBox;
    cocos2d::CCSprite *cardImage;
    cocos2d::CCLabelTTF *detailsLabel;
//    cocos2d::CCLabelTTF *costLabel;
    cocos2d::CCLabelTTF *playCostLabel;
    cocos2d::CCLabelTTF *homeLabel;
    cocos2d::CCLabelTTF *cardNameLabel;
    
    cocos2d::CCSprite *glowSprite;
    
    
    // implement the "static node()" method manually
    CREATE_FUNC(CardSprite);
    
    CardTargets *cardTargets;
    PassiveTargets *passiveTargets;
    
    SolarSystemObject *homeSolarSystem;
    ResearchTypes researchType;
    
    void enableInteractive();
    void disableInteractive();
    
    void setHomeSolarSystem(SolarSystemObject* newHome);
    void setCardType(CardType newCardType);
    CardType getCardType(){ return cardType;}
    void setCardPicture(const char* pictureName);
    virtual void updateInterface();
    
    CardType cardType;
};


#endif /* defined(__RogueDeck__CardSprite__) */
