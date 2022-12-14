#pragma once

#include <Gui/Gui.h>

#include <nap/resourceptr.h>
#include <renderwindow.h>

namespace nap
{

	// Forward declarations;
	class Core;
	class IMGuiService;

	namespace gui
	{

		/**
		 * Displays a content Gui resource in a panel that can be freely positioned and sized within the available client area.
		 * Under the hood the ImGui::ChildWindow function is used to create the panel with a simplified interface compared to the GuiWindow resource.
		 */
		class NAPAPI Panel : public Gui
		{
			RTTI_ENABLE(Gui)

		public:
			/**
			 * Available flags for the panel
			 */
			struct Flags
			{
				bool mNoScrollBar = false;
				bool mNoScrollWithMouse = false;
				bool mHorizontalScrollBar = false;
			};
		public:
			// Properties

			// Positioning
			glm::vec2 mPosition = { 0.f, 0.f }; ///< Property: 'Position' Position of the panel within the available client area. Negative x and y values can be used in order to specify a position relative to the bottom right corner instead of the top left.
			glm::vec2 mSize = { 0.f, 0.f }; ///< Property: 'Size' The width and height of the panel. Negative values can be used to specify width and height values as a different to the width and height of the available client area.

			// ImGUi flags
			Flags mFlags; ///< Property: 'Flags' Values for flags can be specified in this struct

			float mAlpha = 1.f; ///< Property: 'Alpha' Alpha blending value for the panel's background. 0 is transparent, 1 is opaque.
			bool mBorder = true; ///< Property: 'Border' Indicates wether to draw a border around the panel.

			ResourcePtr<Gui> mContent = nullptr; ///< Property: 'Content' Embedded Gui resource that will be displayed inside the panel.

		public:
			Panel(Core& core);
			bool init(utility::ErrorState& errorState) override;

		private:
			void draw() override;
			Core& mCore;
			IMGuiService* mGuiService = nullptr;
		};

	} // namespace gui
} // namespace nap