//
//  Command.hpp
//  SRE
//
//  Created by Rasmus Odgaard on 28/11/2018.
//

#pragma once
#include "PlayingState.hpp"

class Command
{
    // 1. Create a class that encapsulates an object and a member function
    // a pointer to a member function (the attribute's name is "method")
    PlayingState *object;
    void(PlayingState:: *method)();
public:
    Command(PlayingState *obj = 0, void(PlayingState:: *meth)() = 0)
    {
        object = obj; // the argument's name is "meth"
        method = meth;
    }
    void execute()
    {
        ((*object).*method)(); // invoke the method on the object
    }
};
