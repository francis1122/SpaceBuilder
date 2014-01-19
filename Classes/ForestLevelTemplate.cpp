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



MonsterSprite* ForestLevelTemplate::spawnMonster(){
    
    //setup card drop table for cards to be chosen
    IRDSTable *templateDrops = new IRDSTable();
    templateDrops->rdsContents->addObject(new IRDSMonsterTemplate(WeakMinionTemplate::CLASS_NAME, 5.0, 0));
    templateDrops->rdsContents->addObject(new IRDSMonsterTemplate(ArcherTemplate::CLASS_NAME, 4.0, 0));
    templateDrops->rdsContents->addObject(new IRDSMonsterTemplate(BloodGiantTemplate::CLASS_NAME, 8.0, 0));
    
    //randomly choose a template
    IRDSMonsterTemplate *colorChosen = (IRDSMonsterTemplate*)templateDrops->rdsResult(powerLevel);
    // use chosen template to create card
    MonsterSprite *newMonster;
    MonsterTemplate *monsterTemplate = MG->createClass(colorChosen->className);
    monsterTemplate->init(powerLevel);
    newMonster = monsterTemplate->createMonster();
    
    return newMonster;
    
}