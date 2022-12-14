#include "TabbedLayout.h"


RTTI_BEGIN_STRUCT(nap::gui::TabbedLayout::Tab)
	RTTI_PROPERTY("Visible", &nap::gui::TabbedLayout::Tab::mVisible, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("Content", &nap::gui::TabbedLayout::Tab::mContent, nap::rtti::EPropertyMetaData::Embedded)
RTTI_END_STRUCT

RTTI_BEGIN_CLASS(nap::gui::TabbedLayout)
	RTTI_PROPERTY("Tabs", &nap::gui::TabbedLayout::mTabs, nap::rtti::EPropertyMetaData::Default)
RTTI_END_CLASS

namespace nap
{
	namespace gui
	{

		void TabbedLayout::draw()
		{
			if (ImGui::BeginTabBar(mTitle.c_str(), ImGuiTabBarFlags_None))
			{
				for (auto& tab : mTabs)
					if (tab.mVisible && ImGui::BeginTabItem(tab.mContent->mTitle.c_str()))
					{
						tab.mContent->show();
						ImGui::EndTabItem();
					}

				ImGui::EndTabBar();
			}
		}

	}
} // namespace nap