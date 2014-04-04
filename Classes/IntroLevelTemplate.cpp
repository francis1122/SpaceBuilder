//
//  IntroLevelTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/15/14.
//
//

#include "IntroLevelTemplate.h"
#include "MonsterTemplates.h"
#include "Constants.h"
#include "MonsterGenerator.h"
#include "IRDS.h"


bool IntroLevelTemplate::init(int _levelNumber){
    LevelTemplate::init(_levelNumber);
    monstersLeft = 12;
    levelName = new CCString();
    levelName->initWithFormat("Start Town");
    levelDescription = new CCString();
    levelDescription->initWithFormat("The very first battle.");
    return true;
}

MonsterSprite* IntroLevelTemplate::spawnMonster(){

    //setup card drop table for cards to be chosen
    IRDSTable *templateDrops = new IRDSTable();
    templateDrops->rdsContents->addObject(new IRDSMonsterTemplate(WeakMinionTemplate::CLASS_NAME, 0.0, 0));
    
    //randomly choose a template
    IRDSMonsterTemplate *colorChosen = (IRDSMonsterTemplate*)templateDrops->rdsResult(powerLevel);
    // use chosen template to create card
    MonsterSprite *newMonster;
    MonsterTemplate *monsterTemplate = MG->createClass(colorChosen->className);
    monsterTemplate->init(powerLevel);
    newMonster = monsterTemplate->createMonster();
    
    return newMonster;
    
}

MonsterSprite *IntroLevelTemplate::spawnBossMonster(){
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