#include "MenuBar.h"

RTTI_BEGIN_CLASS(nap::gui::MenuItemBase)
    RTTI_PROPERTY("Title", &nap::gui::MenuItemBase::mTitle, nap::rtti::EPropertyMetaData::Default)
RTTI_END_CLASS

RTTI_BEGIN_CLASS(nap::gui::MenuItem)
    RTTI_PROPERTY("Action", &nap::gui::MenuItem::mAction, nap::rtti::EPropertyMetaData::Default)
RTTI_END_CLASS

RTTI_BEGIN_CLASS(nap::gui::Menu)
    RTTI_PROPERTY("Items", &nap::gui::Menu::mItems, nap::rtti::EPropertyMetaData::Embedded)
RTTI_END_CLASS

RTTI_BEGIN_CLASS(nap::gui::MenuBar)
    RTTI_PROPERTY("Menus", &nap::gui::MenuBar::mMenus, nap::rtti::EPropertyMetaData::Embedded)
RTTI_END_CLASS

namespace nap
{

    namespace gui
    {

        void Menu::draw()
        {
            if (ImGui::BeginMenu(mTitle.c_str()))
            {
                for (auto& item : mItems)
                    item->draw();
                ImGui::EndMenu();
            }
        }


        void MenuItem::draw()
        {
            if (ImGui::MenuItem(mTitle.c_str()))
                mAction->perform();
        }


        void MenuBar::draw()
        {
            if (ImGui::BeginMenuBar())
            {
                for (auto& menu : mMenus)
                    menu->draw();
                ImGui::EndMenuBar();
            }
        }

    }

}