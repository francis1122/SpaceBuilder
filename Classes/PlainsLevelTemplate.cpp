//
//  PlainsLevelTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/15/14.
//
//

#include "PlainsLevelTemplate.h"


#include "MonsterTemplates.h"
#include "Constants.h"
#include "MonsterGenerator.h"
#include "IRDS.h"

bool PlainsLevelTemplate::init(int _levelNumber){
    LevelTemplate::init(_levelNumber);
    monstersLeft = 15;
    levelName = new CCString();
    levelName->initWithFormat("Plains");
    levelDescription = new CCString();
    levelDescription->initWithFormat("Lots of creepy monsters that have that are oozy.");
    return true;
}

MonsterSprite* PlainsLevelTemplate::spawnMonster(){
    
    //setup card drop table for cards to be chosen
    IRDSTable *templateDrops = new IRDSTable();
    templateDrops->rdsContents->addObject(new IRDSMonsterTemplate(WeakMinionTemplate::CLASS_NAME, 3.0, 0));
    templateDrops->rdsContents->addObject(new IRDSMonsterTemplate(RushMinionTemplate::CLASS_NAME, 8.0, 0));
    templateDrops->rdsContents->addObject(new IRDSMonsterTemplate(OozeTemplate::CLASS_NAME, 4.0, 0));
    
    //randomly choose a template
    IRDSMonsterTemplate *colorChosen = (IRDSMonsterTemplate*)templateDrops->rdsResult(powerLevel);
    // use chosen template to create card
    MonsterSprite *newMonster;
    MonsterTemplate *monsterTemplate = MG->createClass(colorChosen->className);
    monsterTemplate->init(powerLevel);
    newMonster = monsterTemplate->createMonster();
    
    return newMonster;
    
}

MonsterSprite *PlainsLevelTemplate::spawnBossMonster(){
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