//
//  Command.hpp
//  SRE
//
//  Created by Rasmus Odgaard on 28/11/2018.
//

#pragma once
#include "DragonController.hpp"

class Command
{
    // 1. Create a class that encapsulates an object and a member function
    // a pointer to a member function (the attribute's name is "method")
    DragonController *object;
    void(DragonController:: *method)();
public:
    Command(DragonController *obj = 0, void(DragonController:: *meth)() = 0)
    {
        object = obj; // the argument's name is "meth"
        method = meth;
    }
    void execute()
    {
        ((*object).*method)(); // invoke the method on the object
    }
};
