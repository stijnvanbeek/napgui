#include "Action.h"

#include <Gui/GuiService.h>

RTTI_BEGIN_CLASS_NO_DEFAULT_CONSTRUCTOR(nap::gui::Action)
    RTTI_CONSTRUCTOR(nap::Core&)
    RTTI_PROPERTY("Key", &nap::gui::Action::mKey, nap::rtti::EPropertyMetaData::Default)
    RTTI_PROPERTY("KeyModifier", &nap::gui::Action::mKeyModifier, nap::rtti::EPropertyMetaData::Default)
RTTI_END_CLASS

DEFINE_GROUP(nap::gui::ActionGroup)

namespace nap
{

    namespace gui
    {

        Action::Action(Core &core) : Resource()
        {
            mGuiService = core.getService<GuiService>();
        }


        bool Action::init(utility::ErrorState &errorState)
        {
            return mGuiService->registerAction(*this, errorState);
        }


        void Action::onDestroy()
        {
            mGuiService->unregisterAction(*this);
        }
    }

}