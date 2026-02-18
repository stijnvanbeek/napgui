#include "GuiService.h"
#include <Gui/Action.h>

RTTI_BEGIN_CLASS_NO_DEFAULT_CONSTRUCTOR(nap::gui::GuiService)
    RTTI_CONSTRUCTOR(nap::ServiceConfiguration*)
RTTI_END_CLASS

namespace nap
{

    namespace gui
    {


        bool checkKeyEventWithAction(const KeyEvent &event, Action &action)
        {
            bool shiftDown  = (event.mModifier & static_cast<KeyModifier>(EKeyModifier::Shift))   != 0;
            bool ctrlDown   = (event.mModifier & static_cast<KeyModifier>(EKeyModifier::Control)) != 0;
            bool altDown    = (event.mModifier & static_cast<KeyModifier>(EKeyModifier::Alt))     != 0;
            bool guiDown    = (event.mModifier & static_cast<KeyModifier>(EKeyModifier::Gui))     != 0;

#ifdef __APPLE__
            bool superDown  = guiDown;
#else
            bool superDown  = ctrlDown;
#endif

            bool modifiersOk = (shiftDown == action.mModShift)
                            && (altDown   == action.mModAlt)
                            && (superDown == action.mModSuper);

            if (action.mKey == event.mKey && modifiersOk)
                return true;

            return false;
        }


        void GuiService::processKeyEvent(const KeyEvent &event)
        {
            for (auto& action : mActions)
            {
                if (checkKeyEventWithAction(event, *action))
                    action->perform();
            }
        }


        bool GuiService::registerAction(Action &action, utility::ErrorState &error_state)
        {
            if (action.mKey != EKeyCode::KEY_UNKNOWN)
            {
                auto it = std::find_if(mActions.begin(), mActions.end(), [&](auto& a)
                {
                    return a->mKey == action.mKey &&
                        a->mModShift == action.mModShift &&
                        a->mModAlt == action.mModAlt &&
                        a->mModSuper == action.mModSuper;
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