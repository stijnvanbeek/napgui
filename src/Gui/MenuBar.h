#pragma once

#include <Gui/Gui.h>
#include <Gui/Action.h>

namespace nap
{
    namespace gui
    {
    
        class NAPAPI MenuItemBase : public Resource
        {
            RTTI_ENABLE(Resource)

        public:
            MenuItemBase() = default;

            std::string mTitle; ///< Property: 'Title'

            virtual void draw() { }
        };


        class NAPAPI MenuItem : public MenuItemBase
        {
            RTTI_ENABLE(MenuItemBase)

        public:
            MenuItem() = default;

            ResourcePtr<Action> mAction; ///< Property: 'Action'

            void draw() override;
        };


        class NAPAPI Menu : public MenuItemBase
        {
            RTTI_ENABLE(MenuItemBase)

        public:
            Menu() = default;

            std::vector<ResourcePtr<MenuItemBase>> mItems; ///< Property: 'Items'

            void draw() override;
        };


        class NAPAPI MenuBar : public Gui
        {
            RTTI_ENABLE(Gui)

        public:
            MenuBar() = default;

            std::vector<ResourcePtr<Menu>> mMenus; ///< Property: 'Menus'

        private:
            void draw() override;
        };
    
    }
}