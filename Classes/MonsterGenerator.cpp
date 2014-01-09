//
//  MonsterGenerator.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/26/13.
//
//

#include "MonsterGenerator.h"
#include "MonsterSprite.h"
#include "Statuses.h"
#include "Action.h"
#include "LLMath.h"

using namespace cocos2d;

//All static variables need to be defined in the .cpp file
//I've added this following line to fix the problem
MonsterGenerator* MonsterGenerator::m_mySingleton = NULL;

MonsterGenerator::MonsterGenerator()
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

MonsterGenerator* MonsterGenerator::sharedGameManager()
{
    //If the singleton has no instance yet, create one
    if(NULL == m_mySingleton)
    {
        //Create an instance to the singleton
        m_mySingleton = new MonsterGenerator();
    }
    
    //Return the singleton object
    return m_mySingleton;
}


MonsterSprite* MonsterGenerator::createMonster(float powerLevel){
    MonsterSprite *monster = MonsterSprite::create();
    monster->life = powerLevel/6 + LLMath::getIntValue(0,powerLevel/3);
    monster->attack = powerLevel/5 + LLMath::getIntValue(0,powerLevel/4);
    monster->location = 2 + arc4random()%3;
    monster->monsterLevel = (int)powerLevel;
    
    //add monster rewards
    int rand = arc4random()%5;
    if(rand == 0){
        GainSoulStatus *status = new GainSoulStatus();
        status->initWithSoulGain(powerLevel/2);
        CCString *newString = CCString::createWithFormat("Gain %i Soul", status->soulGainAmount);
        monster->detailsLabel->setString(newString->getCString());
        monster->afterDeathEffectArray->addObject(status);
    }else if(rand ==1){
        GainActionStatus *status = new GainActionStatus();
        CCArray *actions = new CCArray();
        actions->init();
        Action *action = new Action();
        action->init(Neutral);
        actions->addObject(action);
        status->initWithActionGain(actions);
        
        
        monster->afterDeathEffectArray->addObject(status);
        monster->detailsLabel->setString("Gain an Action");
    }
    
    return monster;
}

