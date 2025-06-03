#include "Panel.h"

#include <imguiservice.h>
#include <imgui/imgui.h>
#include <nap/core.h>

RTTI_BEGIN_STRUCT(nap::gui::Panel::Flags)
	RTTI_PROPERTY("NoScrollBar", &nap::gui::Panel::Flags::mNoScrollBar, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("NoScrollWithMouse", &nap::gui::Panel::Flags::mNoScrollWithMouse, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("HorizontalScrollBar", &nap::gui::Panel::Flags::mHorizontalScrollBar, nap::rtti::EPropertyMetaData::Default)
RTTI_END_STRUCT

RTTI_BEGIN_CLASS_NO_DEFAULT_CONSTRUCTOR(nap::gui::Panel)
	RTTI_CONSTRUCTOR(nap::Core&)
	RTTI_PROPERTY("Position", &nap::gui::Panel::mPosition, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("Size", &nap::gui::Panel::mSize, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("Flags", &nap::gui::Panel::mFlags, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("Alpha", &nap::gui::Panel::mAlpha, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("Border", &nap::gui::Panel::mBorder, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("TitleBar", &nap::gui::Panel::mTitleBar, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("Content", &nap::gui::Panel::mContent, nap::rtti::EPropertyMetaData::Embedded)
RTTI_END_CLASS


namespace nap
{
	namespace gui
	{

		Panel::Panel(Core& core) : mCore(core)
		{
			mGuiService = core.getService<IMGuiService>();
		}


		void Panel::draw()
		{
			float availableWidth = ImGui::GetWindowWidth();
			float availableHeight = ImGui::GetWindowHeight();

			ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
			if (mFlags.mNoScrollBar)
				flags = flags | ImGuiWindowFlags_NoScrollbar;
			if (mFlags.mNoScrollWithMouse)
				flags = flags | ImGuiWindowFlags_NoScrollWithMouse;
			if (mFlags.mHorizontalScrollBar)
				flags = flags | ImGuiWindowFlags_HorizontalScrollbar;

			ImGui::SetNextWindowBgAlpha(mAlpha);
			ImVec2 position(mPosition.x * mGuiService->getScale(), mPosition.y * mGuiService->getScale());
			if (position.x > availableWidth)
				position.x = availableWidth;
			if (position.x < 0)
				position.x = availableWidth + position.x;
			if (position.y > availableHeight)
				position.y = availableHeight;
			if (position.y < 0)
				position.y = availableHeight + position.y;

			ImVec2 size(mSize.x * mGuiService->getScale(), mSize.y * mGuiService->getScale());
			if (size.x > availableWidth)
				size.x = availableWidth;
			if (size.x <= 0)
				size.x = availableWidth + size.x;
			if (size.y > availableHeight)
				size.y = availableHeight;
			if (size.y <= 0)
				size.y = availableHeight + size.y;

			auto currentWindowPos = ImGui::GetWindowPos();
			ImGui::SetNextWindowPos(ImVec2(currentWindowPos.x + position.x, currentWindowPos.y + position.y));
			ImGui::SetNextWindowSize(size);

			if (ImGui::BeginChild(mID.c_str(), size, mBorder, flags))
			{
				if (mTitleBar)
					ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ImGui::GetTextLineHeightWithSpacing());
				if (mContent != nullptr)
					mContent->show();
				ImGui::EndChild();
			}

			if (mTitleBar)
			{
				auto rightBottom = ImVec2(ImGui::GetItemRectMax().x, ImGui::GetItemRectMin().y + ImGui::GetFrameHeight());
				auto titlePos = ImVec2(ImGui::GetItemRectMin().x + ImGui::GetStyle().FramePadding.x, ImGui::GetItemRectMin().y + ImGui::GetStyle().FramePadding.y);
				auto textColor = ImGui::ColorConvertFloat4ToU32(ImGui::GetStyle().Colors[ImGuiCol_Text]);
				auto bgColor = ImGui::ColorConvertFloat4ToU32(ImGui::GetStyle().Colors[ImGuiCol_TitleBg]);
				ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetItemRectMin(), rightBottom, bgColor);
				ImGui::GetWindowDrawList()->AddText(titlePos, textColor, mTitle.c_str());
			}
		}


		bool Panel::init(utility::ErrorState& errorState)
		{
			if (!errorState.check(!mTitle.empty(), "Panel needs a title: %s", mID.c_str()))
				return false;
			return true;
		}

	}
} // namespace nap