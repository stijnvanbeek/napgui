#pragma once

#include <nap/service.h>
#include <inputevent.h>

namespace nap
{
    namespace gui
    {

        // Forward declarations
        class Action;
    
        class NAPAPI GuiService : public Service
        {
            RTTI_ENABLE(Service)

            friend class Action;
        public:
            GuiService(ServiceConfiguration* configuration) : Service(configuration) { }
            void processKeyEvent(const KeyEvent& event);
            
        private:
            bool registerAction(Action& action, utility::ErrorState& error_state);
            void unregisterAction(Action& action) { mActions.erase(&action); }

            std::set<Action*> mActions;
        };
    
    }
}
