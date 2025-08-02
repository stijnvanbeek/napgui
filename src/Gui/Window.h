#pragma once

#include <Gui/Gui.h>
#include <Gui/MenuBar.h>

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
		 * Represents an ImGui window or child window
		 */
		class NAPAPI GuiWindow : public Gui
		{
			RTTI_ENABLE(Gui)

		public:
			/**
			 * Settings for the flags that control the window's properties
			 */
			struct WindowFlags
			{
				bool mNoTitleBar = false;
				bool mNoResize = false;
				bool mNoMove = false;
				bool mNoScrollBar = false;
				bool mNoScrollWithMouse = false;
				bool mNoCollapse = false;
				bool mAlwaysAutoResize = false;
				bool mNoSavedSettings = false;
				bool mMenuBar = false;
				bool mHorizontalScrollBar = false;
				bool mCanClose = false;
			};
		public:
			// Properties

			// Positioning
			// Positioning
			glm::vec2 mPosition = { 0.f, 0.f }; ///< Property: 'Position' Position of the window within the available client area. Negative x and y values can be used in order to specify a position relative to the bottom right corner instead of the top left.
			glm::vec2 mSize = { 0.f, 0.f }; ///< Property: 'Size' The width and height of the window. Negative values can be used to specify width and height values as a different to the width and height of the available client area.

			// ImGUi flags
			WindowFlags mFlags; ///< Property: 'Flags' Struct specifying the settings of the window's ImGui flags

			float mAlpha = 1.f; ///< Property: 'Alpha' Alpha blending value for the panel's background. 0 is transparent, 1 is opaque.
			bool mBorder = true; ///< Property: 'Border' Indicates wether to draw a border around the panel.
			bool mOpen = true; ///< Property: 'Open' Indicares wether the window is currently open and visible. Can be altered at runtime to open or close the window.

			ResourcePtr<RenderWindow> mRenderWindow = nullptr; ///< Property: 'RenderWindow' The RenderWindow the panel will be rendered to. Optional, only needed when this panel is rendered directly onto the render window.
			ResourcePtr<Gui> mContent = nullptr; ///< Property: 'Content' The Gui that is displayed inside the window.
			ResourcePtr<MenuBar> mMenuBar = nullptr; ///< Property: 'MenuBar' Link to the window's menu bar, if any

		public:
			GuiWindow(Core& core);
			bool init(utility::ErrorState& errorState) override;

		private:
			void draw() override;
			Core& mCore;
			IMGuiService* mGuiService = nullptr;
		};

	} // namespace gui
} // namespace nap