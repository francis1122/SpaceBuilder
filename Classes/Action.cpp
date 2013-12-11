//
//  Action.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 12/10/13.
//
//

#include "Action.h"



bool Action::init(ActionType type){
    actionType = type;
    return true;
}


ccColor3B Action::getActionColor(){
    if(actionType == Neutral){
        return ccGRAY;
    }else if(actionType == Red){
        return ccRED;
    }else if(actionType == Blue){
        return ccBLUE;
    }else if(actionType == Purple){
        return ccMAGENTA;
    }else if(actionType == Yellow){
        return ccYELLOW;
    }
    return ccBLACK;
}