#pragma once

#include <Gui/Action.h>
#include <nap/service.h>
#include <inputevent.h>

namespace nap
{
    namespace gui
    {
    
        class GuiService : public Service
        {
            RTTI_ENABLE(Service)

            friend class Action;

        public:
            GuiService() = default;

            void processKeyEvent(const KeyEvent& event);
            
        private:
            void registerAction(Action& action) { mActions.emplace(&action); }
            void unregisterAction(Action& action) { mActions.erase(&action); }

            std::set<Action*> mActions;
        };
    
    }
}
