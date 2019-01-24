//
//  Command.hpp
//  SRE
//

#pragma once
#include "PlayingState.hpp"

class Command
{
    // Store reference to playing state
    PlayingState *object;
    // Store reference to playing state method
    void(PlayingState:: *method)();
public:
    // Constructor
    Command(PlayingState *obj = 0, void(PlayingState:: *meth)() = 0)
    {
        object = obj;
        method = meth;
    }
    void execute()
    {
        // invoke the method on the object
        ((*object).*method)(); 
    }
};
