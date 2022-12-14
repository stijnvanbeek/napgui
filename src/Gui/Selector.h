#pragma once

#include <Gui/Gui.h>
#include <nap/resourceptr.h>

namespace nap
{
	namespace gui
	{

		/**
		 * A Selector can switch between different contents using a property.
		 */
		class NAPAPI Selector : public Gui
		{
			RTTI_ENABLE(Gui)

		public:
			int mIndex = 0; ///< Property: 'Index' The index of the Gui within the Content property that is currently being displayed. This property can be freely changed at runtime and for example controlled by a button within a different Gui that points to this selector.

			std::vector<ResourcePtr<Gui>> mContent; ///< Property: 'Content' List of Gui resources that can be switched between and diplayed as content.

		public:
			Selector() = default;

		private:
			void draw() override;
		};

	} // namespace gui

} // namespace nap