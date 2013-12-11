//
//  CardGenerator.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/27/13.
//
//

#include "CardGenerator.h"

#include "MonsterGenerator.h"
#include "MonsterSprite.h"
#include "CardSprite.h"
#include "Statuses.h"
#include "Player.h"
#include "CardTemplates.h"

USING_NS_CC;

//All static variables need to be defined in the .cpp file
//I've added this following line to fix the problem
CardGenerator* CardGenerator::m_mySingleton = NULL;

CardGenerator::CardGenerator()
{
    
    
    //        Monster *card = CardSprite::create();
    //      libraryCards->addObject(card);
    //    deckCards->addObject(card);
    
    
    /*
     CCSprite *sprite1 = CCSprite::create();
     CCSprite *sprite2 = CCSprite::create();
     
     this->deckCards->addObject(sprite1);
     this->deckCards->addObject(sprite2);
     CCLog("capcity %i", this->deckCards->capacity());
     */
}

CardGenerator* CardGenerator::sharedGameManager()
{
    //If the singleton has no instance yet, create one
    if(NULL == m_mySingleton)
    {
        //Create an instance to the singleton
        m_mySingleton = new CardGenerator();
    }
    
    //Return the singleton object
    return m_mySingleton;
}


CardSprite* CardGenerator::createCard(float powerLevel){
    //what should happen
    
    //choose color
    return chooseCardColor(powerLevel);
    
    
    /*int rand = arc4random()%5;
    CardSprite *card = new CardSprite();
    
    rand = 112;
    
    if(rand == 112){
        card->cardImageFile = "sword";
        card->init();
        //Make card ability
        CardTargets *cardTargets = new CardTargets();
        cardTargets->init();
        card->detailsLabel->setString("Do Dmg\nKilling Blow");
        cardTargets->targetingType = Monsters;
        cardTargets->isTargetRequired = true;
        MonsterHealthOffsetStatus *status = new MonsterHealthOffsetStatus();
        status->init(powerLevel);
        DeathBlowStatus *deathStatus = new DeathBlowStatus();
        deathStatus->init(powerLevel);
        cardTargets->statuses->addObject(deathStatus);
        cardTargets->statuses->addObject(status);
        card->cardTargets = cardTargets;
        card->setSoulCostOfCard(powerLevel);
        return card;
    }

    
    if(rand == 111){
        card->cardImageFile = "images";
        card->init();
        //Make card ability
        CardTargets *cardTargets = new CardTargets();
        cardTargets->init();
        card->detailsLabel->setString("discard a card and gain soul equal to cards cost");
        cardTargets->isTargetRequired = false;
        cardTargets->isDraggingRequired = true;
        cardTargets->targetingType = DiscardCard;
        
        GainSoulStatus *status = new GainSoulStatus();
        status->init(powerLevel);
        cardTargets->statuses->addObject(status);
        card->cardTargets = cardTargets;
        card->setSoulCostOfCard(powerLevel);
        return card;
    }
        
    
    if(rand == 0 || rand == 1){
        card->cardImageFile = "sword";
        card->init();
        //Make card ability
        CardTargets *cardTargets = new CardTargets();
        cardTargets->init();
        card->detailsLabel->setString("do damage to monster");
        cardTargets->targetingType = Monsters;
        cardTargets->isTargetRequired = true;
        MonsterHealthOffsetStatus *status = new MonsterHealthOffsetStatus();
        status->init(powerLevel);
        cardTargets->statuses->addObject(status);
        card->cardTargets = cardTargets;
    }else if(rand == 2 || rand == 3){
        card->cardImageFile = "images";
        card->init();
        //Make card ability
        CardTargets *cardTargets = new CardTargets();
        cardTargets->init();
        card->detailsLabel->setString("gain soul");
        cardTargets->isTargetRequired = false;
        GainSoulStatus *status = new GainSoulStatus();
        status->init(powerLevel);
        cardTargets->statuses->addObject(status);
        card->cardTargets = cardTargets;
    }else{
        card->cardImageFile = "images";
        card->init();
        //Make card ability
        CardTargets *cardTargets = new CardTargets();
        cardTargets->init();
        card->detailsLabel->setString("gain two actions");
        cardTargets->isTargetRequired = false;
        GainActionStatus *status = new GainActionStatus();
        status->init(powerLevel);
        cardTargets->statuses->addObject(status);
        card->cardTargets = cardTargets;
    }
    card->setSoulCostOfCard(powerLevel);
    return card;*/
}

CardSprite* CardGenerator::chooseCardColor(float powerLevel){
    
    //choose card color
    return cardForNeutral(powerLevel);
    
}

CardSprite* CardGenerator::cardForNeutral(float powerLevel){
    //randomly choose a template for neutral
    CardSprite *newCard;
    
    //choose directDamage
    int rand = arc4random()%4;
    
    if(rand == 0){
        DirectDamageTemplate *cardTemplate = new DirectDamageTemplate();
        cardTemplate->init(powerLevel);
        newCard = cardTemplate->createCard();
    }else if(rand == 1){
        SoulGainTemplate *cardTemplate = new SoulGainTemplate();
        cardTemplate->init(powerLevel);
        newCard = cardTemplate->createCard();
    }else if(rand == 2){
        DrawCardTemplate *cardTemplate = new DrawCardTemplate();
        cardTemplate->init(powerLevel);
        newCard = cardTemplate->createCard();
    }else if(rand == 3){
        ActionGainTemplate *cardTemplate = new ActionGainTemplate();
        cardTemplate->init(powerLevel);
        newCard = cardTemplate->createCard();
    }
    return newCard;
    
}






