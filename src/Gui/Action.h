#pragma once

#include <nap/group.h>

namespace nap
{
    namespace gui
    {
    
        class Action : public Resource
        {
            RTTI_ENABLE(Resource)
            
        public:
            Action() = default;
            
        private:
        };


        using ActionGroup = Group<Action>;
    
    }
}