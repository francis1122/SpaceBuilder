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

MonsterGenerator* MonsterGenerator::sharedMonsterGeneratorManager()
{
    //If the singleton has no instance yet, create one
    if(NULL == m_mySingleton)
    {
        //Create an instance to the singleton
        m_mySingleton = new MonsterGenerator();
        
        MonsterGenerator *MG = MonsterGenerator::sharedMonsterGeneratorManager();
        MG->registerClass(WeakMinionTemplate::CLASS_NAME, &WeakMinionTemplate::create);
        MG->registerClass(RushMinionTemplate::CLASS_NAME, &RushMinionTemplate::create);
        MG->registerClass(BloodGiantTemplate::CLASS_NAME, &BloodGiantTemplate::create);
        MG->registerClass(OozeTemplate::CLASS_NAME, &OozeTemplate::create);
        MG->registerClass(ArcherTemplate::CLASS_NAME, &ArcherTemplate::create);
        MG->registerClass(DragonBossTemplate::CLASS_NAME, &DragonBossTemplate::create);
        MG->registerClass(DemonTemplate::CLASS_NAME, &DemonTemplate::create);
        MG->registerClass(DemonMinionTemplate::CLASS_NAME, &DemonMinionTemplate::create);
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

