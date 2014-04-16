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
#include "GameManager.h"
#include "MonsterSprite.h"

bool DemonLevelTemplate::init(int _levelNumber){
    LevelTemplate::init(_levelNumber);
    monstersLeft = 20;
    levelName = new CCString();
    levelName->initWithFormat("Hell");
    levelDescription = new CCString();
    levelDescription->initWithFormat("Hellspawn demons hungry for human blood.");
    return true;
}



MonsterSprite *DemonLevelTemplate::getMonster(){
    MonsterSprite *monster;
    //check if boss monster exists with keep spawning
    MonsterSprite *tempMonster;
    bool keepSpawning = false;
    for(int i = 0; i < GM->monsterArray->count(); i++){
        tempMonster = (MonsterSprite*)GM->monsterArray->objectAtIndex(i);
        if(tempMonster->isBoss){
            keepSpawning = true;
        }
    }
    
    if(monstersLeft <= 0 && !keepSpawning){
        return NULL;
    }
    if(monstersLeft <= 1 || keepSpawning){
        monster = spawnBossMonster();
    }else{
        monster = spawnMonster();
    }
    monstersLeft--;
    if(monstersLeft <= 0){
        monstersLeft = 0;
    }
    return monster;
}

MonsterSprite* DemonLevelTemplate::spawnMonster(){
    //setup card drop table for cards to be chosen
    IRDSTable *templateDrops = new IRDSTable();
    templateDrops->rdsContents->addObject(new IRDSMonsterTemplate(DemonMinionTemplate::CLASS_NAME, 7.0, 0));
    templateDrops->rdsContents->addObject(new IRDSMonsterTemplate(NormalMinionTemplate::CLASS_NAME, 7.0, 0));
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
    templateDrops->rdsContents->addObject(new IRDSMonsterTemplate(DemonBossTemplate::CLASS_NAME, 0.0, 0));
    
    //randomly choose a template
    IRDSMonsterTemplate *colorChosen = (IRDSMonsterTemplate*)templateDrops->rdsResult(powerLevel);
    // use chosen template to create card
    MonsterSprite *newMonster;
    MonsterTemplate *monsterTemplate = MG->createClass(colorChosen->className);
    monsterTemplate->init(powerLevel);
    newMonster = monsterTemplate->createMonster();
    
    return newMonster;
    
}