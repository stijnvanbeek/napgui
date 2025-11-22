#pragma once

#include <nap/group.h>
#include <nap/signalslot.h>

namespace nap
{
    namespace gui
    {
    
        class Action : public Resource
        {
            RTTI_ENABLE(Resource)
            
        public:
            Action() = default;
            void perform() { performSignal.trigger(*this); }
            Signal<Action&> performSignal;
        };


        using ActionGroup = Group<Action>;
    
    }
}
