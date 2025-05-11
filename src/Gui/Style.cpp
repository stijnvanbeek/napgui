#include "Style.h"

#include <nap/core.h>
#include <imguiservice.h>

RTTI_BEGIN_CLASS_NO_DEFAULT_CONSTRUCTOR(nap::gui::StyleDef)
    RTTI_CONSTRUCTOR(nap::Core&)
	RTTI_PROPERTY("FloatSettings", &nap::gui::StyleDef::mFloatSettings, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("SizeSettings", &nap::gui::StyleDef::mSizeSettings, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("ColorSettings", &nap::gui::StyleDef::mColorSettings, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("FontScaling", &nap::gui::StyleDef::mFontScaling, nap::rtti::EPropertyMetaData::Default)
RTTI_END_CLASS

namespace nap
{
	namespace gui
	{

        StyleDef::StyleDef(Core& core)
        {
            mGuiService = core.getService<IMGuiService>();
        }


		void StyleDef::push()
		{
			for (auto& setting : mFloatSettings)
				ImGui::PushStyleVar(setting.mVariable, setting.mValue);
			for (auto& setting : mSizeSettings)
				ImGui::PushStyleVar(setting.mVariable, ImVec2(setting.mValue.x * mGuiService->getScale(), setting.mValue.y * mGuiService->getScale()));
			for (auto& setting : mColorSettings)
				ImGui::PushStyleColor(setting.mVariable, ImVec4(setting.mValue[0], setting.mValue[1], setting.mValue[2], setting.mValue[3]));
			ImGui::SetWindowFontScale(mFontScaling);
		}


		void StyleDef::pop()
		{
			for (auto& setting : mFloatSettings)
				ImGui::PopStyleVar();
			for (auto& setting : mSizeSettings)
				ImGui::PopStyleVar();
			for (auto& setting : mColorSettings)
				ImGui::PopStyleColor();
		}


		void StyleDef::apply(ImGuiStyle& imGuiStyle)
		{
			readFloat(imGuiStyle.Alpha, StyleDef::StyleVar::ImGuiStyleVar_Alpha);
			readFloat(imGuiStyle.WindowRounding, StyleDef::StyleVar::ImGuiStyleVar_WindowRounding);
			readFloat(imGuiStyle.WindowBorderSize, StyleDef::StyleVar::ImGuiStyleVar_WindowBorderSize, true);
			readFloat(imGuiStyle.ChildRounding, StyleDef::StyleVar::ImGuiStyleVar_ChildRounding);
			readFloat(imGuiStyle.ChildBorderSize, StyleDef::StyleVar::ImGuiStyleVar_ChildBorderSize, true);
			readFloat(imGuiStyle.PopupRounding, StyleDef::StyleVar::ImGuiStyleVar_PopupRounding);
			readFloat(imGuiStyle.PopupBorderSize, StyleDef::StyleVar::ImGuiStyleVar_PopupBorderSize, true);
			readFloat(imGuiStyle.FrameRounding, StyleDef::StyleVar::ImGuiStyleVar_FrameRounding);
			readFloat(imGuiStyle.FrameBorderSize, StyleDef::StyleVar::ImGuiStyleVar_FrameBorderSize, true);
			readFloat(imGuiStyle.IndentSpacing, StyleDef::StyleVar::ImGuiStyleVar_IndentSpacing, true);
			readFloat(imGuiStyle.ScrollbarSize, StyleDef::StyleVar::ImGuiStyleVar_ScrollbarSize, true);
			readFloat(imGuiStyle.ScrollbarRounding, StyleDef::StyleVar::ImGuiStyleVar_ScrollbarRounding);
			readFloat(imGuiStyle.GrabMinSize, StyleDef::StyleVar::ImGuiStyleVar_GrabMinSize, true);
			readFloat(imGuiStyle.GrabRounding, StyleDef::StyleVar::ImGuiStyleVar_GrabRounding);
			readFloat(imGuiStyle.TabRounding, StyleDef::StyleVar::ImGuiStyleVar_TabRounding);
			readSize(imGuiStyle.WindowPadding, StyleDef::StyleVar::ImGuiStyleVar_WindowPadding, true);
			readSize(imGuiStyle.WindowMinSize, StyleDef::StyleVar::ImGuiStyleVar_WindowMinSize, true);
			readSize(imGuiStyle.WindowTitleAlign, StyleDef::StyleVar::ImGuiStyleVar_WindowTitleAlign, true);
			readSize(imGuiStyle.FramePadding, StyleDef::StyleVar::ImGuiStyleVar_FramePadding, true);
			readSize(imGuiStyle.ItemSpacing, StyleDef::StyleVar::ImGuiStyleVar_ItemSpacing, true);
			readSize(imGuiStyle.ItemInnerSpacing, StyleDef::StyleVar::ImGuiStyleVar_ItemInnerSpacing, true);
			readSize(imGuiStyle.ButtonTextAlign, StyleDef::StyleVar::ImGuiStyleVar_ButtonTextAlign, true);
			readSize(imGuiStyle.SelectableTextAlign, StyleDef::StyleVar::ImGuiStyleVar_SelectableTextAlign, true);

			for (auto& setting : mColorSettings)
				imGuiStyle.Colors[setting.mVariable] = ImVec4(setting.mValue[0], setting.mValue[1], setting.mValue[2], setting.mValue[3]);
		}


		void StyleDef::readFloat(float& dest, StyleVar variable, bool scale)
		{
			auto it = std::find_if(mFloatSettings.begin(), mFloatSettings.end(), [&](auto& setting){
				return setting.mVariable == variable;
			});
			if (it != mFloatSettings.end())
				dest = scale ? it->mValue * mGuiService->getScale() : it->mValue;
		}


		void StyleDef::readSize(ImVec2& dest, StyleVar variable, bool scale)
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
