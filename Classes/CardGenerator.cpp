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
#include "IRDSColor.h"
#include "Action.h"
#include "IRDSTable.h"
#include "IRDSObject.h"
#include "IRDSCardTemplate.h"

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
        
        CardGenerator *CG = CardGenerator::sharedGameManager();
        CG->registerClass(DirectDamageTemplate::CLASS_NAME, &DirectDamageTemplate::create);
        CG->registerClass(SoulGainTemplate::CLASS_NAME, &SoulGainTemplate::create);
        CG->registerClass(ActionGainTemplate::CLASS_NAME, &ActionGainTemplate::create);
        CG->registerClass(DrawCardTemplate::CLASS_NAME, &DrawCardTemplate::create);
        CG->registerClass(RandomTargetDamageTemplate::CLASS_NAME, &RandomTargetDamageTemplate::create);
        CG->registerClass(MultiTargetDirectDamageTemplate::CLASS_NAME, &MultiTargetDirectDamageTemplate::create);
        CG->registerClass(DrawDiscardTemplate::CLASS_NAME, &DrawDiscardTemplate::create);
        CG->registerClass(PosionDamageTemplate::CLASS_NAME, &PosionDamageTemplate::create);
        CG->registerClass(OnDefendDirectDamageTemplate::CLASS_NAME, &OnDefendDirectDamageTemplate::create);
        
        
        
        
    }
    
    //Return the singleton object
    return m_mySingleton;
}


CardSprite* CardGenerator::createCard(float powerLevel){
    //what should happen
    
    //test
  //  CardTemplate *test = createClass("DirectDamageTemplate");
//    test->init(powerLevel);
    
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

CardSprite* CardGenerator::chooseCardColor(float powerLevel)
{
    
    IRDSTable *colorDrops = new IRDSTable();
//    colorDrops->rdsContents->addObject(new IRDSColor(Neutral, 10.0));
    colorDrops->rdsContents->addObject(new IRDSColor(Red, 10.0));
    colorDrops->rdsContents->addObject(new IRDSColor(Yellow, 10.0));
    colorDrops->rdsContents->addObject(new IRDSColor(Purple, 10.0));
    colorDrops->rdsContents->addObject(new IRDSColor(Blue, 1000.0));
    
    IRDSColor *colorChosen = (IRDSColor*)colorDrops->rdsResult(powerLevel);
    
    
    
    //choose card color
    if(colorChosen->color == Neutral){
        return cardForNeutral(powerLevel);
    }else if(colorChosen->color == Blue){
        return cardForBlue(powerLevel);
    }else if(colorChosen->color == Red){
        return cardForRed(powerLevel);
    }else if(colorChosen->color == Yellow){
        return cardForYellow(powerLevel);
    }else if(colorChosen->color == Purple){
        return cardForPurple(Purple);
    }
    
    return NULL;
}

CardSprite* CardGenerator::cardForRed(float powerLevel){

    //setup card drop table for cards to be chosen
    IRDSTable *templateDrops = new IRDSTable();
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(DirectDamageTemplate::CLASS_NAME, 14.0, 0));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(DrawCardTemplate::CLASS_NAME, 3.0, 0));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(MultiTargetDirectDamageTemplate::CLASS_NAME, 5.0, 0));
    
    //randomly choose a template
    IRDSCardTemplate *colorChosen = (IRDSCardTemplate*)templateDrops->rdsResult(powerLevel);
    // use chosen template to create card
    CardSprite *newCard;
    CardTemplate *cardTemplate = createClass(colorChosen->className);
    cardTemplate->init(powerLevel, Red);
    newCard = cardTemplate->createCard();
    //set the color of the cards
    Action *action = new Action();
    action->init(Red);
    newCard->setAction(action);
    return newCard;
    
}


