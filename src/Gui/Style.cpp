#include "Style.h"

#include <nap/core.h>
#include <imguiservice.h>

RTTI_BEGIN_CLASS_NO_DEFAULT_CONSTRUCTOR(nap::gui::Style)
    RTTI_CONSTRUCTOR(nap::Core&)
	RTTI_PROPERTY("FloatSettings", &nap::gui::Style::mFloatSettings, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("SizeSettings", &nap::gui::Style::mSizeSettings, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("ColorSettings", &nap::gui::Style::mColorSettings, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("FontScaling", &nap::gui::Style::mFontScaling, nap::rtti::EPropertyMetaData::Default)
RTTI_END_CLASS

namespace nap
{
	namespace gui
	{

        Style::Style(Core& core)
        {
            mGuiService = core.getService<IMGuiService>();
        }


		void Style::push()
		{
			for (auto& setting : mFloatSettings)
				ImGui::PushStyleVar(setting.mVariable, setting.mValue);
			for (auto& setting : mSizeSettings)
				ImGui::PushStyleVar(setting.mVariable, ImVec2(setting.mValue.x * mGuiService->getScale(), setting.mValue.y * mGuiService->getScale()));
			for (auto& setting : mColorSettings)
				ImGui::PushStyleColor(setting.mVariable, ImVec4(setting.mValue[0], setting.mValue[1], setting.mValue[2], setting.mValue[3]));
			ImGui::SetWindowFontScale(mFontScaling);
		}


		void Style::pop()
		{
			for (auto& setting : mFloatSettings)
				ImGui::PopStyleVar();
			for (auto& setting : mSizeSettings)
				ImGui::PopStyleVar();
			for (auto& setting : mColorSettings)
				ImGui::PopStyleColor();
		}


		void Style::apply(ImGuiStyle& imGuiStyle)
		{
			readFloat(imGuiStyle.Alpha, Style::StyleVar::ImGuiStyleVar_Alpha);
			readFloat(imGuiStyle.WindowRounding, Style::StyleVar::ImGuiStyleVar_WindowRounding);
			readFloat(imGuiStyle.WindowBorderSize, Style::StyleVar::ImGuiStyleVar_WindowBorderSize, true);
			readFloat(imGuiStyle.ChildRounding, Style::StyleVar::ImGuiStyleVar_ChildRounding);
			readFloat(imGuiStyle.ChildBorderSize, Style::StyleVar::ImGuiStyleVar_ChildBorderSize, true);
			readFloat(imGuiStyle.PopupRounding, Style::StyleVar::ImGuiStyleVar_PopupRounding);
			readFloat(imGuiStyle.PopupBorderSize, Style::StyleVar::ImGuiStyleVar_PopupBorderSize, true);
			readFloat(imGuiStyle.FrameRounding, Style::StyleVar::ImGuiStyleVar_FrameRounding);
			readFloat(imGuiStyle.FrameBorderSize, Style::StyleVar::ImGuiStyleVar_FrameBorderSize, true);
			readFloat(imGuiStyle.IndentSpacing, Style::StyleVar::ImGuiStyleVar_IndentSpacing, true);
			readFloat(imGuiStyle.ScrollbarSize, Style::StyleVar::ImGuiStyleVar_ScrollbarSize, true);
			readFloat(imGuiStyle.ScrollbarRounding, Style::StyleVar::ImGuiStyleVar_ScrollbarRounding);
			readFloat(imGuiStyle.GrabMinSize, Style::StyleVar::ImGuiStyleVar_GrabMinSize, true);
			readFloat(imGuiStyle.GrabRounding, Style::StyleVar::ImGuiStyleVar_GrabRounding);
			readFloat(imGuiStyle.TabRounding, Style::StyleVar::ImGuiStyleVar_TabRounding);
			readSize(imGuiStyle.WindowPadding, Style::StyleVar::ImGuiStyleVar_WindowPadding, true);
			readSize(imGuiStyle.WindowMinSize, Style::StyleVar::ImGuiStyleVar_WindowMinSize, true);
			readSize(imGuiStyle.WindowTitleAlign, Style::StyleVar::ImGuiStyleVar_WindowTitleAlign, true);
			readSize(imGuiStyle.FramePadding, Style::StyleVar::ImGuiStyleVar_FramePadding, true);
			readSize(imGuiStyle.ItemSpacing, Style::StyleVar::ImGuiStyleVar_ItemSpacing, true);
			readSize(imGuiStyle.ItemInnerSpacing, Style::StyleVar::ImGuiStyleVar_ItemInnerSpacing, true);
			readSize(imGuiStyle.ButtonTextAlign, Style::StyleVar::ImGuiStyleVar_ButtonTextAlign, true);
			readSize(imGuiStyle.SelectableTextAlign, Style::StyleVar::ImGuiStyleVar_SelectableTextAlign, true);

			for (auto& setting : mColorSettings)
				imGuiStyle.Colors[setting.mVariable] = ImVec4(setting.mValue[0], setting.mValue[1], setting.mValue[2], setting.mValue[3]);
		}


		void Style::readFloat(float& dest, StyleVar variable, bool scale)
		{
			auto it = std::find_if(mFloatSettings.begin(), mFloatSettings.end(), [&](auto& setting){
				return setting.mVariable == variable;
			});
			if (it != mFloatSettings.end())
				dest = scale ? it->mValue * mGuiService->getScale() : it->mValue;
		}


		void Style::readSize(ImVec2& dest, StyleVar variable, bool scale)
		{
			auto it = std::find_if(mSizeSettings.begin(), mSizeSettings.end(), [&](auto& setting){
				return setting.mVariable == variable;
			});
			if (it != mSizeSettings.end())
            {
                if (scale)
                    dest = ImVec2(it->mValue.x * mGuiService->getScale(), it->mValue.y * mGuiService->getScale());
                else
                    dest = ImVec2(it->mValue.x, it->mValue.y);
            }
		}

	}
} // namespace nap
