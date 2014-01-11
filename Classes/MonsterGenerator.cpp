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
#include "MonsterTemplates.h"
#include "IRDSTable.h"
#include "IRDSMonsterTemplate.h"
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

MonsterTemplate* temp(){
    return NULL;
}

MonsterGenerator* MonsterGenerator::sharedGameManager()
{
    //If the singleton has no instance yet, create one
    if(NULL == m_mySingleton)
    {
        //Create an instance to the singleton
        m_mySingleton = new MonsterGenerator();
        
        MonsterGenerator *MG = MonsterGenerator::sharedGameManager();
        MG->registerClass(WeakMinionTemplate::CLASS_NAME, &WeakMinionTemplate::create);
        
    }
    
    

    
    //Return the singleton object
    return m_mySingleton;
}


void MonsterGenerator::registerClass(const std::string& pFunction, createMonsterFunc function){
    MonsterGenerator::map.insert(std::make_pair(pFunction, function));
}

MonsterTemplate* MonsterGenerator::createClass(const std::string& pFunction){
    scriptMonster_map::const_iterator iter = MonsterGenerator::map.find(pFunction);
    if (iter == MonsterGenerator::map.end())
    {
        // not found
    }
    //should call the class
    MonsterTemplate *monsterTemplate = (*iter).second();
    return monsterTemplate;
}



MonsterSprite* MonsterGenerator::createMonster(float powerLevel){
    //setup card drop table for cards to be chosen
    IRDSTable *templateDrops = new IRDSTable();
    templateDrops->rdsContents->addObject(new IRDSMonsterTemplate(WeakMinionTemplate::CLASS_NAME, 0.0, 0));
    
    //randomly choose a template
    IRDSMonsterTemplate *colorChosen = (IRDSMonsterTemplate*)templateDrops->rdsResult(powerLevel);
    // use chosen template to create card
    MonsterSprite *newMonster;
    MonsterTemplate *monsterTemplate = createClass(colorChosen->className);
    monsterTemplate->init(powerLevel);
    newMonster = monsterTemplate->createMonster();

    return newMonster;
}

MonsterSprite* MonsterGenerator::createBossMonster(float powerLevel){
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
    }
    
    return monster;
}

