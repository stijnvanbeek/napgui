#include "Window.h"

#include <imguiservice.h>
#include <imgui/imgui.h>
#include <nap/core.h>

RTTI_BEGIN_STRUCT(nap::gui::GuiWindow::WindowFlags)
	RTTI_PROPERTY("NoTitleBar", &nap::gui::GuiWindow::WindowFlags::mNoTitleBar, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("NoResize", &nap::gui::GuiWindow::WindowFlags::mNoResize, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("NoMove", &nap::gui::GuiWindow::WindowFlags::mNoMove, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("NoScrollBar", &nap::gui::GuiWindow::WindowFlags::mNoScrollBar, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("NoScrollWithMouse", &nap::gui::GuiWindow::WindowFlags::mNoScrollWithMouse, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("NoCollapse", &nap::gui::GuiWindow::WindowFlags::mNoCollapse, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("AlwaysAutoResize", &nap::gui::GuiWindow::WindowFlags::mAlwaysAutoResize, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("NoSavedSettings", &nap::gui::GuiWindow::WindowFlags::mNoSavedSettings, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("MenuBar", &nap::gui::GuiWindow::WindowFlags::mMenuBar, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("HorizontalScrollBar", &nap::gui::GuiWindow::WindowFlags::mHorizontalScrollBar, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("CanClose", &nap::gui::GuiWindow::WindowFlags::mCanClose, nap::rtti::EPropertyMetaData::Default)
RTTI_END_STRUCT

RTTI_BEGIN_CLASS_NO_DEFAULT_CONSTRUCTOR(nap::gui::GuiWindow)
	RTTI_CONSTRUCTOR(nap::Core&)
	RTTI_PROPERTY("Position", &nap::gui::GuiWindow::mPosition, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("Size", &nap::gui::GuiWindow::mSize, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("Flags", &nap::gui::GuiWindow::mFlags, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("Alpha", &nap::gui::GuiWindow::mAlpha, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("Open", &nap::gui::GuiWindow::mOpen, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("Border", &nap::gui::GuiWindow::mBorder, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("RenderWindow", &nap::gui::GuiWindow::mRenderWindow, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("Content", &nap::gui::GuiWindow::mContent, nap::rtti::EPropertyMetaData::Embedded)
RTTI_END_CLASS


namespace nap
{
	namespace gui
	{

		GuiWindow::GuiWindow(Core& core) : mCore(core)
		{
			mGuiService = core.getService<IMGuiService>();
		}


		void GuiWindow::draw()
		{
			if (!mOpen)
				return;

			float availableWidth;
			float availableHeight;
			if (mRenderWindow != nullptr)
			{
				mGuiService->selectWindow(mRenderWindow);
				availableWidth = mRenderWindow->getWidthPixels();
				availableHeight = mRenderWindow->getHeightPixels();
			}
			else
			{
				availableWidth = ImGui::GetWindowWidth();
				availableHeight = ImGui::GetWindowHeight();
			}

			ImGuiWindowFlags flags = ImGuiWindowFlags_None;
			if (mFlags.mNoTitleBar)
				flags = flags | ImGuiWindowFlags_NoTitleBar;
			if (mFlags.mNoMove)
				flags = flags | ImGuiWindowFlags_NoMove;
			if (mFlags.mNoResize)
				flags = flags | ImGuiWindowFlags_NoResize;
			if (mFlags.mNoScrollBar)
				flags = flags | ImGuiWindowFlags_NoScrollbar;
			if (mFlags.mNoScrollWithMouse)
				flags = flags | ImGuiWindowFlags_NoScrollWithMouse;
			if (mFlags.mNoCollapse)
				flags = flags | ImGuiWindowFlags_NoCollapse;
			if (mFlags.mAlwaysAutoResize)
				flags = flags | ImGuiWindowFlags_AlwaysAutoResize;
			if (mFlags.mNoSavedSettings)
				flags = flags | ImGuiWindowFlags_NoSavedSettings;
			if (mFlags.mMenuBar)
				flags = flags | ImGuiWindowFlags_MenuBar;
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
			ImGui::SetNextWindowSize(size, mFlags.mNoResize ? ImGuiCond_Always : ImGuiCond_Once);

			const std::string label = mTitle + "###" + mID;

			if (mRenderWindow != nullptr)
			{
				ImGui::SetNextWindowPos(position, mFlags.mNoMove ? ImGuiCond_Always : ImGuiCond_Once);
				bool* openPtr = mFlags.mCanClose ? &mOpen : nullptr;
				if (ImGui::Begin(label.c_str(), openPtr, flags))
				{
					if (mContent != nullptr)
						mContent->show();
					ImGui::End();
				}
			}
			else {
				ImGui::SetNextWindowPos(ImVec2(currentWindowPos.x + position.x, currentWindowPos.y + position.y), mFlags.mNoMove ? ImGuiCond_Always : ImGuiCond_Once);
				if (ImGui::BeginChild(label.c_str(), size, mBorder, flags))
				{
					if (mContent != nullptr)
						mContent->show();
					ImGui::EndChild();
				}
			}
		}


		bool GuiWindow::init(utility::ErrorState& errorState)
		{
			if (!errorState.check(mRenderWindow == nullptr || mStyle == nullptr, "Outer Panel %s directly rendered on renderwindow can't have it's own Style. Call Style::apply() instead.", mTitle.c_str()))
				return false;
			return true;
		}

	}
} // namespace nap