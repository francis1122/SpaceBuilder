//
//  ForestLevelTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/15/14.
//
//

#include "ForestLevelTemplate.h"
#include "MonsterTemplates.h"
#include "Constants.h"
#include "MonsterGenerator.h"
#include "IRDS.h"


bool ForestLevelTemplate::init(int _levelNumber){
    LevelTemplate::init(_levelNumber);
    monstersLeft = 12;
    levelName = new CCString();
    levelName->initWithFormat("Forest");
    levelDescription = new CCString();
    levelDescription->initWithFormat("A dark forest full of ancient evils.");
    return true;
}


MonsterSprite* ForestLevelTemplate::spawnMonster(){
    
    //setup card drop table for cards to be chosen
    IRDSTable *templateDrops = new IRDSTable();
    templateDrops->rdsContents->addObject(new IRDSMonsterTemplate(NormalMinionTemplate::CLASS_NAME, 8.0, 0));
    templateDrops->rdsContents->addObject(new IRDSMonsterTemplate(ArcherTemplate::CLASS_NAME, 3.0, 0));
    templateDrops->rdsContents->addObject(new IRDSMonsterTemplate(BloodGiantTemplate::CLASS_NAME, 1.0, 0));
    
    //randomly choose a template
    IRDSMonsterTemplate *colorChosen = (IRDSMonsterTemplate*)templateDrops->rdsResult(powerLevel);
    // use chosen template to create card
    MonsterSprite *newMonster;
    MonsterTemplate *monsterTemplate = MG->createClass(colorChosen->className);
    monsterTemplate->init(powerLevel);
    newMonster = monsterTemplate->createMonster();
    
    return newMonster;
}

MonsterSprite *ForestLevelTemplate::spawnBossMonster(){
    //setup card drop table for cards to be chosen
    IRDSTable *templateDrops = new IRDSTable();
    templateDrops->rdsContents->addObject(new IRDSMonsterTemplate(ArcherBossTemplate::CLASS_NAME, 0.0, 0));
    
    //randomly choose a template
    IRDSMonsterTemplate *colorChosen = (IRDSMonsterTemplate*)templateDrops->rdsResult(powerLevel);
    // use chosen template to create card
    MonsterSprite *newMonster;
    MonsterTemplate *monsterTemplate = MG->createClass(colorChosen->className);
    monsterTemplate->init(powerLevel);
    newMonster = monsterTemplate->createMonster();
    
    return newMonster;
    
}