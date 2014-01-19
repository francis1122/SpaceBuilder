//
//  MonsterGenerator.h
//  RogueDeck
//
//  Created by Hunter Francis on 11/26/13.
//
//

#ifndef __RogueDeck__MonsterGenerator__
#define __RogueDeck__MonsterGenerator__

#include "cocos2d.h"
#include "MonsterTemplate.h"



typedef MonsterTemplate* (*createMonsterFunc)(void); // function pointer type
typedef std::map<std::string, createMonsterFunc> scriptMonster_map;

USING_NS_CC;

class MonsterSprite;
class MonsterGenerator
{
private:
    //Constructor
    MonsterGenerator();
    
    //Instance of the singleton
    static MonsterGenerator* m_mySingleton;
    
public:
    //Get instance of singleton
    static MonsterGenerator* sharedMonsterGeneratorManager();
    
    scriptMonster_map map;
    void registerClass(const std::string& pFunction, createMonsterFunc function);
    MonsterTemplate* createClass(const std::string& pFunction);
    
    
};

#endif /* defined(__RogueDeck__MonsterGenerator__) */
