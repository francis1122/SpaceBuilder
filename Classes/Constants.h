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


//research tiers
#define RESEARCH_TIER_1 50
#define RESEARCH_TIER_2 150
#define RESEARCH_TIER_3 300
#define RESEARCH_TIER_4 800
#define RESEARCH_TIER_5 10000



#define SYSTEM_RESOURCECARD_LIMIT 8

typedef enum ResourceTypes{
    FoodResource,
    ProductionResource,
    MoneyResource,
    TechResource,
    WasteResource
} ResourceTypes;

typedef enum ResearchTypes{
    MilitaryTech,
    IndustryTech,
    ExpansionTech,
    ScienceTech
} ResearchTypes;

typedef enum PlanetSize{
    Small,
    Medium,
    Large
} PlanetSize;

typedef enum PlanetType{
    Terran,
    Arid,
    Artic
} PlanetType;

#endif
