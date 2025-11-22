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
            auto title = mTitle;
            std::string keyStr = "";
            if (mAction->mKey != EKeyCode::KEY_UNKNOWN)
            {
                if (mAction->mKeyModifier != EKeyModifier::None)
                {
                    auto mod_name = RTTI_OF(EKeyModifier).get_enumeration().value_to_name(mAction->mKeyModifier);
                    keyStr = keyStr + "(" + mod_name + "+";
                }
                else
                    keyStr = keyStr + " (";
                auto key_name = RTTI_OF(EKeyCode).get_enumeration().value_to_name(mAction->mKey);
                keyStr = keyStr + key_name + ")";
            }
            if (ImGui::MenuItem(title.c_str()))
                mAction->perform();
            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetColorU32(ImGuiCol_TextDisabled));
            ImGui::Text(keyStr.c_str());
            ImGui::PopStyleColor();
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