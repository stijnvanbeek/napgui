#pragma once

#include <nap/group.h>

#include "nap/signalslot.h"

namespace nap
{
    namespace gui
    {
    
        class Action : public Resource
        {
            RTTI_ENABLE(Resource)
            
        public:
            Action() = default;
            Signal<> perform;
        };


        using ActionGroup = Group<Action>;
    
    }
}
