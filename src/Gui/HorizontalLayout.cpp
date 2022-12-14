#include "HorizontalLayout.h"

#include <imgui/imgui.h>

RTTI_BEGIN_CLASS(nap::gui::HorizontalLayout)
	RTTI_PROPERTY("ColumnWidths", &nap::gui::HorizontalLayout::mColumnWidths, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("Borders", &nap::gui::HorizontalLayout::mBorders, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("Content", &nap::gui::HorizontalLayout::mContent, nap::rtti::EPropertyMetaData::Embedded)
RTTI_END_CLASS

namespace nap
{
	namespace gui
	{

		void HorizontalLayout::draw()
		{
			ImGui::Columns(mContent.size(), nullptr, mBorders);
			for (auto i = 0; i < mContent.size(); ++i)
			{
				mContent[i]->show();
				ImGui::NextColumn();
			}
			ImGui::Columns(1);
		}

	}
} // namespace nap