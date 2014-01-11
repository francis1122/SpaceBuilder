//
//  RandomTargetDamageTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 12/30/13.
//
//

#include "RandomTargetDamageTemplate.h"

#include "DirectDamageTemplate.h"
#include "Statuses.h"
#include "CardSprite.h"
#include "Targets.h"
#include "Action.h"
#include "CardGenerator.h"
#include "LLMath.h"


const std::string RandomTargetDamageTemplate::CLASS_NAME = "RandomTargetDamageTemplate";

void RandomTargetDamageTemplate::createCardTargets(){
    CardTargets *cardTargets = new PlayAreaTargets();
    cardTargets->init();
    createdCard->cardTargets = cardTargets;
}


#pragma mark - augmentation


void RandomTargetDamageTemplate::addNeutralAugmentationStatus(){
    
}

void RandomTargetDamageTemplate::addRedAugmentationStatus(){
  /*  int rand = arc4random()%3;
    if(rand == 0){
        //killing blow augmentation
        DeathBlowStatus *deathStatus = new DeathBlowStatus();
        //choose status
        Status *killStatus;
        GainActionStatus *status = new GainActionStatus();
        CCArray *actions = new CCArray();
        actions->init();
        Action *action = new Action();
        action->init(Red);
        actions->addObject(action);
        status->initWithActionGain(actions);
        killStatus = status;
        powerLevel -= 2;
        cardCostOffset += 2;
        augmentationDescription = CCString::createWithFormat("\nKilling Blow: Gain a Red Action");
        
        deathStatus->initWithStatus(killStatus);
        createdCard->cardTargets->statuses->addObject(deathStatus);
        
    }*/
}

void RandomTargetDamageTemplate::addBlueAugmentationStatus(){
   /* int rand = arc4random()%3;
    if(rand == 0){
        //killing blow augmentation
        DeathBlowStatus *deathStatus = new DeathBlowStatus();
        //choose status
        Status *killStatus;
        GainActionStatus *status = new GainActionStatus();
        CCArray *actions = new CCArray();
        actions->init();
        Action *action = new Action();
        action->init(Neutral);
        actions->addObject(action);
        status->initWithActionGain(actions);
        killStatus = status;
        powerLevel -= 2;
        cardCostOffset += 2;
        augmentationDescription = CCString::createWithFormat("\nKilling Blow: Gain a Neutral Action");
        deathStatus->initWithStatus(killStatus);
        createdCard->cardTargets->statuses->addObject(deathStatus);
        
    }
    */
}

void RandomTargetDamageTemplate::addYellowAugmentationStatus(){

}

void RandomTargetDamageTemplate::addPurpleAugmentationStatus(){
  //  cardPower += 6;
//    cardCostOffset -= 3;
}

#pragma mark - additional cost


void RandomTargetDamageTemplate::addNeutralAdditionalCost(){
}

void RandomTargetDamageTemplate::addRedAdditionalCost(){
}

void RandomTargetDamageTemplate::addBlueAdditionalCost(){
}

void RandomTargetDamageTemplate::addYellowAdditionalCost(){
}

void RandomTargetDamageTemplate::addPurpleAdditionalCost(){
}


#pragma mark - main status

void RandomTargetDamageTemplate::addNeutralMainStatus(){
    
    //

    
    
    int targetAmount = 1 + arc4random()%2;
    createdCard->cardTargets->targetAmount = targetAmount;
    if(targetAmount == 1){
        cardPower += 6;
    }
    int attack = (int)cardPower/6 + LLMath::diceRoll((int)cardPower/3, 3);
    cardCostOffset -= 2;
    
    MonsterHealthOffsetStatus *status = new MonsterHealthOffsetStatus();
    status->initWithHealthOffset(-attack);
    
    RandomMonsterStatus *rndStatus = new RandomMonsterStatus();
    rndStatus->initWithStatus(status, 1);
    
    createdCard->cardTargets->statuses->addObject(rndStatus);
    createdCard->setupDamageCard(attack);
    mainDescription = CCString::createWithFormat("\nRandom %i monsters", targetAmount);
}

void RandomTargetDamageTemplate::addRedMainStatus(){
    addNeutralMainStatus();
}

void RandomTargetDamageTemplate::addBlueMainStatus(){
    addNeutralMainStatus();
}

void RandomTargetDamageTemplate::addYellowMainStatus(){
    addNeutralMainStatus();
}

void RandomTargetDamageTemplate::addPurpleMainStatus(){
    addNeutralMainStatus();
}

#pragma mark -



