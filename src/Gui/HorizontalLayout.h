#pragma once

#include <Gui/Gui.h>
#include <nap/resourceptr.h>

namespace nap
{
	namespace gui
	{


		/**
		 * Lays out a series of content Guis in horizontal columns.
		 */
		class NAPAPI HorizontalLayout : public Gui
		{
			RTTI_ENABLE(Gui)
		public:
			std::vector<float> mColumnWidths; ///< Property: 'ColumnWidhts' The width of each column. This property can be left empty to fill up all available space with equal sized columns. Alternatively the size of the vector can be smaller than the number of columns the wrap around the values.

			bool mBorders = false; ///< Property: 'Borders' True if borders should be drawn between the columns.
			std::vector<ResourcePtr<Gui>> mContent; ///< Property: 'Content' An embedded Gui to be displayed in each column. The size of this vector equals the number of columns.

		public:
			HorizontalLayout() = default;

		private:
			void draw() override;
		};

	} // namespace gui
} // namespace nap