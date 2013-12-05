//
//  MonsterGenerator.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/26/13.
//
//

#include "MonsterGenerator.h"
#include "MonsterSprite.h"

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


MonsterSprite* MonsterGenerator::createMonster(int powerLevel){
    MonsterSprite *monster = MonsterSprite::create();
    monster->life = powerLevel * 2;
    monster->attack = powerLevel;
    return monster;
}

