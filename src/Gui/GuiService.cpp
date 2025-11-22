#include "GuiService.h"
#include <Gui/Action.h>

RTTI_BEGIN_CLASS_NO_DEFAULT_CONSTRUCTOR(nap::gui::GuiService)
    RTTI_CONSTRUCTOR(nap::ServiceConfiguration*)
RTTI_END_CLASS

namespace nap
{

    namespace gui
    {

        void GuiService::processKeyEvent(const KeyEvent &event)
        {
            for (auto& action : mActions)
                if (action->mKey == event.mKey && static_cast<KeyModifier>(action->mKeyModifier) == event.mModifier)
                    action->perform();
        }


        bool GuiService::registerAction(Action &action, utility::ErrorState &error_state)
        {
            if (action.mKey != EKeyCode::KEY_UNKNOWN)
            {
                auto it = std::find_if(mActions.begin(), mActions.end(), [&](auto& a)
                {
                    return a->mKey == action.mKey && a->mKeyModifier == action.mKeyModifier;
                });
                if (it != mActions.end())
                {
                    error_state.fail("Actions have duplicate key bindings: %s and %s", action.mID.c_str(), (*it)->mID.c_str());
                    return false;
                }
            }

            mActions.emplace(&action);
            return true;
        }

    }

}