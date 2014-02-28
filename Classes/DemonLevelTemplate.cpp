//
//  DemonLevelTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 2/23/14.
//
//

#include "DemonLevelTemplate.h"


#include "MonsterTemplates.h"
#include "Constants.h"
#include "MonsterGenerator.h"
#include "IRDS.h"

bool DemonLevelTemplate::init(int _levelNumber){
    LevelTemplate::init(_levelNumber);
    monstersLeft = 15;
    levelName = new CCString();
    levelName->initWithFormat("Hell");
    levelDescription = new CCString();
    levelDescription->initWithFormat("Hellspawn demons hungry for human blood.");
    return true;
}

MonsterSprite* DemonLevelTemplate::spawnMonster(){
    //setup card drop table for cards to be chosen
    IRDSTable *templateDrops = new IRDSTable();
    templateDrops->rdsContents->addObject(new IRDSMonsterTemplate(DemonMinionTemplate::CLASS_NAME, 7.0, 0));
    templateDrops->rdsContents->addObject(new IRDSMonsterTemplate(DemonTemplate::CLASS_NAME, 4.0, 0));
    
    //randomly choose a template
    IRDSMonsterTemplate *colorChosen = (IRDSMonsterTemplate*)templateDrops->rdsResult(powerLevel);
    // use chosen template to create card
    MonsterSprite *newMonster;
    MonsterTemplate *monsterTemplate = MG->createClass(colorChosen->className);
    monsterTemplate->init(powerLevel);
    newMonster = monsterTemplate->createMonster();
    
    return newMonster;
}

MonsterSprite *DemonLevelTemplate::spawnBossMonster(){
    //setup card drop table for cards to be chosen
    IRDSTable *templateDrops = new IRDSTable();
    templateDrops->rdsContents->addObject(new IRDSMonsterTemplate(DragonBossTemplate::CLASS_NAME, 0.0, 0));
    
    //randomly choose a template
    IRDSMonsterTemplate *colorChosen = (IRDSMonsterTemplate*)templateDrops->rdsResult(powerLevel);
    // use chosen template to create card
    MonsterSprite *newMonster;
    MonsterTemplate *monsterTemplate = MG->createClass(colorChosen->className);
    monsterTemplate->init(powerLevel);
    newMonster = monsterTemplate->createMonster();
    
    return newMonster;
    
}