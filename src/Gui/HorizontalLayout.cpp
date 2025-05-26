#include "HorizontalLayout.h"

#include <imgui/imgui.h>
#include <imgui_internal.h>


RTTI_BEGIN_CLASS(nap::gui::HorizontalLayout)
	RTTI_PROPERTY("ColumnWidths", &nap::gui::HorizontalLayout::mColumnWidths, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("Borders", &nap::gui::HorizontalLayout::mBorders, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("Resizable", &nap::gui::HorizontalLayout::mResizable, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("RelativeSizes", &nap::gui::HorizontalLayout::mRelativeSizes, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("Content", &nap::gui::HorizontalLayout::mContent, nap::rtti::EPropertyMetaData::Embedded)
RTTI_END_CLASS

namespace nap
{
	namespace gui
	{
		bool HorizontalLayout::init(utility::ErrorState &errorState)
		{
			if (mColumnWidths.empty())
				return true;

			if (mColumnWidths.size() != mContent.size())
			{
				errorState.fail("Layout %s: ColumnWidths needs to be empty or equal size to Content");
				return false;
			}

			return true;
		}


		void HorizontalLayout::draw()
		{
			auto height = ImGui::GetContentRegionAvail().y;
			auto totalWidth = ImGui::GetContentRegionAvail().x;
			if (mColumnWidths.empty())
				mColumnWidths.resize(mContent.size(), totalWidth / mContent.size());

			// Normalize column widths
			if (mRelativeSizes)
			{
				auto sum = 0.f;
				for (auto& column : mColumnWidths)
					sum += column;
				for (auto& column : mColumnWidths)
					column = (column / sum) * totalWidth;
			}

			ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_HorizontalScrollbar;

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0,0));
			auto i = 0;
			for (auto& column : mContent)
			{
				std::string id = mID + "Column" + std::to_string(i);
				ImGui::BeginChild(id.c_str(), ImVec2(mColumnWidths[i], height), mBorders, flags);
				ImGui::PopStyleVar();
				column->show();
				ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0,0));
				ImGui::EndChild();
				if (column != mContent.back())
				{
					if (mResizable)
					{
						ImGui::SameLine();
						ImGui::InvisibleButton((mID + "Splitter" + std::to_string(i)).c_str(), ImVec2(8.f, height));
						if (ImGui::IsItemActive())
						{
							mColumnWidths[i] += ImGui::GetIO().MouseDelta.x;
							mColumnWidths[i + 1] -= ImGui::GetIO().MouseDelta.x;
						}
					}
					ImGui::SameLine();
				}
				++i;
			}
			ImGui::PopStyleVar();
		}

	}
} // namespace nap