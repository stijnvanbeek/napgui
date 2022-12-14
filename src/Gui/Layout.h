#pragma once

#include <Gui/Gui.h>

#include <nap/resourceptr.h>

namespace nap
{
	namespace gui
	{

		/**
		 * Displays a number of Guis after one another without applying any layout.
		 * ImGui will typically display content underneath one another in lines.
		 * However, this object can also be used to group a collection of (child) windows or panels using GuiWindow or Panel.
		 * For Windows and Panels the positions and sizes can be explicitly specified and they can be freely positioned in the available space.
		 * In other words this is merely a grouping class.
		 */
		class NAPAPI Layout : public Gui
		{
			RTTI_ENABLE(Gui)

		public:
			bool mSeparators = false; ///< Property: 'Separators' Indicates wether separators should be drawn in between the different content items.
			std::vector<ResourcePtr<Gui>> mContent; ///< Property: 'Content'  List of Guis that will be displayed as content.

		public:
			Layout() = default;

		private:
			void draw() override;
		};

	} // namespace gui
} // namespace nap