CardSprite* CardGenerator::cardForBlue(float powerLevel){
    //setup card drop table for cards to be chosen
    IRDSTable *templateDrops = new IRDSTable();
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(DirectDamageTemplate::CLASS_NAME, 10.0, 0));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(ActionGainTemplate::CLASS_NAME, 7.0, 0));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(SoulGainTemplate::CLASS_NAME, 5.0, 0));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(DrawDiscardTemplate::CLASS_NAME, 500.0, 0));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(OnDefendDirectDamageTemplate::CLASS_NAME, 5.0, 0));
    
    
    

    //randomly choose a template
    IRDSCardTemplate *colorChosen = (IRDSCardTemplate*)templateDrops->rdsResult(powerLevel);
    // use chosen template to create card
    CardSprite *newCard;
    CardTemplate *cardTemplate = createClass(colorChosen->className);
    cardTemplate->init(powerLevel, Blue);
    newCard = cardTemplate->createCard();
    //set the color of the cards
    Action *action = new Action();
    action->init(Blue);
    newCard->setAction(action);
    return newCard;
    
}


CardSprite* CardGenerator::cardForYellow(float powerLevel){
    IRDSTable *templateDrops = new IRDSTable();
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(DirectDamageTemplate::CLASS_NAME, 10.0, 0));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(ActionGainTemplate::CLASS_NAME, 5.0, 0));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(SoulGainTemplate::CLASS_NAME, 5.0, 0));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(RandomTargetDamageTemplate::CLASS_NAME, 5.0, 0));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(DrawCardTemplate::CLASS_NAME, 5.0, 0));
    //randomly choose a template
    IRDSCardTemplate *colorChosen = (IRDSCardTemplate*)templateDrops->rdsResult(powerLevel);
    // use chosen template to create card
    CardSprite *newCard;
    CardTemplate *cardTemplate = createClass(colorChosen->className);
    cardTemplate->init(powerLevel, Yellow);
    newCard = cardTemplate->createCard();
    //set the color of the cards
    Action *action = new Action();
    action->init(Yellow);
    newCard->setAction(action);
    return newCard;
    
}


CardSprite* CardGenerator::cardForPurple(float powerLevel){
    IRDSTable *templateDrops = new IRDSTable();
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(DirectDamageTemplate::CLASS_NAME, 12.0, 0));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(ActionGainTemplate::CLASS_NAME, 5.0, 0));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(SoulGainTemplate::CLASS_NAME, 5.0, 0));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(PosionDamageTemplate::CLASS_NAME, 5.0, 0));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(DrawCardTemplate::CLASS_NAME, 5.0, 0));
    //randomly choose a template
    IRDSCardTemplate *colorChosen = (IRDSCardTemplate*)templateDrops->rdsResult(powerLevel);
    // use chosen template to create card
    CardSprite *newCard;
    CardTemplate *cardTemplate = createClass(colorChosen->className);
    cardTemplate->init(powerLevel, Purple);
    newCard = cardTemplate->createCard();
    //set the color of the cards
    Action *action = new Action();
    action->init(Purple);
    newCard->setAction(action);
    return newCard;
    
}


CardSprite* CardGenerator::cardForNeutral(float powerLevel){
    //setup card drop table for cards to be chosen
    IRDSTable *templateDrops = new IRDSTable();
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(DirectDamageTemplate::CLASS_NAME, 10.0, 0));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(SoulGainTemplate::CLASS_NAME, 8.0, 0));
    //randomly choose a template
    IRDSCardTemplate *colorChosen = (IRDSCardTemplate*)templateDrops->rdsResult(powerLevel);
    // use chosen template to create card
    CardSprite *newCard;
    CardTemplate *cardTemplate = createClass(colorChosen->className);
    cardTemplate->init(powerLevel, Neutral);
    newCard = cardTemplate->createCard();
    //set the color of the cards
    Action *action = new Action();
    action->init(Neutral);
    newCard->setAction(action);
    return newCard;
}



void CardGenerator::registerClass(const std::string& pFunction, createFunc function){
    CardGenerator::map.insert(std::make_pair(pFunction, function));
}

CardTemplate* CardGenerator::createClass(const std::string& pFunction){
        script_map::const_iterator iter = CardGenerator::map.find(pFunction);
        if (iter == CardGenerator::map.end())
        {
            // not found
        }
        //should call the class
        CardTemplate *cardTemplate = (*iter).second();
    return cardTemplate;
}


