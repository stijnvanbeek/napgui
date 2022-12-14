#pragma once

#include <nap/resource.h>
#include <imgui/imgui.h>

#include <imguistylesettings.h>

namespace nap
{

    // Forward declarations
    class IMGuiService;

	namespace gui
	{

		/**
		 * Resource that can hold an arbitrary number of style settings that can be applied to any Gui object.
		 */
		class NAPAPI Style : public Resource
		{
			RTTI_ENABLE(Resource)

		public:
			using StyleVar = ImGuiStyleVar_;
			using ColorStyleVar = ImGuiCol_;

		public:
			std::vector<FloatSetting> mFloatSettings; ///< Property: 'FloatSettings' All style variable settings of type float
			std::vector<SizeSetting> mSizeSettings; ///< Property: 'SizeSettings' All style variable settings of type vec2, indicating a rectangle size
			std::vector<ColorSetting> mColorSettings; ///< Property: 'ColorSettings' All style variable settings specifying a color
			float mFontScaling = 1.f; ///< Property: 'FontScaling'

		public:
            Style(Core& core);
			void push();
			void pop();
			void apply(ImGuiStyle& imGuiStyle);

		private:
			void readFloat(float& dest, StyleVar variable, bool scale = false);
			void readSize(ImVec2& dest, StyleVar variable, bool scale = false);
            IMGuiService* mGuiService = nullptr;
		};


	} // namespace gui

} // namespace nap
