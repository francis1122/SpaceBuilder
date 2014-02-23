//
//  Constants.h
//  RogueDeck
//
//  Created by Hunter Francis on 12/11/13.
//
//

#ifndef RogueDeck_Constants_h
#define RogueDeck_Constants_h


#define Main_Font "BlueHighway-Regular"
//#define Main_Font "Marmelad-Regular"
#define Main_Bold_Font "BlueHighway-Bold"
//#define LARGE_NUMBER_FONT "FetteEgyptienne"
#define LARGE_NUMBER_FONT "BambiBold"

#define MONSTER_IMPROVEMENT_PER_LEVEL 4
#define DEFAULT_CARD_SCALE .25
#define DEFAULT_MONSTER_CARD_SCALE .3


#define GM GameManager::sharedGameManager()
#define AM AnimationManager::sharedAnimationManager()
#define MG MonsterGenerator::sharedMonsterGeneratorManager()

//z ordering of objects

#define ZORDERING_ACTIONSPRITE 6
#define ZORDERING_ACTIONHOLDER 5

#endif
