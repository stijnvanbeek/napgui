#pragma once

#include <keyboard.h>
#include <nap/group.h>
#include <nap/signalslot.h>
#include <nap/core.h>

namespace nap
{
    namespace gui
    {

        // Forward declarations
        class GuiService;
    
        class Action : public Resource
        {
            RTTI_ENABLE(Resource)
            
        public:
            Action(Core& core);

            EKeyCode mKey = EKeyCode::KEY_UNKNOWN; ///< Property: 'Key'
            EKeyModifier mKeyModifier = EKeyModifier::None; ///< Property: 'KeyModifier'

            bool init(utility::ErrorState &errorState) override;
            void onDestroy() override;

            void perform() { performSignal.trigger(*this); }
            Signal<Action&> performSignal;

        private:
            GuiService* mGuiService = nullptr;
        };


        using ActionGroup = Group<Action>;
    
    }
}
