#pragma once

#include <Gui/Gui.h>
#include <nap/resourceptr.h>

namespace nap
{
	namespace gui
	{

		/**
		 * Shows different Gui objects as tabs in a tab control.
		 */
		class NAPAPI TabbedLayout : public Gui
		{
			RTTI_ENABLE(Gui)
		public:
			/**
			 * Defines a tab within the tab control.
			 * The title of the tab is determined by the mContent member's title.
			 */
			struct Tab
			{
				bool mVisible = true; ///< Property: 'Visible' Indicates wether the tab is currently showed in the control
				ResourcePtr<Gui> mContent = nullptr; ///< Property: 'Content' The contents of the tab.
			};

			std::vector<Tab> mTabs; ///< Property: 'Tabs' List with all the tabs in the tab control

		public:
			TabbedLayout() = default;

		private:
			void draw() override;
		};

	} // namespace gui
} // namespace nap