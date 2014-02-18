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
        CG->registerClass(WashTemplate::CLASS_NAME, &WashTemplate::create);
        CG->registerClass(SellCardTemplate::CLASS_NAME, &SellCardTemplate::create);
        CG->registerClass(InstantMonsterTemplate::CLASS_NAME, &InstantMonsterTemplate::create);
        CG->registerClass(PreemptiveDamageTemplate::CLASS_NAME, &PreemptiveDamageTemplate::create);
        CG->registerClass(BasicDamageTemplate::CLASS_NAME, &BasicDamageTemplate::create);
        
        
        
    }
    
    //Return the singleton object
    return m_mySingleton;
}


CardSprite* CardGenerator::createCard(float powerLevel){
    //choose color
    return chooseCardColor(powerLevel);
}

CardSprite* CardGenerator::chooseCardColor(float powerLevel)
{
    
    IRDSTable *colorDrops = new IRDSTable();
    colorDrops->rdsContents->addObject(new IRDSColor(Red, 10.0));
    colorDrops->rdsContents->addObject(new IRDSColor(Yellow, 10.0));
    colorDrops->rdsContents->addObject(new IRDSColor(Green, 10.0));
    colorDrops->rdsContents->addObject(new IRDSColor(Blue, 10.0));

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
    }else if(colorChosen->color == Green){
        return cardForGreen(powerLevel);
    }
    
    return NULL;
}

CardSprite* CardGenerator::cardForRed(float powerLevel){

    //setup card drop table for cards to be chosen
    IRDSTable *templateDrops = new IRDSTable();
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(BasicDamageTemplate::CLASS_NAME, 7.0, 0));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(DirectDamageTemplate::CLASS_NAME, 7.0, 15));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(SellCardTemplate::CLASS_NAME, 3.0, 0));
//    templateDrops->rdsContents->addObject(new IRDSCardTemplate(DrawCardTemplate::CLASS_NAME, 3.0, 15));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(MultiTargetDirectDamageTemplate::CLASS_NAME, 5.0, 15));

    
    
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
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(BasicDamageTemplate::CLASS_NAME, 7.0, 0));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(DirectDamageTemplate::CLASS_NAME, 7.0, 15));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(SellCardTemplate::CLASS_NAME, 4.0, 0));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(ActionGainTemplate::CLASS_NAME, 4.0, 15));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(SoulGainTemplate::CLASS_NAME, 6.0, 0));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(DrawDiscardTemplate::CLASS_NAME, 7.0, 15));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(InstantMonsterTemplate::CLASS_NAME, 5.0, 15));
    
    
    

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
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(BasicDamageTemplate::CLASS_NAME, 7.0, 0));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(DirectDamageTemplate::CLASS_NAME, 7.0, 15));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(SellCardTemplate::CLASS_NAME, 4.0, 0));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(SoulGainTemplate::CLASS_NAME, 6.0, 0));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(ActionGainTemplate::CLASS_NAME, 5.0, 15));

    templateDrops->rdsContents->addObject(new IRDSCardTemplate(RandomTargetDamageTemplate::CLASS_NAME, 5.0, 15));
//    templateDrops->rdsContents->addObject(new IRDSCardTemplate(DrawCardTemplate::CLASS_NAME, 5.0, 15));

    templateDrops->rdsContents->addObject(new IRDSCardTemplate(PreemptiveDamageTemplate::CLASS_NAME, 5.0, 15));
    
    
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


CardSprite* CardGenerator::cardForGreen(float powerLevel){
    IRDSTable *templateDrops = new IRDSTable();
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(BasicDamageTemplate::CLASS_NAME, 7.0, 0));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(DirectDamageTemplate::CLASS_NAME, 7.0, 15));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(SoulGainTemplate::CLASS_NAME, 6.0, 0));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(SellCardTemplate::CLASS_NAME, 4.0, 0));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(ActionGainTemplate::CLASS_NAME, 5.0, 15));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(PosionDamageTemplate::CLASS_NAME, 5.0, 15));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(OnDefendDirectDamageTemplate::CLASS_NAME, 5.0, 15));
//    templateDrops->rdsContents->addObject(new IRDSCardTemplate(DrawCardTemplate::CLASS_NAME, 5.0, 15));


    //randomly choose a template
    IRDSCardTemplate *colorChosen = (IRDSCardTemplate*)templateDrops->rdsResult(powerLevel);
    // use chosen template to create card
    CardSprite *newCard;
    CardTemplate *cardTemplate = createClass(colorChosen->className);
    cardTemplate->init(powerLevel, Green);
    newCard = cardTemplate->createCard();
    //set the color of the cards
    Action *action = new Action();
    action->init(Green);
    newCard->setAction(action);
    return newCard;
}


CardSprite* CardGenerator::cardForNeutral(float powerLevel){
    //setup card drop table for cards to be chosen
    IRDSTable *templateDrops = new IRDSTable();
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(DirectDamageTemplate::CLASS_NAME, 10.0, 0));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(SoulGainTemplate::CLASS_NAME, 8.0, 0));
    templateDrops->rdsContents->addObject(new IRDSCardTemplate(WashTemplate::CLASS_NAME, 7.0, 0));
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


